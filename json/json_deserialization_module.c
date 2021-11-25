#include <wjelement.h>
#include <string.h>
#include <stdbool.h>
#include "../table_storage/storage.h"
#include "json_deserialization_module.h"
#include <ctype.h>

int check_if_string_is_float(char *str) {
    int len;
    float ignore;
    char *str1 = malloc(strlen(str));
    strcpy(str1, str);
    int ret = sscanf(str1, "%f %n", &ignore, &len);
    //printf("%d", ret == 1 && !str1[len]);
    //printf("str after float is %s\n", str);
}

int check_if_string_is_int(char *str) {
    char *str1 = malloc(strlen(str));
    strcpy(str1, str);
    for (int i = 0; str1[i] != '\0'; i++) {
        if (isdigit(str1[i]) == 0)
            return 0;
    }
    return 1;
}

static struct storage_value *json_to_storage_value(char * str) {
    struct storage_value *value;

    if (check_if_string_is_int(str) == 1) {
        int x = atoi(str);
        value = malloc(sizeof(*value));
        value->value._int = x;
        if (value->value._int < 0) {
            value->type = STORAGE_COLUMN_TYPE_INT;
        } else {
            value->type = STORAGE_COLUMN_TYPE_UINT;
            value->value.uint = x;
        }
        return value;
    }

    if (check_if_string_is_float(str) == 1) {
        value = malloc(sizeof(*value));
        value->type = STORAGE_COLUMN_TYPE_NUM;
        double d;
        sscanf(str, "%lf", &d);
        value->value.num = d;
        return value;
    }

    value = malloc(sizeof(*value));
    value->type = STORAGE_COLUMN_TYPE_STR;
    value->value.str = str;
    return value;
}

static struct json_where *json_to_where(WJElement command) {
    struct json_where *where = malloc(sizeof(*where));

    WJElement condition = NULL;
    int x = 0;
    while (condition = WJEObjectF(command, WJE_GET, NULL, "condition[%d]", x)) {
        //column name
        char *type = WJEStringF(condition, WJE_GET, NULL, NULL, "condition-type");
        where->op = convert_string_to_operator(type);
        //left param
        where->column = WJEStringF(condition, WJE_GET, NULL, NULL, "left-param");
        //right param
        char * string_value = WJEStringF(condition, WJE_GET, NULL, NULL, "right-param");
        where->value = json_to_storage_value(string_value);
        x++;
    }

    if(x==0)
        return NULL;

    return where;
}


char *get_table_name(WJElement command) {
    return WJEStringF(command, WJE_GET, NULL, NULL, "table-name");
}


enum storage_column_type convert_string_to_col_type(const char *str) {
    int j;
    for (j = 0; j < sizeof(col_type_conversion) / sizeof(col_type_conversion[0]); ++j)
        if (!strcmp(str, col_type_conversion[j].str))
            return col_type_conversion[j].val;
}

struct json_create_table_request json_to_create_table_request(WJElement command) {
    struct json_create_table_request request;
    request.table_name = get_table_name(command);
    int amount = 0;
    WJElement column_def = NULL;
    while (column_def = WJEObjectF(command, WJE_GET, NULL, "column-defs[%d]", amount)) {
        amount++;
    }
    request.columns.amount = amount;
    request.columns.columns = malloc(sizeof(*request.columns.columns) * request.columns.amount);
    amount = 0;
    while (column_def = WJEObjectF(command, WJE_GET, NULL, "column-defs[%d]", amount)) {
        request.columns.columns[amount].name = WJEStringF(column_def, WJE_GET, NULL, NULL, "name");
        char *col_type = WJEStringF(column_def, WJE_GET, NULL, NULL, "type");
        //TODO on client change col types
        request.columns.columns[amount].type = convert_string_to_col_type(col_type);
        amount++;
    }
    return request;
}

struct json_drop_table_request json_to_drop_table_request(WJElement command) {
    struct json_drop_table_request request;
    request.table_name = get_table_name(command);
    return request;
}

