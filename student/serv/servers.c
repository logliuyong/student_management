#include<stdio.h>
#include<ctype.h>
#include"server.h"
#include<stdlib.h>
#include<sys/wait.h>
int main(void){
    int sfd,cfd;

    sfd=t_listen(6000,5);
    while(1){
        cfd=t_accept(sfd);

       pid_t pid=fork();
       if(pid==-1){
           perror("fork");
          return -1;
       }
       if(pid==0){
           close(sfd);
           doit(cfd);
           close(cfd);
           exit(0);
       }else{
          close(cfd);
          waitpid(-1,NULL,WNOHANG);
       }
    }
   return 0;
}
