#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "messageQueueFeature.h"

struct msgBuffer {
    long msgType;
    char msgText[100];
} message;

void writeMessage() {
    key_t key;
    int msgId;

    key = ftok("mq", 65);
    msgId = msgget(key, 0666 | IPC_CREAT);
    message.msgType = 1;

    printf("Please enter a message under 100 characters\n");
    scanf("%s", message.msgText);

    msgsnd(msgId, &message, sizeof(message), 0);
    printf("Sent message: %s\n", message.msgText);
}

void readMessage() {
    key_t key;
    int msgId;

    key = ftok("mq", 65);
    msgId = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgId, &message, sizeof(message), 1, 0);
    printf("Received data: \n%s\n", message.msgText);

    msgctl(msgId, IPC_RMID, NULL);
}
