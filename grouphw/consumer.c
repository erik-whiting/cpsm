#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pipeFeature.h"
#include "messageQueueFeature.h"
#include "sharedMemFeature.h"
#include "socketFeature.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Something went wrong\n");
    }
    
    char input;
    sprintf(&input, "%s", argv[1]);

    if (input == '1') { talkWithPipes(); }
    if (input == '2') { readMessage(); }
    if (input == '3') { readSharedMem(); }
    if (input == '5') { readFromSocket(); }

    return 0;
}
