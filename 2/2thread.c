// Kristin Tong
// Sept 30, 2022
// Lab 2 - Processes and threads
// creating two pthreads instead of forking
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <pthread.h>     /* thread */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function with command-line arguments to pass */
void *thread1();
void* thread2();

int main(int argc, char *argv[]) {
    pthread_t  tid1, tid2;
    printf("\n Before threading.\n");
   //create thread 1 and thread 2
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);
    //wait for thread1 to execute then wait for thread2 to execute
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL); 
    //end thread
    //pthread_exit(NULL);
    printf("\n After threading. \n");
    return 0;
}
void* thread1() {
        // Child process
        int i;
	for (i=0;i<100;i++) {
            printf("Child thread %d",i);
            usleep(30000);
        }
    return 0;
}

void* thread2() {
	int i;
	for(i=0;i<100;i++){
		printf("\t\t Parent thread %d\n",i);
		usleep(30000);
	}
	return 0;
}
