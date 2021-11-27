#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define NLOOP 500

int counter;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
void *doit(void *);

int main() {
    pthread_t tidA, tidB;
    pthread_create(&tidA, NULL, &doit, NULL);
    pthread_create(&tidB, NULL, &doit, NULL);
    // wait for threads to terminate
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);
}

void *doit(void *vptr) {
    int i, val;
    /*
       Each thread fetches, prints, and increments the counter NLOOP times
       The value of the counter should increase monotonically
    */
    for (i = 0; i < NLOOP; i++) {
        pthread_mutex_lock(&counter_mutex);
        val = counter;
        printf("%ld: %d\n", pthread_self(), val + 1);
        counter = val + 1;
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}
