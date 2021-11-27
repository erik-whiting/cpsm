#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "menu.h"
#include "messageQueueFeature.h"
#include "sharedMemFeature.h"
#include "semaphoreFeature.h"
#include "socketFeature.h"

int main() {
    int selection = makeSelection();
    printf("You picked %d\n", selection);
    char command[30];
    sprintf(command, "./consumer %d", selection);
    printf("I will run this command: %s\n", command);

    int proc = fork();
    if (proc == 0) {
        if (selection == 1) {
            // Pipe
            system(command);
        } else if (selection == 2) {
            // Message Queue
            writeMessage();
            system(command);
        } else if (selection == 3) {
            // Shared memory
            writeSharedMem();
            system(command);
        } else if (selection == 4) {
            // Semaphore
            writeSem();
        } else if (selection == 5) {
            // Socket
            writeToSocket();
            sleep(1);
            system(command);
        }
    } else {
        // Wait for child
        waitpid(proc, 0, 0);
    }

    return 0;
}
