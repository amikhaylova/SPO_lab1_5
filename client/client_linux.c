#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <wjelement.h>

#define MAX 80
#define PORT 9090
#define SA struct sockaddr
#define BOLDGREEN   "\033[1m\033[32m"
#define RESET "\033[0m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"

int sockfd;

int send_message_size(uint32_t size) {
    write(sockfd, &size, sizeof(uint32_t));
    return 0;
}

int send_message_client(char *message, uint32_t size) {
    write(sockfd, message, size);
    return 0;
}

void read_n_bytes(int socket, unsigned int x, void *buffer) {
    int bytesRead = 0;
    int result;
    while (bytesRead < x) {
        result = read(socket, buffer + bytesRead, x - bytesRead);
        if (result < 1) {
        }
        bytesRead += result;
    }
}


void send_and_receive(char *message_to_send, WJElement *response) {
    uint32_t size = (int) strlen(message_to_send);
    send_message_size(size);
    send_message_client(message_to_send, size);

    uint32_t size_buf[1];
    read(sockfd, size_buf, sizeof(size_buf));
    uint32_t response_size = *size_buf;
    char buff[response_size];
    bzero(buff, response_size);
    read_n_bytes(sockfd, response_size, buff);
    *response = WJEParse(buff);
}

int initialize_client() {
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    } else
        printf("connected to the server..\n");

    // close the socket
    //close(sockfd);
}


void handle_response(WJElement response) {
    char *response_status = WJEStringF(response, WJE_GET, NULL, NULL, "status");
    if (strcmp(response_status, "success") == 0) {
        char *type = WJEStringF(response, WJE_GET, NULL, NULL, "query-type");
        if (strcmp(type, "SELECT") == 0) {

            WJElement col_array = NULL;
            col_array = WJEArrayF(response, WJE_GET, &col_array, "columns");
            char *column_name = NULL;
            int64_t col_amount = 0;
            while ((column_name = WJEStringF(col_array, WJE_GET, NULL, NULL, "[%ld]", col_amount))) {
                col_amount++;
            }

            char *columns[col_amount];
            int i = 0;
            size_t longest_column_length = 0;
            while ((column_name = WJEStringF(col_array, WJE_GET, NULL, NULL, "[%d]", i))) {
                columns[i] = column_name;
                if (strlen(columns[i]) > longest_column_length)
                    longest_column_length = strlen(columns[i]);
                i++;
            }

            int64_t amount = WJEInt64F(response, WJE_GET, NULL, NULL, "amount");
            char *rows_array[amount][col_amount];

            WJElement rows = WJEArray(response, "values", WJE_GET);
            WJElement row = NULL;
            int k = 0;
            while (row = WJEArrayF(rows, WJE_GET, NULL, "[%d]", k)) {
                char *value;
                int m = 0;
                while (value = WJEStringF(response, WJE_GET, NULL, NULL, "values[%d][%d]", k, m)) {
                    rows_array[k][m] = value;
                    if (strlen(rows_array[k][m]) > longest_column_length)
                        longest_column_length = strlen(rows_array[k][m]);
                    m++;
                }
                k++;
            }

            int length = longest_column_length + 5;

            for (int j = 0; j < col_amount; j++) {
                printf(BOLDGREEN "%-*s" RESET, (int) length, columns[j]);
            }
            printf("\n");
            for (int i = 0; i < amount; i++) {
                for (int j = 0; j < col_amount; j++) {
                    printf("%-*s", (int) length, rows_array[i][j]);
                }
                printf("\n");
            }
            printf(MAGENTA "%ld rows were selected\n" RESET, amount);
        } else if (strcmp(type, "DELETE") == 0) {
            int64_t amount = WJEInt64F(response, WJE_GET, NULL, NULL, "amount");
            printf(MAGENTA"%ld rows were deleted\n"RESET, amount);
        } else if (strcmp(type, "UPDATE") == 0) {
            int64_t amount = WJEInt64F(response, WJE_GET, NULL, NULL, "amount");
            printf(MAGENTA"%ld rows were updated\n"RESET, amount);
        } else if (strcmp(type, "DROP") == 0 || strcmp(type, "CREATE") == 0 || strcmp(type, "INSERT") == 0) {
            char *msg = WJEStringF(response, WJE_GET, NULL, NULL, "msg");
            printf(MAGENTA"%s\n"RESET, msg);
        }
    } else if (strcmp(response_status, "failed") == 0) {
        char *msg = WJEStringF(response, WJE_GET, NULL, NULL, "msg");
        printf(RED"operation failed: %s\n"RESET, msg);
    } else {
        printf(RED"%s\n"RESET, "unexpected answer from server\n");
    }

}


