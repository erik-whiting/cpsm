#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/shm.h>

#define SHM_KEY 0x1000

int main() {
    int shmid, status;
    static char data = 'A';
    shmid = shmget(SHM_KEY, sizeof(char), 0644|IPC_CREAT);
    char *sh_mem = (char *) shmat(shmid, NULL, 0);

    for (int i = 1; i <= 26; i++) {
        memmove(sh_mem, &data, data);
        printf("sh_mem: %p\n", sh_mem);
        // printf("data: %s\n", &data);
        sh_mem++;
        data++;
    }

    pid_t proc = fork();
    if (proc == 0) {
        // I really can't figure this out
        char read_data;
        sh_mem--;
        printf("Before loop:\n");
        printf("sh_mem is: %p\n", sh_mem);
        for (int i = 26; i >= 1; i--) {
            printf("(from loop) sh_mem is: %p\n", sh_mem);
            sh_mem--;
        }
        exit(EXIT_SUCCESS);
    } else {
        // No op
    }

    shmdt(sh_mem);
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
