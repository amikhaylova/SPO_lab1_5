#ifndef SPO_LAB_1_5_LEX_YY_H
#define SPO_LAB_1_5_LEX_YY_H

#include <stdio.h>
#include <stdlib.h>

char * yytext;

struct sql_node {
    int node_type;
    struct sql_node * first;
    struct sql_node * next;
    char * text;
};


void set_input_string(const char* in);
void end_lexical_scan(void);

int parse_string(const char* in, struct sql_node * node);
void print_sql_tree(struct sql_node * curr, int level);


#endif //SPO_LAB_1_5_LEX_YY_H
