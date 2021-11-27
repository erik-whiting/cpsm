#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // pipe(fileDescriptor1, fileDescriptor2);

    int fd[2];
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1) {
        printf("An error occured with opening the pipe\n");
        return 1;
    }

    int id = fork();
    if (id == -1) {
        printf("Something went wrong with forking");
        return 4;
    }

    if (id == 0) {
        // As user to input number
        // send to parent from child
        close(fd[0]); // Close the read end of pipe
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1) {
            printf("Something went wrong with writing");
            return 2;
        }
        close(fd[1]);
    } else {
        close(fd[1]); // Close the write end of pipe
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1) {
            printf("Soemething went wrong with reading");
            return 3;
        }
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }

    return 0;
}
