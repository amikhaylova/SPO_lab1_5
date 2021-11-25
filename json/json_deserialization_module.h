#ifndef SPO_LAB1_5_JSON_DESERIALIZATION_MODULE_H
#define SPO_LAB1_5_JSON_DESERIALIZATION_MODULE_H

#include <wjelement.h>
#include "../table_storage/storage.h"

struct json_create_table_request {
    char *table_name;
    struct {
        unsigned int amount;
        struct {
            char *name;
            enum storage_column_type type;
        } *columns;
    } columns;
};

struct json_drop_table_request {
    char *table_name;
};

struct json_insert_request {
    char *table_name;
    struct {
        unsigned int amount;
        char **columns;
    } columns;
    struct {
        unsigned int amount;
        struct storage_value **values;
    } values;
};

enum json_operator {
    OPERATOR_EQ = 0,
    OPERATOR_GT = 1,
    OPERATOR_LE = 2,
};

const static struct {
    enum json_operator val;
    const char *str;
} operator_conversion[] = {
        {OPERATOR_EQ, "="},
        {OPERATOR_GT, ">"},
        {OPERATOR_LE, ""}
};


struct json_where {
    enum json_operator op;
    struct {
        char *column;
        struct storage_value *value;
    };
};

struct json_delete_request {
    char *table_name;
    struct json_where *where;
};

struct json_select_request {
    char *table_name;
    struct {
        unsigned int amount;
        char **columns;
    } columns;
    struct json_where *where;
};

struct json_update_request {
    char *table_name;
    struct {
        unsigned int amount;
        char **columns;
    } columns;
    struct {
        unsigned int amount;
        struct storage_value **values;
    } values;
    struct json_where *where;
};

const static struct {
    enum storage_column_type val;
    const char *str;
} col_type_conversion[] = {
        {STORAGE_COLUMN_TYPE_INT,  "INT"},
        {STORAGE_COLUMN_TYPE_UINT, "UINT"},
        {STORAGE_COLUMN_TYPE_NUM,  "NUM"},
        {STORAGE_COLUMN_TYPE_STR,  "TEXT"}
};

enum storage_column_type convert_string_to_col_type(const char *str);

enum json_operator convert_string_to_operator(const char *str);

struct json_create_table_request json_to_create_table_request(WJElement command);

struct json_drop_table_request json_to_drop_table_request(WJElement command);

struct json_insert_request json_to_insert_request(WJElement command);

struct json_delete_request json_to_delete_request(WJElement command);

struct json_select_request json_to_select_request(WJElement command);

struct json_update_request json_to_update_request(WJElement command);


#endif //SPO_LAB1_5_JSON_DESERIALIZATION_MODULE_H
