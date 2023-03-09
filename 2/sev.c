// Kristin Tong
// COEN 177
// Lab 2 - seven processes
// creating exactly seven processes (including parent process)
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
	printf("parent pid	%d\n", getpid());
	//1st fork -> child 1
	if(fork() == 0){
		//2nd fork -> children 1.1 & 1.2
		if(fork() == 0)
		{	printf("p1.1 pid %d ppid %d\n", getpid(), getppid());
			exit(0);
		}
		else{
			if(fork() ==0){
				printf("p1.2 pid %d ppid %d\n", getpid(), getppid());
				exit(0);
			}else{
				printf("p1 pid %d ppid %d\n", getpid(), getppid());
				exit(0);
			}
		}
	}else{
		//second fork -> child 2
		if(fork() ==0){
		//fork again children 2.1 & 2.2
			if(fork() ==0){
				printf("p2.1 pid %d ppid %d\n", getpid(), getppid());
				exit(0);
			}else{
				if(fork() ==0){
					printf("p2.2 pid %d ppid %d\n", getpid(), getppid());
					exit(0);		
				}
			}
		}else{
			printf("p2 pid %d ppid %d\n", getpid(), getppid());
		}
	}
	return 0;
}
