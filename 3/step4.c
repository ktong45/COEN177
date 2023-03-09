// Kristin Tong
// Oct. 12, 2022
// Lab 3 - Pthreads and ICP (Pipes)
// Step 4 - shell program for cat /etc/passwd | grep root

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char *argv[]) {
    int fds[2];
    pipe(fds);

    if(fork()==0){
        dup2(fds[0],0);
        close(fds[1]);

        //include /bin/grep/as file source 
        execlp("/bin/grep", "grep", "root", 0);
    }
    else if(fork()==0){
        dup2(fds[1],1);
        close(fds[0]);
        //include bin/cat as file source
        execlp("/bin/cat","cat","/etc/passwd",0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}