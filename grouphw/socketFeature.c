#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include "socketFeature.h"

#define PORT 5000

void writeToSocket() {
    char message[100];
    printf("Please enter a message under 100 characters\n");
    scanf("%s", message);

    int listenfd = 0, connection = 0;
    struct sockaddr_in serv_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    // Zero out server address
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);

    while(1) {
        connection = accept(listenfd, (struct sockaddr*) NULL, NULL);
        write(connection, message, strlen(message));

        close(connection);
        sleep(1);
    }
}

void readFromSocket() {
    int reader = 0, n = 0;
    struct sockaddr_in server;
    char message[100];

    reader = socket(AF_INET, SOCK_STREAM, 0);
    // Memset message buffer
    memset(message, '0', sizeof(message));
    memset(&server, '0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    
    // Translate IP address
    inet_pton(AF_INET, "127.0.0.0", &server.sin_addr);

    connect(reader, (struct sockaddr *) &server, sizeof(server));

    while ( (n = read(reader, message, sizeof(message)-1)) > 0 ) {
        fputs(message, stdout);
    }
}