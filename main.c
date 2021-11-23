#include <stdio.h>
#include <wjreader.h>
#include <wjwriter.h>
#include <wjelement.h>

#include "tableStorage/TableStorage.h"
#include "sql_grammar/y.tab.h"
#include "sql_lexical_analyzer/lex.yy.h"
#include "json/json_serialization_module.h"
#include "client/client_linux.h"
#include "server/server_linux.h"

int main(int argc, char **argv) {
   /* for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }*/
    if (strcmp("server", argv[1]) == 0) {
        //init_server();
        server_linux();
    }
    if (strcmp("client", argv[1]) == 0) {
        /*char ** argv1 = malloc(sizeof(argv));
        argv1[0] = argv[2];
        argv1[1] = argv[3];
        //init_client(2, argv1);
        initialize_connect_socket(2, argv1);
        char line[1024];
        scanf("%[^\n]", line);
        printf("%s\n", line);
        struct sql_node * node = malloc(sizeof(struct sql_node));
        parse_string(line, node);
        WJElement json_object = get_json_object(node);
        char * json_string = WJEToString(json_object, TRUE);
        send_and_receive(json_string);*/
        initialize_client();
        char line[1024];
        bool quit = 0;
        while (!quit) {
            size_t command_capacity = 0;
            char * command = NULL;

            printf("> ");
            fflush(stdout);

            ssize_t was_read = getline(&command, &command_capacity, stdin);
            if (was_read <= 0) {
                free(command);
                break;
            }

            struct sql_node * node = malloc(sizeof(struct sql_node));
            int status = parse_string(command, node);

            if (status != 1){
                char * json_string = sql_node_to_json_string(node);
                send_and_receive(json_string);
            }else{
                printf("The syntax of command is invalid\n");
            }
        }

        return 1;
    }


    // printf(argv[0]);
    //char *filename = argv[1];
    /*db_init(filename);
    ColumnMetaData columns[] = {{
                                    .type = COLUMN_TYPE_TEXT,
                                    .is_key = 1,
                                    .is_required = 1},
                                {
                                    .type = COLUMN_TYPE_INT,
                                    .is_key = 0,
                                    .is_required = 1}};
    strcpy(columns[0].name, "id");
    strcpy(columns[1].name, "name");

    create_table("test", 2, columns);
    create_table("test1", 2, columns);
    InsertEntry entry[] = {{"id",  "1"},
                           {"name", "hello"}};
    insert_into_table("test", 2, entry);*/

    /*struct sql_node * node = malloc(sizeof(struct sql_node));
    printf("create table bla (id number, name text, text1 text) ;\n");
    parse_string("create table bla (id number, name text, text1 text) ;", node);
    print_sql_tree(node, 0);
    get_json_object(node);

    struct sql_node *node1 = malloc(sizeof(struct sql_node));
    printf("select a from bla where a=1;\n");
    parse_string("select a from bla where a=1;", node1);
    print_sql_tree(node1, 0);
    get_json_object(node1);

    struct sql_node *node10 = malloc(sizeof(struct sql_node));
    printf("select * from bla;\n");
    parse_string("select * from bla;", node10);
    print_sql_tree(node10, 0);
    get_json_object(node10);

    struct sql_node *node2 = malloc(sizeof(struct sql_node));
    printf("UPDATE abc SET b=1,a=1 WHERE id=1;\n");
    parse_string("UPDATE abc SET b=1,a=1 WHERE id=1;", node2);
    print_sql_tree(node2, 0);
    get_json_object(node2);

    //INSERT into_stmt columns VALUES '(' values ')'
    struct sql_node *node3 = malloc(sizeof(struct sql_node));
    printf("INSERT INTO bla (a, b) VALUES (1, 2);\n");
    parse_string("INSERT INTO bla (a, b) VALUES (1, 2);", node3);
    print_sql_tree(node3, 0);
    get_json_object(node3);

    //DROP TABLE bla
    struct sql_node *node4 = malloc(sizeof(struct sql_node));
    printf("DROP TABLE bla;\n");
    parse_string("DROP TABLE bla;", node4);
    print_sql_tree(node4, 0);
    WJElement element =  get_json_object(node4);
    char * json_string = WJEToString(element, TRUE);
    printf("%s", json_string);

    //DELETE FROM table_name WHERE condition;
    struct sql_node *node5 = malloc(sizeof(struct sql_node));
    printf("DELETE FROM bla WHERE id<1;\n");
    parse_string("DELETE FROM bla WHERE id<1;", node5);
    print_sql_tree(node5, 0);
    get_json_object(node5);

    //INSERT into_stmt VALUES '(' values ')'
    struct sql_node *node6 = malloc(sizeof(struct sql_node));
    printf("INSERT INTO bla VALUES (1, 2);\n");
    parse_string("INSERT INTO bla VALUES (1, 2);", node6);
    print_sql_tree(node6, 0);
    get_json_object(node6);*/

    /* //DROP TABLE bla
     struct sql_node *node4 = malloc(sizeof(struct sql_node));
     printf("DROP TABLE bla;\n");
     parse_string("DROP TABLE bla;", node4);
     print_sql_tree(node4, 0);
     WJElement element =  get_json_object(node4);
     char * json_string = WJEToString(element, TRUE);
     printf("%s", json_string);
     */

    /*   //CREATE
       struct sql_node * node = malloc(sizeof(struct sql_node));
       printf("create table bla (id number, name text, text1 text) ;\n");
       parse_string("create table bla (id number, name text, text1 text) ;", node);
       print_sql_tree(node, 0);
       WJElement element =  get_json_object(node);
       char * json_string = WJEToString(element, TRUE);
       printf("%s", json_string);*/
/*
    //SELECT WITHOUT WHERE
    struct sql_node *node10 = malloc(sizeof(struct sql_node));
    printf("select col1, col2 from bla;\n");
    parse_string("select col1, col2 from bla;", node10);
    print_sql_tree(node10, 0);
    WJElement element =  get_json_object(node10);
    char * json_string = WJEToString(element, TRUE);
    printf("%s", json_string);*/

    /* //SELECT WITH WHERE
     struct sql_node *node1 = malloc(sizeof(struct sql_node));
     printf("select a from bla where a=1;\n");
     parse_string("select a from bla where a=1;", node1);
     print_sql_tree(node1, 0);
     get_json_object(node1);
     WJElement element =  get_json_object(node1);
     char * json_string = WJEToString(element, TRUE);
     printf("%s", json_string);*/

    /*  //UPDATE
      struct sql_node *node2 = malloc(sizeof(struct sql_node));
      printf("UPDATE abc SET b=1,a=1 WHERE id=1;\n");
      parse_string("UPDATE abc SET b=1,a=1 WHERE id=1;", node2);
      print_sql_tree(node2, 0);
      get_json_object(node2);
      WJElement element =  get_json_object(node2);
      char * json_string = WJEToString(element, TRUE);
      printf("%s", json_string);*/

    /* //INSERT into_stmt VALUES '(' values ')'
     struct sql_node *node6 = malloc(sizeof(struct sql_node));
     printf("INSERT INTO bla (col1, col2) VALUES (1, 2);\n");
     parse_string("INSERT INTO bla (col1, col2)  VALUES (1, 2);", node6);
     print_sql_tree(node6, 0);
     WJElement element =  get_json_object(node6);
     char * json_string = WJEToString(element, TRUE);
     printf("%s", json_string);*/

    //DELETE FROM table_name WHERE condition;
    /*struct sql_node *node5 = malloc(sizeof(struct sql_node));
    printf("DELETE FROM bla WHERE id<1;\n");
    parse_string("DELETE FROM bla WHERE id<1;", node5);
    print_sql_tree(node5, 0);
    WJElement element =  get_json_object(node5);
    char * json_string = WJEToString(element, TRUE);
    printf("%s", json_string);*/

    // return 0;
}
