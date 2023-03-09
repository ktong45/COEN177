// Kristin Tong
// Oct 27, 2022
// Lab 5: Synchronization
// Step 3 - Consumer producer problem with semaphores

//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool
//empty and full count the number of empty and full buffers
//Initially: full = 0, empty = n, mutex  = 1

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

#define NTHREADS 10
#define n 10
pthread_t threads[NTHREADS];
sem_t *full;  // 0
sem_t *empty; // n
sem_t *mutex; // 1

int buffers[n];
int in = 0;
int out = 0;

//Producer thread
void* producer(void* arg) {
    int item;
    do { 
        // produce next item        
        item = rand() % 20;
        sleep(1);
        printf("%d producing %d \n", (int)arg, item);
        sleep(1);
        //enter CR
        sem_wait(empty);
        sem_wait(mutex);
        // add the item to buffer (and move index)
        buffers[in] = item;
        in = (in+1) % n;
        //exit CR
        sem_post(mutex);
        sem_post(full);
    } while (1);
}
//Consumer thread
void* consumer(void *arg) {
    int item;
    do { 
        //enter CR
        sem_wait(full);
        sem_wait(mutex);
        // remove next item from buffer
        item = buffers[out];
        out = (out+1) % n;
        //exit CR
        sem_post(mutex);
        sem_post(empty);
        // consume the item
        sleep(1);
        printf("\t\t %d consuming %d \n", (int)arg, item);
        sleep(1);
    } while (1);
}

int main() {
    int i;
    sem_unlink("full");
    sem_unlink("empty");
    sem_unlink("mutex");
    
    srand(time(NULL));

	full = sem_open("full", O_CREAT, 0644, 0);
	empty = sem_open("empty", O_CREAT, 0644, n);
	mutex = sem_open("mutex", O_CREAT, 0644, 1);
    
    // create half producer threads and half consumer threads
    for(i=0; i<NTHREADS; i++){
        if(i < (NTHREADS/2))
            pthread_create(&threads[i], NULL, producer, (void *)(size_t)i);
        else
            pthread_create(&threads[i], NULL, consumer, (void *)(size_t)i);
    }

    // join threads
    for(i =0; i<NTHREADS; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}