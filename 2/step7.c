// Kristin Tong
// Sept 30, 2022
// Lab 2 - Processes and threads
// using system calls in processes
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }else if(pid ==0){
        execlp("/bin/ls","ls", NULL);
    }else{
    	wait(NULL);
	printf("Child complete");
	exit(0);
    }
    return 0;
}
