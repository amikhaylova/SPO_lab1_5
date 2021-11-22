
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wjelement.h>


#define MAX 512
#define PORT 9090
#define SA struct sockaddr
int clientSocket;

void readXBytes(int socket, unsigned int x, void *buffer) {
    int bytesRead = 0;
    int result;
    while (bytesRead < x) {
        result = read(socket, buffer + bytesRead, x - bytesRead);
        if (result < 1) {
            // Throw your error.
        }

        bytesRead += result;
        printf("%d\n", bytesRead);
    }
}

// Function designed for chat between client and server.
void receive_and_send(int sockfd) {
    char buff[MAX];
    int n;
    bzero(buff, MAX);
    uint32_t size_buf[1];
    printf("want to read something \n");
    read(sockfd, size_buf, sizeof(size_buf));
    uint32_t size = *size_buf;
    printf("I have to read  %d bytes\n", size);
    readXBytes(sockfd, size, buff);
    printf("Text from client: %s\n", buff);
    WJElement wjelement = WJEParse(buff);
    char * command = WJEStringF(wjelement, WJE_GET, NULL, NULL, "query-type");
    printf("COMMAND = %s\n", command);
    // WJElement columns_array = WJEArrayF(wjelement, WJE_GET, NULL, NULL, "selected-columns");

    WJElement person = NULL;
    int x = 0;
    person = WJEArrayF(wjelement, WJE_GET, &person, "selected-columns");
    char * column = NULL;
    while ((column = WJEStringF(person, WJE_GET, NULL, NULL, "[%d]", x))) {
        printf("%s \n", column);
        x++;
    }
}

// Driver function
int server_linux() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *) &servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *) &cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    } else
        printf("server accept the client...\n");

    // Function for chatting between client and server
    receive_and_send(connfd);

    // After chatting close the socket
    close(sockfd);
}
