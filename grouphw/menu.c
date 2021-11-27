#include "menu.h"
#include <stdio.h>

int getUserInput() {
    int input = 0;
    while (input < 1 || input > 5) {
        printf("Select number between 1 and 5: ");
        scanf("%d", &input);
    }
    return input;
}

int makeSelection() {
    printf("Please select what IPC to use:\n");
    printf("1 - Pipe\n");
    printf("2 - Message Queue\n");
    printf("3 - Shared Memory\n");
    printf("4 - Semaphore\n");
    printf("5 - Sockets\n");

    int userInput = getUserInput();
    switch(userInput) {
        case 1:
            printf("Pipe\n");
            break;
        case 2:
            printf("Message Queue\n");
            break;
        case 3:
            printf("Shared Memory\n");
            break;
        case 4:
            printf("Semaphore\n");
            break;
        case 5:
            printf("Socket\n");
            break;
    }

    return userInput;
}
