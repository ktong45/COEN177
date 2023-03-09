// Kristin Tong
// Oct. 12, 2022
// Lab 3 - Pthreads and ICP (Pipes)
// Step 3 - using dup2() and redirecting streams

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
       close(fds[0]);
       //close file desc reader
       //redirect the writing fds[1] call it 1
       dup2(fds[1],1);
       execlp("ls","ls",0);

       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);

       dup2(fds[0],0);

       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
               write(1,"",1);
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}