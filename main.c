#include <stdio.h>
#include <wjelement.h>
#include <stdbool.h>
#include "sql_lexical_analyzer/lex.yy.h"
#include "json/json_serialization_module.h"
#include "client/client_linux.h"
#include "server/server_linux.h"

int main(int argc, char **argv) {
    if (strcmp("server", argv[1]) == 0) {
        if (argc != 3) {
            printf("start program with params \"server\" <filename>\n");
            exit(0);
        }
        server_linux(argv[2]);
    }
    if (strcmp("client", argv[1]) == 0) {
        initialize_client();
        bool quit = 0;
        while (!quit) {
            size_t command_capacity = 0;
            char *command = NULL;

            printf("> ");
            fflush(stdout);

            ssize_t was_read = getline(&command, &command_capacity, stdin);
            if (was_read <= 0) {
                free(command);
                break;
            }

            struct sql_node *node = malloc(sizeof(struct sql_node));
            int status = parse_string(command, node);

            if (status != 1) {
                char *json_string = sql_node_to_json_string(node);
                WJElement response = NULL;
                send_and_receive(json_string, &response);
                handle_response(response);
            } else {
                printf("The syntax of command is invalid\n");
            }
        }
        return 1;
    }
}
