#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 80
#define PORT 9090
#define SA struct sockaddr
int sockfd;

int send_message_size(uint32_t size) {
    write(sockfd, &size, sizeof(uint32_t));
    printf("the size of message was send: (%d) bytes\n", size);
    //return 0;
}

int send_message(char *message, uint32_t size) {
    write(sockfd, message, size);
    printf("The message was send\n");
    printf("%s\n", message);
    //return 0;
}

int send_and_receive(char *message) {
    uint32_t size = (int) strlen(message);
    send_message_size(size);
    send_message(message, size);

    char buff[MAX];
    read(sockfd, buff, sizeof(buff));
    printf("From Server : %s", buff);

    //return 0;

}

int initialize_client() {
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    } else
        printf("connected to the server..\n");

    // close the socket
    //close(sockfd);
}
