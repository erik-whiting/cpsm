#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
// #include "unpipc.h"

// This doesn't compile
#define	MAXNITEMS   1000
#define	MAXNTHREADS 100

int nitems;
struct {
    pthread_mutex_t mutex;
    int buff[MAXNITEMS];
    int nput; // Next index to store
    int nval; // Next value to store
} shared = { PTHREAD_MUTEX_INITIALIZER };

void *produce(void *), *consume(void *);

int main(int argc, char *argv) {
    int i, nthreads, count[MAXNTHREADS];
    pthread_t tid_produce[MAXNTHREADS], tid_consume;

    if (argc != 3) {
        err_quit("Usage: filename <#items> <#threads>\n");
    }

    nitems = min(atoi(argv[1]), MAXNITEMS)
    nthreads = min(atoi(argv[2]), MAXNTHREADS);

    set_concurrency(nthreads + 1);
    // Create all proucers and one consumer
    for (i = 0; i < nthreads; i++) {
        count[i] = 0;
        pthread_create(&tid_produce[i], NULL, produce, &count[i]);
    }

    // Wait for all producers
    for (i = 0; i < nthreads; i++) {
        pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }

    pthread_create(&tid_consume, NULL, consume, NULL);
    pthread_join(tid_consume, NULL);

    exit(0);
}

void *produce(void *arg) {
    for (;;) {
        pthread_mutex_lock(&shared.mutex);
        if (shared.nput >= nitems) {
            // buffer is full
            pthread_mutex_unlock(&shared.mutex);
            return(NULL); // because we're done
        }
        // buffer is not full
        shared.buff[shared.nput] = shared.nval;
        shared.nput++;
        shared.nval++;
        pthread_mutex_unlock(&shared.mutex);
        *((int *) arg) += 1;
    }
}

void *consume(void *arg) {
    int i;
    for (i = 0; i < nitems; i++) {
        if (shared.buff[i] != i) {
            printf("buff[%d] = %d\n", i, shared.buff[i]);
        }
        return(NULL);
    }
}
