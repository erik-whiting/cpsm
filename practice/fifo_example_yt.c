#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    // Problem is pipes can only be used by
    // programs in same hierarchy.
    // FIFO are filetypes which you can read
    // or write from any process.
    // Is called a "named pipe."
    if (mkfifo("myfifo1", 0777) == -1) {
        if (errno != EEXIST) { // The red squiggles here are wrong
            printf("Could not create fifo file\n");
        return 1;
        }
    }

    // Have to open FIFO too
    printf("Opening FIFO\n");
    int fd = open("myfifo1", O_WRONLY);
    printf("Opened FIFO\n");
    int x = 97;
    if (write(fd, &x, sizeof(x)) == -1) {
        printf("Error at write");
        return 2;
    }
    printf("Written\n");
    close(fd);
    printf("Closed\n");

    return 0;
}
