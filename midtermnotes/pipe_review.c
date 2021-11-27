#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2], n;
    char buff[100];

    if (pipe(pipefd) < 0) { printf("\n Error: pipe error\n"); }

    printf("\nRead fd = %d, write fd=%d\n", pipefd[0], pipefd[1]);
    if (write(pipefd[1], "Hello World\n", 12) != 12) { printf("\nPipe write error\n"); }
    if ( (n = read(pipefd[0], buff, sizeof(buff))) <= 0 ) {  printf("\nPipe read error\n"); }

    write(1, buff, n); /** fd 1 = stdout **/
    printf("%s", buff);
    exit(0);
}