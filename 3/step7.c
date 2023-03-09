// Kristin Tong
// Oct. 12, 2022
// Lab 3 - Pthreads and ICP (Pipes)
// Step 7 - fixing step 6 code

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    //must change the i to a universal pointer to a size_t type
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    
    for (i = 0; i < NTHREADS; i++) {
	    printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
    //must cast to integer and use size_t pointer to keep track of same variable
 printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), (int) (size_t *)arg);
 return 0;
}


