#include "../sql_lexical_analyzer/lex.yy.h"
#include <string.h>

#ifndef SPO_LAB1_5_JSON_MODULE_H
#define SPO_LAB1_5_JSON_MODULE_H

WJElement get_json_request_object(struct sql_node * node);
char * sql_node_to_json_string(struct sql_node * node);

char *get_success_response(int amount, char * query_type);
char *get_failure_response(char *msg);
char *get_select_success_response(int amount, WJElement element);
char *get_success_response_msg(char * msg, char * query_type);

#endif //SPO_LAB1_5_JSON_MODULE_H
