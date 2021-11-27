#include <stdio.h>
// After reading popen() documentation, I've realized that it's not
// what I want. Ditching this program in the middle of working with
// it, so nothing here should be assumed to be the correct way to
// do anything.

int main(int argc, char *argv[]) {
    // pipe(fileDescriptor1, fileDescriptor2);

    int fd[2];
    // fd[0] - read
    // fd[1] - write
    if (popen(fd, ) == -1) {
        printf("An error occured with opening the pipe\n");
        return 1;
    }

    int id = fork();

    if (id == 0) {
        // As user to input number
        // send to parent from child
        // close(fd[0]); // Close the read end of pipe. Necessary with popen?
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        fwrite(&x, sizeof(int), sizeof(int), fd[1]);
        // fwrite(fd[1], &x, sizeof(int));
        pclose(fd[1]);
    } else {
        // close(fd[1]); // Close the write end of pipe. Necessary with popen?
        int y;
        fread(&y, sizeof(int), sizeof(int), fd[0]);
        // fread(fd[0], &y, sizeof(int));
        pclose(fd[0]);
        printf("Got from child process %d\n", y);
    }

    return 0;
}
