%{
#include <stdio.h>
#include <string.h>
#include "../sql_lexical_analyzer/lex.yy.h"

#define CORRECT_SYNTAX_MESSAGE "Syntax Correct\n"
#define YYERROR_VERBOSE 1

int yylex(void);
int yyparse(void);
int yychar;

void yyerror(const char *str)
{
        fprintf(stderr,"Error: %s\n",str);
}

int yywrap()
{
        return 1;
}

struct sql_node * new_sql_node (
    int node_type,
    char * text,
    struct sql_node * first,
    struct sql_node * next
) {
  struct sql_node * sql_node = malloc (sizeof (struct sql_node));
  sql_node->node_type = node_type;
  sql_node->text = text;
  sql_node->first = first;
  sql_node->next = next;
  return sql_node;
}

struct sql_node * root;

%}
%start query
%union {
    struct sql_node * node;
    int number;
    char * text;
}

%type <node> query query_type select_query insert_query create_query update_query from_stmt into_stmt
%type <node> add_table_stmt table_name items columns values column_type column_name column_def column_defs condition set_value
%type <node> set_values identifier identifiers column_type_val drop_query delete_query

%%

%token QUERY SELECT INSERT UPDATE CREATE DELETE DROP
FROM IDENTIFIERS WHERE AND VALUES INTO SET TABLE TABLE_NAME STATEMENT TABLE_DEF ALL
TEXT_TYPE NUMBER_TYPE COLUMN_NAME SET_VALUE SET_VALUES CONDITION COLUMN_TYPE ITEMS COLUMN COLUMNS;

%token<text> IDENTIFIER;

query: query_type ';'
    {$$ = new_sql_node(QUERY, "query", $1, NULL);
    printf(CORRECT_SYNTAX_MESSAGE);
    root = $$;};

query_type: select_query {$$ = $1;};
            |
            update_query {$$ = $1;};
            |
            create_query {$$ = $1;};
            |
            insert_query {$$ = $1;};
            |
            drop_query {$$ = $1;};
            |
            delete_query {$$ = $1;};

select_query: SELECT items from_stmt
                {$$ = new_sql_node(SELECT, "select", $2, NULL);
                $$->first->next = $3;}
              |
              SELECT items from_stmt WHERE condition
                {$$ = new_sql_node(SELECT, "select", $2, NULL);
                $$->first->next = $3;
                $$->first->next->next = $5;};

insert_query: INSERT into_stmt columns VALUES '(' values ')'
                {$$ = new_sql_node(INSERT, "insert", $2, NULL);
                $$->first->next = $3;
                $$->first->next->next = $6;};
                |
                INSERT into_stmt VALUES '(' values ')'
                {$$ = new_sql_node(INSERT, "insert", $2, NULL);
                $$->first->next = $5;};

create_query: CREATE add_table_stmt
                {$$ = new_sql_node(CREATE, "create", $2, NULL);};

drop_query: DROP TABLE table_name
                {$$ = new_sql_node(DROP, "drop", $3, NULL);};

update_query: UPDATE table_name SET set_values WHERE condition
                {$$ = new_sql_node(UPDATE, "update", $2, NULL);
                struct sql_node *  set_values_node = new_sql_node(SET_VALUES, "set_values", $4, NULL);
                $$->next = set_values_node;
                 struct sql_node *  condition_node = new_sql_node(CONDITION, "condition", $6, NULL);
                $$->next->next = condition_node;};


delete_query: DELETE FROM table_name WHERE condition
                {$$ = new_sql_node(DELETE, "delete", $3, NULL);
                struct sql_node *  condition_node = new_sql_node(CONDITION, "condition", $5, NULL);
                $$->next = condition_node;
                };

from_stmt: FROM table_name
            {$$ = new_sql_node(FROM, "from", $2, NULL);};

into_stmt: INTO table_name
            {$$ = new_sql_node(INTO, "into", $2, NULL);};

add_table_stmt: TABLE table_name '(' column_defs ')'
                    {$$ = new_sql_node(TABLE, "table", $2, NULL);
                    struct sql_node *  node = new_sql_node(COLUMNS, "columns", $4, NULL);
                    $$->first->next = node;};

table_name: IDENTIFIER
                {$$ = new_sql_node(TABLE, $1, NULL, NULL);};

items: ALL { $$ = new_sql_node(ALL, "all", NULL, NULL);}
       | identifiers {$$ = new_sql_node(ITEMS, "values", $1, NULL);};

columns: '(' identifiers ')'
            {$$ = new_sql_node(COLUMNS, "columns", $2, NULL);};

values: identifiers
            {$$ = new_sql_node(VALUES, "values", $1, NULL);};

identifiers: identifier
                {$$ = $1;}
             | identifier ',' identifiers
                { $1->next = $3;};

identifier: IDENTIFIER
                {$$ = new_sql_node(IDENTIFIER, $1, NULL, NULL);};

column_type_val: NUMBER_TYPE
                    {$$ = new_sql_node(NUMBER_TYPE, "number", NULL, NULL);}
                 |
                 TEXT_TYPE
                    {$$ = new_sql_node(TEXT_TYPE, "text", NULL, NULL);};

column_type: column_type_val
                { $$ = new_sql_node(COLUMN_TYPE, "column_type", $1, NULL);};

column_name: identifier
                {$$ = new_sql_node(COLUMN_NAME, "column_name", $1, NULL);};

column_def:     column_name column_type
                    {$$ = new_sql_node(COLUMN, "column_def", $1, NULL);
                    $1->next = $2;};

column_defs: column_def
             |
             column_def ',' column_defs
                {$1->next = $3;}

condition: identifier '=' identifier
            {$$ = new_sql_node(CONDITION, "=", $1, NULL);
            $$->first->next = $3;};
            |
            identifier '>' identifier
            {$$ = new_sql_node(CONDITION, ">", $1, NULL);
             $$->first->next = $3;};
            |
            identifier '<' identifier
            {$$ = new_sql_node(CONDITION, "<", $1, NULL);
             $$->first->next = $3;};

set_value: identifier '=' identifier
            {$$ = new_sql_node(SET_VALUE, "=", $1, NULL);
            $$->first->next = $3;}

set_values: set_value
            |
            set_value ','  set_values
                {$$ = $1; $$->next = $3; }

%%

void print_sql_tree(struct sql_node * curr, int level) {
    if (curr == NULL) {
        return;
    }
    for(int i = 0; i < level; i++) printf("  ");
    printf("|_%s %d\n", curr->text, curr->node_type);
    print_sql_tree(curr->first, level + 1);
    print_sql_tree(curr->next, level);
}

int parse_string(const char* in, struct sql_node * node) {
  set_input_string(in);
  int rv = yyparse();
  *node = *root;
  printf("\n");
  end_lexical_scan();
  return rv;
}

main_1()
{
        yyparse();
}