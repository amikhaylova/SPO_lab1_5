#include "../sql_lexical_analyzer/lex.yy.h"
#include <string.h>

#ifndef SPO_LAB1_5_JSON_MODULE_H
#define SPO_LAB1_5_JSON_MODULE_H

char * WHERE_FAILED = "where clause is invalid";
char * TABLE_DOES_NOT_EXIST = "table with the specified name does not exist";
char * TABLE_DOES_EXIST = "table with the specified name already exists";
char * MAP_COLUMNS_FAILURE = "was unable to map column to indexes";

WJElement get_json_request_object(struct sql_node * node);
char * sql_node_to_json_string(struct sql_node * node);

char *get_success_response(int amount);
char *get_failure_response(char *msg);
char *get_select_success_response(int amount, WJElement element);
char *get_success_response_msg(char * msg);

#endif //SPO_LAB1_5_JSON_MODULE_H
