#include <string.h>
#include <wjelement.h>
#include "json_serialization_module.h"

WJElement get_create_object(struct sql_node * node){
    char * query_type = "CREATE";
    struct sql_node * table = node->first->first;
    char * table_name = table->first->text;
    struct sql_node * columns = table->first->next;
    struct sql_node * column_def = columns->first;

    WJElement element = NULL;
    element = WJEObject(NULL, NULL, WJE_NEW);
    WJEString(element, "query-type", WJE_SET, query_type);
    WJEString(element, "table-name", WJE_SET, table_name);
    WJEArray(element, "column-defs", WJE_SET);

    while (column_def!= NULL){
        WJEObject(element, "column-defs[$]", WJE_NEW);
        WJEString(element, "column-defs[-1].name", WJE_SET, column_def->first->first->text);
        WJEString(element, "column-defs[-1].type", WJE_SET, column_def->first->next->first->text);
        column_def = column_def-> next;
    }

    return element;
}

WJElement get_select_object(struct sql_node * node){
    char * query_type = "SELECT";

    struct sql_node * values = node->first->first;

    WJElement element = NULL;
    element = WJEObject(NULL, NULL, WJE_NEW);
    WJEString(element, "query-type", WJE_SET, query_type);
    WJEArray(element, "selected-columns", WJE_SET);

    if (strcmp(values->text, "all") == 0){
        WJEObject(element, "selected-columns[$]", WJE_NEW);
        WJEString(element, "selected-columns[-1]", WJE_SET, "ALL");
    }else{
        struct sql_node * cur_value = values -> first;
        while (cur_value != NULL){
            WJEObject(element, "selected-columns[$]", WJE_NEW);
            WJEString(element, "selected-columns[-1]", WJE_SET, cur_value->text);
            cur_value = cur_value -> next;
        }
    }

    struct sql_node * table = values->next;
    char * table_name = table->first->text;
    WJEString(element, "table-name", WJE_SET, table_name);

    if (table -> next != NULL){
        struct sql_node * condition = table -> next;
        char * condition_type = condition->text;
        char * left_param = condition->first->text;
        char * right_param =condition->first->next->text;
        WJEArray(element, "condition", WJE_SET);
        WJEString(element, "condition[$].condition-type", WJE_NEW, condition_type);
        WJEString(element, "condition[-1].right-param", WJE_NEW, right_param);
        WJEString(element, "condition[-1].left-param", WJE_NEW, left_param);
    }
    printf("\n");
    return element;
}

WJElement get_update_object(struct sql_node * node){
    WJElement element = NULL;
    element = WJEObject(NULL, NULL, WJE_NEW);

    char * query_type = "UPDATE";
    WJEString(element, "query-type", WJE_SET, query_type);

    char * table_name = node->first->first->text;
    WJEString(element, "table-name", WJE_SET, table_name);

    WJEArray(element, "set-values", WJE_SET);

    struct sql_node * set_values = node->first->next;
    struct sql_node * cur_value = set_values->first;
    while (cur_value != NULL){
        WJEObject(element, "set-values[$]", WJE_NEW);
        WJEString(element, "set-values[-1].col-name", WJE_SET, cur_value->first->text);
        WJEString(element, "set-values[-1].value", WJE_SET, cur_value->first->next->text);
        cur_value = cur_value->next;
    }
    struct sql_node * condition = set_values->next;
    char * condition_type = condition->first->text;
    char * left_param = condition->first->first->text;
    char * right_param =condition->first->first->next->text;

    WJEArray(element, "condition", WJE_SET);
    WJEString(element, "condition[$].condition-type", WJE_NEW, condition_type);
    WJEString(element, "condition[-1].right-param", WJE_NEW, right_param);
    WJEString(element, "condition[-1].left-param", WJE_NEW, left_param);

    return element;
}

WJElement get_insert_object(struct sql_node * node){
    WJElement element = NULL;
    element = WJEObject(NULL, NULL, WJE_NEW);

    char * query_type = "INSERT";
    WJEString(element, "query-type", WJE_SET, query_type);

    char * table_name = node->first->first->first->text;
    WJEString(element, "table-name", WJE_SET, table_name);

    struct sql_node * columns = NULL;
    struct sql_node * values = NULL;
    if (strcmp(node->first->first->next->text, "columns") == 0 ){
        columns = node->first->first->next;
        values =  node->first->first->next->next;
    }else if (strcmp(node->first->first->next->text, "values") == 0){
        values = node->first->first->next;
        columns = NULL;
    }
    if (columns != NULL){
        WJEArray(element, "selected-columns", WJE_SET);
        struct sql_node * cur_column = columns -> first;
        while (cur_column != NULL){
            //selected columns
            //printf ("%s ", cur_column->text);
            WJEObject(element, "selected-columns[$]", WJE_NEW);
            WJEString(element, "selected-columns[-1]", WJE_SET, cur_column->text);
            cur_column = cur_column -> next;

        }
    }
    if (values != NULL){
        WJEArray(element, "values", WJE_SET);
        struct sql_node * cur_value = values -> first;
        while (cur_value != NULL){
            //values
           // printf ("%s ", cur_value->text);
            WJEObject(element, "values[$]", WJE_NEW);
            WJEString(element, "values[-1]", WJE_SET, cur_value->text);
            cur_value = cur_value -> next;
        }
    }
    return element;
    //printf ("%s %s\n", query_type, table_name);
}

WJElement get_drop_object(struct sql_node * node){
    char * query_type = "DROP";
    char * table_name = node->first->first->text;
    printf ("%s %s\n", query_type, table_name);
    WJElement element = NULL;
    element = WJEObject(NULL, NULL, WJE_NEW);
    WJEString(element, "query-type", WJE_SET, query_type);
    WJEString(element, "table-name", WJE_SET, table_name);
    return element;
}

WJElement get_delete_object(struct sql_node * node){
    WJElement element = WJEObject(NULL, NULL, WJE_NEW);
    char * query_type = "DELETE";

    WJEString(element, "query-type", WJE_SET, query_type);

    char * table_name = node->first->first->text;
    WJEString(element, "table-name", WJE_SET, table_name);

    struct sql_node * condition = node->first->next;
    char * condition_type = condition->first->text;
    char * left_param = condition->first->first->text;
    char * right_param =condition->first->first->next->text;

    WJEArray(element, "condition", WJE_SET);
    WJEString(element, "condition[$].condition-type", WJE_NEW, condition_type);
    WJEString(element, "condition[-1].right-param", WJE_NEW, right_param);
    WJEString(element, "condition[-1].left-param", WJE_NEW, left_param);

    return element;
}

WJElement get_json_object(struct sql_node * node) {
    char * query_type = node->first->text;

    if (strcmp(query_type, "create") == 0) {
        return get_create_object(node);
    }else if (strcmp(query_type, "drop") == 0) {
        return get_drop_object(node);
    }else if (strcmp(query_type, "select") == 0) {
        return get_select_object(node);
    }else if (strcmp(query_type, "update") == 0) {
        return get_update_object(node);
    }else if (strcmp(query_type, "insert") == 0) {
        return get_insert_object(node);
    }else if (strcmp(query_type, "delete") == 0) {
        return get_delete_object(node);
    }
    return NULL;
}

char * sql_node_to_json_string(struct sql_node * node){
    WJElement json_object = get_json_object(node);
    return WJEToString(json_object, TRUE);
}