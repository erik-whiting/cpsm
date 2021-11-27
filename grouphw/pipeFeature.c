#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pipeFeature.h"
#include "messageQueueFeature.h"

void talkWithPipes() {
    int fd[2];
    if (pipe(fd) == -1) {
        printf("An error occured opening the pipe\n");
        exit(1);
    }

    int pid = fork();
    if (pid == -1) {
        printf("An error occured while forking\n");
        exit(2);
    }

    if (pid == 0) {
        close(fd[0]); // Close read end of pipe
        char message[100];
        printf("Please enter a message under 100 characters\n");
        scanf("%s", message);
        printf("Writing message ...\n");
        if (write(fd[1], message, sizeof(message)) == -1) {
            printf("An error occred while writing pipe\n");
            exit(3);
        }
        close(fd[1]);
    } else {
        close(fd[1]); // Close write end of pipe
        char payload[100];
        if (read(fd[0], payload, sizeof(payload)) == -1) {
            printf("An error occursed while reading pipe\n");
            exit(4);
        }
        close(fd[0]);
        printf("Data from pipe:\n");
        printf("%s\n", payload);
    }
}
