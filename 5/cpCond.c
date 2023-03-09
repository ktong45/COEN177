// Kristin Tong
// Oct 27, 2022
// Lab 5: Synchronization
// Step 4 - Consumer Producer using condition variables

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>

#define NTHREADS 10
#define n 10
pthread_t threads[NTHREADS];

pthread_mutex_t lock;
pthread_cond_t full;
pthread_cond_t empty;

int buffer[n];
int in;
int out;
int used;

//Producer thread
void* producer(void* arg) {
    int item;
    do { 
        // produce next item
        item = rand() % 20;
        // enter CR
        pthread_mutex_lock(&lock);
        while (used >= n)
            pthread_cond_wait(&empty, &lock);

        // add the item to buffer
        buffer[in] = item;
        sleep(1);
        printf("%d producing %d \n", (int)arg, item);
        in = (in + 1) % n;
        used++;
        // exit CR
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&lock);
    } while (1);
}

//Consumer thread
void* consumer(void* arg) {
    int item;
    do { 
        // enter CR
        pthread_mutex_lock(&lock);
        while (used <= 0)
            pthread_cond_wait(&full, &lock);
        
        // remove next item from buffer
        item = buffer[out];
        sleep(1);
        printf("\t\t %d consuming %d", (int)arg, item);
        out = (out + 1) % n;        
        used--;
        // signal empty buffer
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);

    } while (1);
}

int main() {
    int i;
    srand(time(NULL));
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    if(pthread_mutex_init(&lock, NULL) != 0) {
        printf("mutex init failed... \n");
        return 1;
    }

    // half producer and half consumer threads
    for(i=0; i<NTHREADS; i++){
        if(i < (NTHREADS/2))
                pthread_create(&threads[i], NULL, producer, (void *)(size_t)i);
        else
                pthread_create(&threads[i], NULL, consumer, (void *)(size_t)i);
    }

    for(i=0; i<NTHREADS; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    return 0;
}