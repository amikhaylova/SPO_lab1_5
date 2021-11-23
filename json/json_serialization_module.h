#include "../sql_lexical_analyzer/lex.yy.h"
#include <string.h>

#ifndef SPO_LAB1_5_JSON_MODULE_H
#define SPO_LAB1_5_JSON_MODULE_H

WJElement get_json_object(struct sql_node * node);
char * sql_node_to_json_string(struct sql_node * node);

#endif //SPO_LAB1_5_JSON_MODULE_H
