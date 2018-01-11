#include <stdio.h>
#include <string.h>
#include "client.h"
int t_connect(char *address,int port){
    SA4 serv;
    //创建一个socket设备
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1){
        perror("socket");
        return -1;
    }
    //需要初始化serv
    serv.sin_family=AF_INET;
    serv.sin_port=htons(port);
    //127.0.0.1   text<-->binary
    inet_pton(AF_INET,address,\
            &serv.sin_addr);
    //在socket上发起连接向服务器
    int c=connect(sfd,\
        (SA *)&serv,\
        sizeof(serv));
    if(c==-1){
        perror("connect");
        return -1;
    }
    return sfd;
}
int main(int argc,char *argv[]){
   int sfd=t_connect(argv[1],6000);
   if(sfd==-1){
     printf("链接服务器失败，请检查网络！\n");
     return -1;
   }
        mystudent(sfd);
    //关闭本次连接
    close(sfd);
    return 0;
}
