#include <stdio.h>
#include "server.h"
#include<string.h>

int t_listen(int port,int backlog){
    int sfd;
    SA4 serv;//具体的IPV4地址
    //创建一个通讯设备
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1){
        perror("socket");
        return -1;
    }
    //需要初始化服务器的ip地址和端口号
    serv.sin_family=AF_INET;
    serv.sin_port=htons(port);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);

    //将sfd绑定到本地的ip地址和端口号
    int b=bind(sfd,(SA*)&serv,sizeof(serv));
    if(b==-1){
        perror("bind");
        return -1;
    }
    //设置sockfd为被动监听状态
    listen(sfd,backlog);
    return sfd;
}
int t_accept(int fd){
    SA4 cli;
    socklen_t cli_len;
    char IP[32];
    cli_len=sizeof(cli);
    int cfd=accept(fd,(SA *)&cli,&cli_len);
    if(cfd==-1){
        perror("accept");
        return -1;
    }
    printf("%s\n",inet_ntop(AF_INET,&cli.sin_addr,\
                IP,32));

    return cfd;
}



