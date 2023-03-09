// Kristin Tong
// Oct. 12, 2022
// Lab 3 - Pthreads and ICP (Pipes)
// Step 5 - implement producere-consumer message communicatino using pipes

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main( int argc, char *argv[]) {
    int fds[2];
    char buff[60];
    int count, i;
    pipe(fds);

    //first child process closes reader and writes to pipe
    if(fork()==0){
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        close(fds[0]);
        //all strings in commandline args added to buffer
        for(i=1;i<argc;i++){
            strcat(buff,argv[i]);
        }
        //write from fds[1] to buffer
        write(fds[1],buff,strlen(buff));
        exit(0);
    //second child process closes writer and reads from pipe
    } else if(fork()==0){
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);

        //read from fds[0] from buffer
        while((count=read(fds[0],buff,60))>0 ){
                read(fds[0],buff,60);
                printf("%s",buff);
        }
        
        printf("\n");

        exit(0);
    } else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}