#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wjelement.h>
#include <errno.h>
#include <sys/fcntl.h>
#include <stdbool.h>
#include "../json/json_deserialization_module.h"
#include "../json/json_serialization_module.h"

#define MAX 512
#define PORT 9090
#define SA struct sockaddr
char *TABLE_DOES_NOT_EXIST = "table with the specified name does not exist";
char *TABLE_DOES_EXIST = "table with the specified name already exists";

static char *
map_columns_to_indexes(unsigned int request_columns_amount, char **request_columns_names,
                       struct storage_table *table, unsigned int *columns_amount,
                       unsigned int **columns_indexes) {
    unsigned int columns_count = request_columns_amount;

    uint16_t table_columns_amount = table->columns.amount;

    if (columns_count == 0) {
        columns_count = table_columns_amount;
    }

    *columns_indexes = malloc(sizeof(**columns_indexes) * columns_count);
    if (request_columns_amount == 0) {
        for (unsigned int i = 0; i < columns_count; ++i) {
            (*columns_indexes)[i] = i;
        }
    } else {
        for (unsigned int i = 0; i < columns_count; ++i) {
            bool found = false;
            for (unsigned int j = 0; j < table_columns_amount; j++) {
                if (strcmp(request_columns_names[i], table->columns.columns[j].name) == 0) {
                    (*columns_indexes)[i] = j;
                    found = true;
                    break;
                }
            }

            if (!found) {
                size_t msg_length = 41 + strlen(request_columns_names[i]);
                char msg[msg_length];
                snprintf(msg, msg_length, "column with name %s is not exists in table", request_columns_names[i]);
                return get_failure_response(msg);
            }
        }
    }

    *columns_amount = columns_count;
    return NULL;
}

static char *
check_values(unsigned int request_values_amount, struct storage_value **request_values_values,
             struct storage_table *table, unsigned int columns_amount, const unsigned int *columns_indexes) {

    if (request_values_amount != columns_amount) {
        return get_failure_response("values amount is not equals to columns amount");
    }

    for (unsigned int i = 0; i < columns_amount; ++i) {
        if (request_values_values[i] == NULL) {
            continue;
        }

        struct storage_column column = table->columns.columns[columns_indexes[i]];
        if (request_values_values[i]->type == column.type) {
            continue;
        }

        switch (request_values_values[i]->type) {
            case STORAGE_COLUMN_TYPE_INT:
                if (column.type == STORAGE_COLUMN_TYPE_UINT) {
                    if (request_values_values[i]->value._int >= 0) {
                        request_values_values[i]->type = STORAGE_COLUMN_TYPE_UINT;
                        request_values_values[i]->value.uint = (uint64_t) request_values_values[i]->value._int;
                        continue;
                    }
                }

                break;

            case STORAGE_COLUMN_TYPE_UINT:
                if (column.type == STORAGE_COLUMN_TYPE_INT) {
                    if (request_values_values[i]->value.uint <= INT64_MAX) {
                        request_values_values[i]->type = STORAGE_COLUMN_TYPE_INT;
                        request_values_values[i]->value._int = (int64_t) request_values_values[i]->value.uint;
                        continue;
                    }
                }

                break;

            default:
                break;
        }

        const char *col_type = storage_column_type_to_string(column.type);
        const char *val_type = storage_column_type_to_string(request_values_values[i]->type);
        size_t msg_length = 47 + strlen(column.name) + strlen(col_type) + strlen(val_type);

        char msg[msg_length];
        snprintf(msg, msg_length, "value for column with name %s (%s) has wrong type %s",
                 column.name, col_type, val_type);
        return get_failure_response(msg);
    }

    return NULL;
}

char *handle_create_table(WJElement command, struct storage *storage) {
    struct json_create_table_request request = json_to_create_table_request(command);

    struct storage_table *table = malloc(sizeof(*table));

    table->storage = storage;
    table->position = 0;
    table->next = 0;
    table->first_row = 0;
    table->name = strdup(request.table_name);
    table->columns.amount = request.columns.amount;
    table->columns.columns = malloc(sizeof(*table->columns.columns) * request.columns.amount);

    for (int i = 0; i < request.columns.amount; ++i) {
        table->columns.columns[i].name = strdup(request.columns.columns[i].name);
        table->columns.columns[i].type = request.columns.columns[i].type;
    }

    errno = 0;
    storage_table_add(table);
    bool error = errno != 0;

    storage_table_delete(table);

    if (error) {
        return get_failure_response(TABLE_DOES_EXIST);
    } else {
        return get_success_response_msg("the table was successfully created", "CREATE");
    }
}

