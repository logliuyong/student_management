#include <stdio.h>
#include <string.h>
#include "client.h"
#include<stdlib.h>
int add_stu(int sfd){
 stu s;
 bzero(&s,sizeof(s));
 int i=0,ms=0;
 char buf[128];
 char *msg1="数据库正在使用，请稍后再试!\n";
 char *msg2="可以写入数据，正在加载数据库，请稍后...\n";
 read(sfd,&ms,sizeof(int));
 if(ms==-1){//加锁失败
 write(1,msg1,strlen(msg1)+1);
    return -1;
 }
 write(1,msg2,strlen(msg2)+1);
 sleep(1);
 printf("请输入学号:");
 scanf("%d",&(s.no));      
 printf("请输入年龄:");
 scanf("%d",&(s.age));
 scanf("%*[^\n]");
 scanf("%*c");
 printf("请输入姓名:");
 fgets(s.name,10,stdin);
 s.p_next=NULL;
 write(sfd,&s,sizeof(s));
 memset(s.name,0,10);
 int r=read(sfd,buf,128);
 write(1,buf,r);
 return 0;
}
int query_stu(int sfd){
  int fd=0,num=0,ms=0;
  stu s;
  bzero(&s,sizeof(stu));
  char *msg="数据库不存在，无法执行该操作\n";
  char *msg1="数据库正在维护，请稍后再试!\n";
  char *msg2="正在加载数据，请稍后...\n";
  read(sfd,&fd,sizeof(int));
   if(fd==-1){//文件打开失败
      write(1,msg,strlen(msg)+1);
      return -1;
    }
  read(sfd,&ms,sizeof(int));
    if(ms==-1){//加锁失败
     write(1,msg1,strlen(msg1)+1);
     return -1;
    }
  write(1,msg2,strlen(msg2)+1);
  sleep(1);
  printf("请输入你要查找的学生的学号,输入‘9’显示所有学生信息:\n");
  scanf("%d",&num);
  write(sfd,&num,sizeof(num));
   if(num==9){
     printf("学号\t年龄\t姓名\n");
     while(1){
        read(sfd,&s,sizeof(stu));
        if(s.no==0)break;
        printf("%d\t%d\t%s",s.no,s.age,s.name);
        bzero(&s,sizeof(stu));
         }
    }else{
    read(sfd,&s,sizeof(stu));
    if(s.no==0){
        printf("没有找到该学生\n");
    return 0;
    }
    printf("学号:%d,年龄:%d,姓名:%s",s.no,s.age,s.name);
     }
    return 0;
}
int delete_stu(int sfd){
  int fd=0,ms=0,num=0;
  char buf[128];
  char *msg="数据库不存在，无法执行该操作\n";
  char *msg1="数据库正在使用，请稍后再试!\n";
  char *msg2="数据库加载中，请稍后...\n";
  read(sfd,&fd,sizeof(int));
    if(fd==-1){//文件打开失败
      write(1,msg,strlen(msg)+1);
      return -1;
    }
  read(sfd,&ms,sizeof(int));
    if(ms==-1){//加锁失败
     write(1,msg1,strlen(msg1)+1);
     return -1;
    }
  write(1,msg2,strlen(msg2)+1);
  sleep(1);
  memset(buf,0,128);
  printf("请输入你要删除学生信息的学号：");
  scanf("%d",&num);
  write(sfd,&num,sizeof(num));
  int r=read(sfd,buf,128);
  write(1,buf,r);
  return 0;
}
int modify_stu(int sfd){
  int num=0,flag=0,age=0,ms=0,fd=0,tmp=0;
  char name[10];
  char buf[128];
  stu s;
  char *msg="数据库不存在，无法执行该操作\n";
  char *msg1="数据库正在使用，请稍后再试!\n";
  char *msg2="数据库加载中，请稍后...\n";
  read(sfd,&fd,sizeof(int));
    if(fd==-1){//文件打开失败
      write(1,msg,strlen(msg)+1);
      return -1;
    }
  read(sfd,&ms,sizeof(int));
    if(ms==-1){//加锁失败
     write(1,msg1,strlen(msg1)+1);
     return -1;
    }
  write(1,msg2,strlen(msg2)+1);
  sleep(1);
  printf("请输入你要修改信息的学生学号:");
  scanf("%d",&num);
  write(sfd,&num,sizeof(int));
  read(sfd,&tmp,sizeof(int));
   if(tmp!=-1){
    read(sfd,&s,sizeof(stu));
    printf("请输入你要修改的内容：1.年龄,2.姓名");
    scanf("%d",&flag);
   if(flag==1){
    printf("原先的年龄是%d岁，请输入修改后的年龄：",s.age);
    scanf("%d",&age);
    s.age=age;
   }
  if(flag==2){
    scanf("%*[^\n]");
    scanf("%*c");
    printf("原来的姓名是%s,请输入修改后的姓名:",s.name);
    fgets(name,10,stdin);
    strcpy(s.name,name);
    memset(name,0,10);
    }
 write(sfd,&s,sizeof(stu));
    memset(s.name,0,10);
 int r=read(sfd,buf,128);
  write(1,buf,r);
  return 0;
  }else{
      printf("没有找到该学生!\n");
      return -1;
  }
 }
int download_stu(int sfd){
  int fd=0,num=9,ms=0;
  stu s;
  bzero(&s,sizeof(stu));
  char *msg="数据库不存在，无法执行该操作\n";
  char *msg1="数据库正在维护，请稍后再试!\n";
  char *msg2="正在下载文件，请稍后...\n";
  FILE *p_file=fopen("student.txt","w+");
  if(p_file==NULL){
    perror("fopen");
    return -1;
  }
  read(sfd,&fd,sizeof(int));
   if(fd==-1){//加锁失败(服务器)
      write(1,msg,strlen(msg)+1);
      return -1;
    }
  read(sfd,&ms,sizeof(int));
    if(ms==-1){//加锁失败(服务器)
     write(1,msg1,strlen(msg1)+1);
     return -1;
    }
  write(1,msg2,strlen(msg2)+1);
  sleep(1);
  write(sfd,&num,sizeof(num)); 
  fprintf(p_file,"%s\t%s\t%s\n","学号","年龄","姓名");
  while(1){
    read(sfd,&s,sizeof(stu));
     if(s.no==0)break;
     fprintf(p_file,"%d\t%d\t%s",s.no,s.age,s.name);
     bzero(&s,sizeof(stu));
  }
 fclose(p_file);
  p_file=NULL;
  return 0;
}













