
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#include "sharedMemFeature.h"

void writeSharedMem() {
    char message[100];
    printf("Please enter a message under 100 characters\n");
    scanf("%s", message);
    
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*) 0, 0);
    shmdt(str);
}

void readSharedMem() {
    key_t key =  ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*) 0, 0);
    printf("Received data: %s\n", str);
    
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
}