char *handle_drop_table(WJElement command, struct storage *storage) {
    struct json_drop_table_request request = json_to_drop_table_request(command);

    struct storage_table *table = storage_find_table(storage, request.table_name);

    if (!table) {
        return get_failure_response(TABLE_DOES_NOT_EXIST);
    }
    storage_table_remove(table);
    storage_table_delete(table);
    return get_success_response_msg("the table was successfully dropped", "DROP");
}


char *handle_insert_row(WJElement command, struct storage *storage) {
    struct json_insert_request request = json_to_insert_request(command);

    struct storage_table *table = storage_find_table(storage, request.table_name);

    if (!table) {
        return get_failure_response(TABLE_DOES_NOT_EXIST);
    }

    unsigned int columns_amount;
    unsigned int *columns_indexes;

    char *error = map_columns_to_indexes(request.columns.amount, request.columns.columns,
                                         table, &columns_amount, &columns_indexes);

    if (error) {
        storage_table_delete(table);
        return error;

    }


    char *error1 = check_values(request.values.amount, request.values.values, table, columns_amount, columns_indexes);

    if (error1) {
        free(columns_indexes);
        storage_table_delete(table);
        return error1;
    }


    struct storage_row *row = storage_table_add_row(table);
    for (unsigned int i = 0; i < columns_amount; ++i) {
        storage_row_set_value(row, columns_indexes[i], request.values.values[i]);
    }

    free(columns_indexes);
    storage_row_delete(row);
    storage_table_delete(table);
    return get_success_response_msg("the row was successfully inserted", "INSERT");
}

static char *is_where_correct(struct storage_table *table, struct json_where *where) {
    printf("in is where correct\n");
    fflush(stdout);
    uint16_t table_columns_amount = table->columns.amount;

    switch (where->op) {
        case OPERATOR_EQ:
        case OPERATOR_GT:
        case OPERATOR_LE:
            if (where->value == NULL) {
                return get_failure_response("NULL value is not comparable");
            }

            for (unsigned int i = 0; i < table_columns_amount; ++i) {
                struct storage_column column = table->columns.columns[i];

                if (strcmp(column.name, where->column) == 0) {
                    switch (column.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                        case STORAGE_COLUMN_TYPE_UINT:
                        case STORAGE_COLUMN_TYPE_NUM:
                            switch (where->value->type) {
                                case STORAGE_COLUMN_TYPE_INT:
                                case STORAGE_COLUMN_TYPE_UINT:
                                case STORAGE_COLUMN_TYPE_NUM:
                                    return NULL;

                                case STORAGE_COLUMN_TYPE_STR:
                                    break;
                            }

                            break;

                        case STORAGE_COLUMN_TYPE_STR:
                            if (where->value->type == STORAGE_COLUMN_TYPE_STR) {
                                return NULL;
                            }

                            break;
                    }

                    const char *column_type = storage_column_type_to_string(column.type);
                    const char *value_type = storage_column_type_to_string(where->value->type);
                    size_t msg_length = 31 + strlen(column_type) + strlen(value_type);
                    char msg[msg_length];

                    snprintf(msg, msg_length, "types %s and %s are not comparable", column_type, value_type);
                    return get_failure_response(msg);
                }
            }

            {
                size_t msg_length = 41 + strlen(where->column);
                char msg[msg_length];
                snprintf(msg, msg_length, "column with name %s does not exist in table", where->column);
                return get_failure_response(msg);
            }

    }
}

