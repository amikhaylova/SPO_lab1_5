#ifndef SPO_LAB1_5_CLIENT_LINUX_H
#define SPO_LAB1_5_CLIENT_LINUX_H

int initialize_client();
int send_and_receive(char * message_to_send, WJElement * response);
void handle_response(WJElement response);
void handle_response_interface(WJElement response, char * output);

#endif //SPO_LAB1_5_CLIENT_LINUX_H