void handle_response_interface(WJElement response, char * output) {
    char *response_status = WJEStringF(response, WJE_GET, NULL, NULL, "status");
    if (strcmp(response_status, "success") == 0) {
        char *type = WJEStringF(response, WJE_GET, NULL, NULL, "query-type");
        if (strcmp(type, "SELECT") == 0) {

            WJElement col_array = NULL;
            col_array = WJEArrayF(response, WJE_GET, &col_array, "columns");
            char *column_name = NULL;
            int64_t col_amount = 0;
            while ((column_name = WJEStringF(col_array, WJE_GET, NULL, NULL, "[%ld]", col_amount))) {
                col_amount++;
            }

            char *columns[col_amount];
            int i = 0;
            size_t longest_column_length = 0;
            while ((column_name = WJEStringF(col_array, WJE_GET, NULL, NULL, "[%d]", i))) {
                columns[i] = column_name;
                if (strlen(columns[i]) > longest_column_length)
                    longest_column_length = strlen(columns[i]);
                i++;
            }

            int64_t amount = WJEInt64F(response, WJE_GET, NULL, NULL, "amount");
            char *rows_array[amount][col_amount];

            WJElement rows = WJEArray(response, "values", WJE_GET);
            WJElement row = NULL;
            int k = 0;
            while (row = WJEArrayF(rows, WJE_GET, NULL, "[%d]", k)) {
                char *value;
                int m = 0;
                while (value = WJEStringF(response, WJE_GET, NULL, NULL, "values[%d][%d]", k, m)) {
                    rows_array[k][m] = value;
                    if (strlen(rows_array[k][m]) > longest_column_length)
                        longest_column_length = strlen(rows_array[k][m]);
                    m++;
                }
                k++;
            }

            int length = longest_column_length + 5;

            for (int j = 0; j < col_amount; j++) {
                output += sprintf(output, "%-*s", (int) length, columns[j]);
                printf(BOLDGREEN "%-*s" RESET, (int) length, columns[j]);
            }
            output += sprintf(output, "\r\n");
            printf("\n");
            for (int i = 0; i < amount; i++) {
                for (int j = 0; j < col_amount; j++) {
                    output += sprintf(output, "%-*s", (int) length, rows_array[i][j]);
                    printf("%-*s", (int) length, rows_array[i][j]);
                }
                output += sprintf(output, "\r\n");
                printf("\n");
            }
            printf(MAGENTA "%ld rows were selected\n" RESET, amount);
            output += sprintf(output, "%ld rows were selected\r\n", amount);
        } else if (strcmp(type, "DELETE") == 0) {
            int64_t amount = WJEInt64F(response, WJE_GET, NULL, NULL, "amount");
            printf(MAGENTA"%ld rows were deleted\n"RESET, amount);
            output += sprintf(output,"%ld rows were deleted\r\n", amount);
        } else if (strcmp(type, "UPDATE") == 0) {
            int64_t amount = WJEInt64F(response, WJE_GET, NULL, NULL, "amount");
            output += sprintf(output, "%ld rows were updated\r\n", amount);
            printf(MAGENTA"%ld rows were updated\n"RESET, amount);
        } else if (strcmp(type, "DROP") == 0 || strcmp(type, "CREATE") == 0 || strcmp(type, "INSERT") == 0) {
            char *msg = WJEStringF(response, WJE_GET, NULL, NULL, "msg");
            output += sprintf(output, "%s\r\n", msg);
            printf(MAGENTA"%s\n"RESET, msg);
        }
    } else if (strcmp(response_status, "failed") == 0) {
        char *msg = WJEStringF(response, WJE_GET, NULL, NULL, "msg");
        printf(RED"operation failed: %s\n"RESET, msg);
        output += sprintf(output, "operation failed: %s\r\n", msg);
    } else {
        output += sprintf(output,"unexpected answer from server\r\n");
        printf(RED"%s\n", "unexpected answer from server\n");
    }

}