static bool compare_values_not_null(enum json_operator op, struct storage_value left, struct storage_value right) {
    switch (op) {
        case OPERATOR_EQ:
            switch (left.type) {
                case STORAGE_COLUMN_TYPE_INT:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            return left.value._int == right.value._int;

                        case STORAGE_COLUMN_TYPE_UINT:
                            if (left.value._int < 0) {
                                return false;
                            }

                            return ((uint64_t) left.value._int) == right.value.uint;

                        case STORAGE_COLUMN_TYPE_NUM:
                            return ((double) left.value._int) == right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_UINT:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            if (right.value._int < 0) {
                                return false;
                            }

                            return left.value.uint == ((uint64_t) right.value._int);

                        case STORAGE_COLUMN_TYPE_UINT:
                            return left.value.uint == right.value.uint;

                        case STORAGE_COLUMN_TYPE_NUM:
                            return ((double) left.value.uint) == right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_NUM:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            return left.value.num == ((double) right.value._int);

                        case STORAGE_COLUMN_TYPE_UINT:
                            return left.value.num == ((double) right.value.uint);

                        case STORAGE_COLUMN_TYPE_NUM:
                            return left.value.num == right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_STR:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                        case STORAGE_COLUMN_TYPE_UINT:
                        case STORAGE_COLUMN_TYPE_NUM:
                            return false;

                        case STORAGE_COLUMN_TYPE_STR:
                            return strcmp(left.value.str, right.value.str) == 0;
                    }
            }

        case OPERATOR_LE:
            switch (left.type) {
                case STORAGE_COLUMN_TYPE_INT:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            return left.value._int < right.value._int;

                        case STORAGE_COLUMN_TYPE_UINT:
                            if (left.value._int < 0) {
                                return true;
                            }

                            return ((uint64_t) left.value._int) < right.value.uint;

                        case STORAGE_COLUMN_TYPE_NUM:
                            return ((double) left.value._int) < right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_UINT:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            if (right.value._int < 0) {
                                return false;
                            }

                            return left.value.uint < ((uint64_t) right.value._int);

                        case STORAGE_COLUMN_TYPE_UINT:
                            return left.value.uint < right.value.uint;

                        case STORAGE_COLUMN_TYPE_NUM:
                            return ((double) left.value.uint) < right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_NUM:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            return left.value.num < ((double) right.value._int);

                        case STORAGE_COLUMN_TYPE_UINT:
                            return left.value.num < ((double) right.value.uint);

                        case STORAGE_COLUMN_TYPE_NUM:
                            return left.value.num < right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_STR:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                        case STORAGE_COLUMN_TYPE_UINT:
                        case STORAGE_COLUMN_TYPE_NUM:
                            return false;

                        case STORAGE_COLUMN_TYPE_STR:
                            return strcmp(left.value.str, right.value.str) < 0;
                    }
            }

        case OPERATOR_GT:
            switch (left.type) {
                case STORAGE_COLUMN_TYPE_INT:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            return left.value._int > right.value._int;

                        case STORAGE_COLUMN_TYPE_UINT:
                            if (left.value._int < 0) {
                                return false;
                            }

                            return ((uint64_t) left.value._int) > right.value.uint;

                        case STORAGE_COLUMN_TYPE_NUM:
                            return ((double) left.value._int) > right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_UINT:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            if (right.value._int < 0) {
                                return true;
                            }

                            return left.value.uint > ((uint64_t) right.value._int);

                        case STORAGE_COLUMN_TYPE_UINT:
                            return left.value.uint > right.value.uint;

                        case STORAGE_COLUMN_TYPE_NUM:
                            return ((double) left.value.uint) > right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_NUM:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                            return left.value.num > ((double) right.value._int);

                        case STORAGE_COLUMN_TYPE_UINT:
                            return left.value.num > ((double) right.value.uint);

                        case STORAGE_COLUMN_TYPE_NUM:
                            return left.value.num > right.value.num;

                        case STORAGE_COLUMN_TYPE_STR:
                            return false;
                    }

                case STORAGE_COLUMN_TYPE_STR:
                    switch (right.type) {
                        case STORAGE_COLUMN_TYPE_INT:
                        case STORAGE_COLUMN_TYPE_UINT:
                        case STORAGE_COLUMN_TYPE_NUM:
                            return false;

                        case STORAGE_COLUMN_TYPE_STR:
                            return strcmp(left.value.str, right.value.str) > 0;
                    }
            }

        default:
            return false;
    }
}

static bool compare_values(enum json_operator op, struct storage_value *left, struct storage_value *right) {

    switch (op) {
        case OPERATOR_EQ:
            if (left == NULL || right == NULL) {
                return left == NULL && right == NULL;
            }

            break;

        case OPERATOR_GT:
        case OPERATOR_LE:
            if (left == NULL || right == NULL) {
                return false;
            }

            break;

        default:
            return false;
    }

    return compare_values_not_null(op, *left, *right);
}