struct json_select_request json_to_select_request(WJElement command) {
    fflush(stdout);
    printf("i am here2\n");
    fflush(stdout);
    struct json_select_request request;
    request.columns.amount = 0;
    request.columns.columns = NULL;
    request.where = NULL;
    request.table_name = get_table_name(command);
    request.where = json_to_where(command);
    WJElement selected_columns = NULL;
    int amount = 0;
    selected_columns = WJEArrayF(command, WJE_GET, &selected_columns, "selected-columns");
    char *column_name = NULL;
    while ((column_name = WJEStringF(selected_columns, WJE_GET, NULL, NULL, "[%d]", amount))) {
        amount++;
    }
    if (selected_columns == NULL)
        request.columns.amount = 0;
    request.columns.amount = amount;
    request.columns.columns = malloc(sizeof(*request.columns.columns) * request.columns.amount);
    amount = 0;
    while ((column_name = WJEStringF(selected_columns, WJE_GET, NULL, NULL, "[%d]", amount))) {
        request.columns.columns[amount] = column_name;
        amount++;
    }
    return request;
}

struct json_update_request json_to_update_request(WJElement command) {
    struct json_update_request request;
    request.where = NULL;
    request.table_name = get_table_name(command);
    request.where = json_to_where(command);
    WJElement set_value = NULL;
    int amount = 0;
    while (set_value = WJEObjectF(command, WJE_GET, NULL, "set-values[%d]", amount)) {
        amount++;
    }
    request.columns.amount = amount;
    request.columns.columns = malloc(sizeof(*request.columns.columns) * request.columns.amount);
    request.values.amount = amount;
    request.values.values = malloc(sizeof(struct storage_value *) * request.values.amount);
    amount = 0;
    while (set_value = WJEObjectF(command, WJE_GET, NULL, "set-values[%d]", amount)) {
        request.columns.columns[amount] = WJEStringF(set_value, WJE_GET, NULL, NULL, "col-name");
        char * value = WJEStringF(set_value, WJE_GET, NULL, NULL, "value");
        request.values.values[amount] = json_to_storage_value(value);
        amount++;
    }
    return request;
}

struct json_insert_request json_to_insert_request(WJElement command) {
    struct json_insert_request request;

    request.columns.amount = 0;
    request.columns.columns = NULL;

    request.table_name = get_table_name(command);

    WJElement selected_columns = NULL;
    int col_amount = 0;
    selected_columns = WJEArrayF(command, WJE_GET, &selected_columns, "selected-columns");
    char *column_name = NULL;
    while ((column_name = WJEStringF(selected_columns, WJE_GET, NULL, NULL, "[%d]", col_amount))) {
        col_amount++;
    }
    request.columns.amount = col_amount;
    request.columns.columns = malloc(sizeof(*request.columns.columns) * request.columns.amount);

    col_amount = 0;

    while ((column_name = WJEStringF(selected_columns, WJE_GET, NULL, NULL, "[%d]", col_amount))) {
        request.columns.columns[col_amount] = column_name;
        col_amount++;
    }

    WJElement inserted_values = NULL;
    int value_amount = 0;
    inserted_values = WJEArrayF(command, WJE_GET, &inserted_values, "values");
    char * value = NULL;
    while ((value = WJEStringF(inserted_values, WJE_GET, NULL, NULL, "[%d]", value_amount))) {
        value_amount++;
    }

    request.values.amount = value_amount;
    request.values.values = malloc(sizeof(struct storage_value *) * request.values.amount);

    value_amount = 0;

    while ((value = WJEStringF(inserted_values, WJE_GET, NULL, NULL, "[%d]", value_amount))) {
        request.values.values[value_amount] = json_to_storage_value(value);
        value_amount++;
    }

    return request;
}

enum json_operator convert_string_to_operator(const char *str) {
    int j;
    for (j = 0; j < sizeof(operator_conversion) / sizeof(operator_conversion[0]); ++j)
        if (!strcmp(str, operator_conversion[j].str))
            return operator_conversion[j].val;
}


struct json_delete_request json_to_delete_request(WJElement command) {
    struct json_delete_request request;
    request.where = NULL;
    request.table_name = get_table_name(command);
    request.where = json_to_where(command);
    return request;
}

