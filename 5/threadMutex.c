// Kristin Tong
// Oct 27, 2022
// Lab 5: Synchronization
// Step 2 - Using mutex to replace a semaphore

// Thread Sychronization
//To compile this code:
//If using the SCU Linux lab first add #include<fcntl.h>
//Then you're ready to compile.
//To compile just add -lpthread to your gcc command like:
//gcc threadSync.c -lpthread
//gcc threadSync.c -o test -lpthread

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock; 

void* go(void* arg) { 
  //entry section
   pthread_mutex_lock(&lock);
  //critical section
  printf("Thread %d Entered Critical Section..\n", (int)arg); 
   sleep(1); 
   //exit section
   pthread_mutex_unlock(&lock);
  return (NULL);
} 

int main() { 
   if(pthread_mutex_init(&lock, NULL) != 0) {
      printf("mutex init has failed... \n");
      return 1;
   }
   static int i;
   for (i = 0; i < NTHREADS; i++)  
      pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
   for (i = 0; i < NTHREADS; i++) {
      pthread_join(threads[i],NULL);
      printf("\t\t\tThread %d returned \n", i);
      }
   printf("Main thread done.\n");
   pthread_mutex_destroy(&lock);
   return 0; 
} 