static bool eval_where(struct storage_row *row, struct json_where *where) {
    uint16_t table_columns_amount = row->table->columns.amount;

    switch (where->op) {
        case OPERATOR_EQ:
        case OPERATOR_GT:
        case OPERATOR_LE:
            for (unsigned int i = 0; i < table_columns_amount; ++i) {
                if (strcmp(row->table->columns.columns[i].name, where->column) == 0) {
                    return compare_values(where->op, storage_row_get_value(row, (uint16_t) i), where->value);
                }
            }
            errno = EINVAL;
            return false;
    }
}

char *handle_delete_row(WJElement command, struct storage *storage) {
    struct json_delete_request request = json_to_delete_request(command);
    struct storage_table *table = storage_find_table(storage, request.table_name);

    if (!table) {
        return get_failure_response(TABLE_DOES_NOT_EXIST);
    }

    if (request.where) {
        char *error = is_where_correct(table, request.where);

        if (error) {
            storage_table_delete(table);
            return error;
        }
    }

    int amount = 0;
    for (struct storage_row *row = storage_table_get_first_row(table); row; row = storage_row_next(row)) {
        if (request.where == NULL || eval_where(row, request.where)) {
            storage_row_remove(row);
            ++amount;
        }
    }

    storage_table_delete(table);
    return get_success_response(amount, "DELETE");
}

char *handle_select(WJElement command, struct storage *storage) {
    struct json_select_request request = json_to_select_request(command);

    struct storage_table *table = storage_find_table(storage, request.table_name);

    WJElement answer = WJEObject(NULL, NULL, WJE_NEW);

    if (!table) {
        return get_failure_response(TABLE_DOES_NOT_EXIST);
    }

    unsigned int columns_amount;
    unsigned int *columns_indexes;

    char *error = map_columns_to_indexes(request.columns.amount, request.columns.columns,
                                         table, &columns_amount, &columns_indexes);


    if (request.where) {
        char *error1 = is_where_correct(table, request.where);
        if (error) {
            storage_table_delete(table);
            return error;
        }
        if (error1) {
            storage_table_delete(table);
            return error1;
        }
    }


    if (request.columns.amount == 0) {
        for (int i = 0; i < table->columns.amount; i++) {
            WJEObject(answer, "columns[$]", WJE_NEW);
            WJEString(answer, "columns[-1]", WJE_SET, table->columns.columns[i].name);
        }
    } else {
        for (int i = 0; i < columns_amount; i++) {
            WJEObject(answer, "columns[$]", WJE_NEW);
            WJEString(answer, "columns[-1]", WJE_SET, request.columns.columns[i]);
        }
    }

    WJEObject(answer, "values[]", WJE_NEW);
    int amount = 0;
    for (struct storage_row *row = storage_table_get_first_row(table); row; row = storage_row_next(row)) {
        WJEArray(answer, "values[$]", WJE_NEW);
        if (request.where == NULL || eval_where(row, request.where)) {
            for (int i = 0; i < columns_amount; i++) {
                struct storage_value *value = storage_row_get_value(row, columns_indexes[i]);

                if (value == NULL) {
                    WJEString(answer, "values[-1][$]", WJE_SET, "NULL");
                    continue;
                }

                int _int;
                double _double;
                switch (value->type) {
                    case STORAGE_COLUMN_TYPE_INT:
                        _int = value->value._int;
                        int length = snprintf(NULL, 0, "%d", _int);
                        char* str = malloc( length + 1 );
                        snprintf(str, length + 1, "%d", _int );
                        WJEString(answer, "values[-1][$]", WJE_SET, str);
                        free(str);
                        break;
                    case STORAGE_COLUMN_TYPE_UINT:
                        _int = value->value.uint;
                        length = snprintf(NULL, 0, "%d", _int);
                        str = malloc( length + 1 );
                        snprintf(str, length + 1, "%d", _int );
                        WJEString(answer, "values[-1][$]", WJE_SET, str);
                        free(str);
                        break;
                    case STORAGE_COLUMN_TYPE_NUM:
                        _double = value->value.num;
                        length = snprintf(NULL, 0, "%g", _double);
                        str = malloc( length + 1 );
                        snprintf(str, length + 1, "%g", _double);
                        WJEString(answer, "values[-1][$]", WJE_SET, str);
                        free(str);
                        break;
                    case STORAGE_COLUMN_TYPE_STR:
                        WJEString(answer, "values[-1][$]", WJE_SET, value->value.str);
                        break;
                }
            }
            amount++;
        }
    }

    return get_select_success_response(amount, answer);
}

