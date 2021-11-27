#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("Tell me a program to run (pg1, pg2, or pg3, or /bin/ls, bin/du etc): ");
    char userInput[20];
    scanf("%s", userInput);
    int t = fork();
    if (t > 0) {
        int childStatus;
        printf("Parent started\n");
        waitpid(t, &childStatus, 0);
        printf("Parent exiting\n");
    } else {
        printf("Child started\n");
        execl(userInput, ".", (char*) NULL);
        printf("Child exiting");
        exit(1);
    }
    printf("Main program exiting\n");
    return 0;
}
