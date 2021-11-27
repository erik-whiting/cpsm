#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define NLOOP 500
int counter;

void *doit(void *);

int main() {
    pthread_t tidA, tidB;

    pthread_create(&tidA, NULL, &doit, NULL);
    pthread_create(&tidB, NULL, &doit, NULL);

    // Wait for threads to terminate
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);
    exit(0);
    return 0;
}

void *doit(void *vptr) {
    int i, val;
    /*
       Each thread fetches, prints, and increments the counter NLOOP times
       The value of the counter should increase monotonically
    */
    for (i = 0; i < NLOOP; i++) {
        val = counter;
        printf("%ld: %d\n", pthread_self(), val + 1);
        counter = val + 1;
    }
    /*
       Note that the counter variable isn't being locked so
       sometimes one thread will print a value that's already
       been printed by another
    */
    return NULL;
}