char *handle_update(WJElement command, struct storage *storage) {
    struct json_update_request request = json_to_update_request(command);
    struct storage_table *table = storage_find_table(storage, request.table_name);

    if (!table) {
        return get_failure_response(TABLE_DOES_NOT_EXIST);
    }

    if (request.where) {
        char *error = is_where_correct(table, request.where);
        if (error) {
            storage_table_delete(table);
            return error;
        }
    }

    unsigned int columns_amount;
    unsigned int *columns_indexes;


        char *error = map_columns_to_indexes(request.columns.amount, request.columns.columns,
                                             table, &columns_amount, &columns_indexes);

        if (error) {
            storage_table_delete(table);
            return error;
        }



         char *error1 = check_values(request.values.amount, request.values.values, table, columns_amount,
                                                  columns_indexes);

         if (error1) {
             free(columns_indexes);
             storage_table_delete(table);
             return error1;
         }


    int amount = 0;
    for (struct storage_row *row = storage_table_get_first_row(table); row; row = storage_row_next(row)) {
        if (request.where == NULL || eval_where(row, request.where)) {
            for (unsigned int i = 0; i < columns_amount; ++i) {
                storage_row_set_value(row, columns_indexes[i], request.values.values[i]);
            }
            ++amount;
        }
    }

    free(columns_indexes);
    storage_table_delete(table);
    return get_success_response(amount, "UPDATE");

}


char *handle_request(WJElement command, struct storage *storage) {
    char *query_type = WJEStringF(command, WJE_GET, NULL, NULL, "query-type");

    if (strcmp(query_type, "CREATE") == 0) {
        return handle_create_table(command, storage);
    } else if (strcmp(query_type, "DROP") == 0) {
        return handle_drop_table(command, storage);
    } else if (strcmp(query_type, "SELECT") == 0) {
        return handle_select(command, storage);
    } else if (strcmp(query_type, "UPDATE") == 0) {
        return handle_update(command, storage);
    } else if (strcmp(query_type, "INSERT") == 0) {
        return handle_insert_row(command, storage);
    } else if (strcmp(query_type, "DELETE") == 0) {
        return handle_delete_row(command, storage);
    }
    return "";
}

void readXBytes(int socket, unsigned int x, void *buffer) {
    int bytesRead = 0;
    int result;
    while (bytesRead < x) {
        result = read(socket, buffer + bytesRead, x - bytesRead);
        if (result < 1) {
        }
        bytesRead += result;
    }
}

int send_message(char *message, int sockfd){
    uint32_t size = (int) strlen(message);
    write(sockfd, &size, sizeof(uint32_t));
    write(sockfd, message, size);
    return 1;
}

// Function designed for chat between client and server.
void receive_and_send(int sockfd, struct storage *storage) {
    char buff[MAX];
    bzero(buff, MAX);
    uint32_t size_buf[1];
    read(sockfd, size_buf, sizeof(size_buf));
    uint32_t size = *size_buf;
    readXBytes(sockfd, size, buff);
    WJElement wjelement = WJEParse(buff);
    char * response = handle_request(wjelement, storage);
    send_message(response, sockfd);
}

int server_linux() {
    int fd = open("db", O_RDWR);
    struct storage *storage;

    if (fd < 0 && errno != ENOENT) {
        perror("Error while opening file");
        return errno;
    }

    if (fd < 0 && errno == ENOENT) {
        //TODO file from args
        fd = open("db", O_CREAT | O_RDWR, 0644);
        storage = storage_init(fd);
    } else {
        storage = storage_open(fd);
    }

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *) &servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *) &cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    } else
        printf("server accept the client...\n");

    bool quit = false;
    // Function for chatting between client and server
    while (!quit) {
        receive_and_send(connfd, storage);
    }

    // After chatting close the socket
    close(sockfd);
}
