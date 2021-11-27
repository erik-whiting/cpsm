#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#include "semaphoreFeature.h"

sem_t semaphore;

void* routine(void* args) {
    sem_wait(&semaphore);
    printf("This message is from the semaphore:\n");
    printf("%s\n", (char*) args);
    sem_post(&semaphore);
    free(args);
}

void writeSem() {
    char message[100];
    printf("Please enter a message under 100 characters\n");
    scanf("%s", message);
    
    pthread_t th;
    sem_init(&semaphore, 0, 1);
    pthread_create(&th, NULL, &routine, message);
    sleep(1);
    pthread_join(th, NULL);
    sem_destroy(&semaphore);
}

void readSem() {
    printf("Not implemented\n");
}
