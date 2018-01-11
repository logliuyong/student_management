#include <stdio.h>
#include <string.h>
#include "client.h"
#include<stdlib.h>
    void mystudent(int sfd){
        long code=0;
        char msg[128];
        char *msg1="正在退出...\n";
        printf("<<欢迎使用学生管理系统>>\n请输入登录密码:");
        system("stty -echo");
        scanf("%ld",&code);
        system("stty echo");
        write(sfd,&code,sizeof(code));
        read(sfd,msg,128);
        if(strcmp(msg,"密码错误，登录失败")==0){
        write(1,msg,strlen(msg)+1);
        printf("\n");
        exit(-1);
        }
        printf("登录成功！请输入你的操作：\n");
        printf("\n");
        while(1){
        int choice=0,tmp=0;
            printf("<<(1)添加学生信息>>\n");
            printf("<<(2)查找学生信息>>\n");
            printf("<<(3)删除学生信息>>\n");
            printf("<<(4)修改学生信息>>\n");
            printf("<<(5)下载所有学生信息>>\n");
            printf("<<(6)退出>>\n");
           scanf("%d",&choice);
           write(sfd,&choice,sizeof(choice));
           switch(choice){
               case 1:
               add_stu(sfd);
               break;
               case 2:
               query_stu(sfd);
               break;
               case 3:
               delete_stu(sfd);
               break;
               case 4:
               modify_stu(sfd);
               break;
               case 5:
               tmp=download_stu(sfd);
               if(!tmp)printf("下载成功！\n");
               break;
               case 6:
               write(1,msg1,strlen(msg1)+1);
               sleep(1);
               exit(0);
               default:
               printf("wrong choice\n");
               break;
           }
    }
    }


