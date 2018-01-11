#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include"server.h"
#include<r_file.h>
#include<string.h>
#include<stdlib.h>
extern struct flock lock;
int t_save(int cfd){
    char *msg1="添加成功\n";
    char *msg2="学号重复，添加失败!\n";
    stu *p_s=NULL;
       p_s=(stu *)malloc(sizeof(stu));
       p_s->no=0;
    int fd=open("student.dat",O_RDWR|O_CREAT|O_APPEND,0664);
    if(fd==-1){
        perror("open");
        return -1;
    }
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=0;
    int t=lock_t(fd);//给文件加写锁
    write(cfd,&t,sizeof(int));
    if(t==-1){
        close(fd);
         return -1;
    }
     read(cfd,p_s,sizeof(stu));
     link_t h=read_link(fd);//读取链表
    if(search_node(h,p_s->no)){//查询是否有重复学号
     write(cfd,msg2,strlen(msg2)+1);
     }else{
     write(fd,p_s,sizeof(stu));
     write(cfd,msg1,strlen(msg1)+1);
     }
     destroy_link(h);//销毁链表
    close(fd);
    if(p_s!=NULL){
    free(p_s);
    p_s=NULL;
    }
    return 0;
}
int t_select(int cfd){
    int num=0,r=0,flag=0;
    stu s;
     int fd=open("student.dat",O_RDONLY);
    write(cfd,&fd,sizeof(int));
     if(fd==-1){
     perror("open");
     return;
     }
    lock.l_type=F_RDLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=0;
    int t=lock_t(fd);//给文件加读锁
    write(cfd,&t,sizeof(int));
    if(t==-1){
        close(fd);
         return -1;
    }
     read(cfd,&num,sizeof(num));
     printf("%d\n",num);
     lseek(fd,0,SEEK_SET);
     while(1){
         r=read(fd,&s,sizeof(stu));
        if(r==0)break;
        if(num==9){//显示所有学生信息
            write(cfd,&s,sizeof(stu));
        }else if(num==s.no){//显示指定学号学生信息
         write(cfd,&s,sizeof(stu));
         flag++;
         close(fd);
         return 0;
    }
     lseek(fd,0,SEEK_CUR);
    }
     if(flag==0)s.no=0;
     write(cfd,&s,sizeof(stu));
     close(fd);
     return 0;
}
int t_modify(int cfd){
    char *msg="修改成功!\n";
    int num=0,count=0,flag1=-1,flag2=0;;
    stu *p_s=NULL;
    int fd=open("student.dat",O_RDWR);
    write(cfd,&fd,sizeof(int));
    if(fd==-1){
      perror("open");
      return -1;
    }
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=0;
    int t=lock_t(fd);//给文件加写锁
    write(cfd,&t,sizeof(int));
    if(t==-1){
        close(fd);
         return -1;
    }
    link_t h1=read_link(fd);//读取链表
    read(cfd,&num,sizeof(num));
   if((p_s=search_node(h1,num))==NULL){//查找要修改结点并判空
    write(cfd,&flag1,sizeof(int));
    destroy_link(h1);//销毁链表
    close(fd);
    return -1;
   }
    write(cfd,&flag2,sizeof(int));
    write(cfd,p_s,sizeof(stu));
    lseek(fd,0,SEEK_SET);
    ftruncate(fd,0);
    lseek(fd,0,SEEK_SET);
    read(cfd,p_s,sizeof(stu));
    save_link(h1,fd);//保存链表并销毁
    close(fd);
    write(cfd,msg,strlen(msg)+1);
    return 0;
}
int t_delete(int cfd){
   int num=0,count=0;
   link_t h1=NULL;
   char *msg="删除成功!\n";
   char *msg1="没有找到该学生!\n";
   char *msg2="数据库为空，不能执行该操作!\n";
   int fd=open("student.dat",O_RDWR);
   write(cfd,&fd,sizeof(int));
   if(fd==-1){
   perror("open");
   return -1;
   }
   lock.l_type=F_WRLCK;
   lock.l_whence=SEEK_SET;
   lock.l_start=0;
   lock.l_len=0;
    int t=lock_t(fd);//给文件加写锁
    write(cfd,&t,sizeof(int));
    if(t==-1){
        close(fd);
        return -1;
    }
    if((h1=read_link(fd))==NULL){//读取链表
    write(cfd,msg2,strlen(msg2)+1);
    destroy_link(h1);//销毁链表
    close(fd);
    return -1;
    }
    read(cfd,&num,sizeof(num));
   if(search_node(h1,num)==NULL){//查询要删除结点
    write(cfd,msg1,strlen(msg1)+1);
    destroy_link(h1);//销毁链表
    close(fd);
    return 0;
   }
   h1=link_del_node(h1,num);//删除结点
    lseek(fd,0,SEEK_SET);
    ftruncate(fd,0);
    lseek(fd,0,SEEK_SET);
   save_link(h1,fd);//保存链表并销毁
   close(fd);
   write(cfd,msg,strlen(msg)+1);
   return 0;
}
void doit(int cfd){
    long code=0;
    int save;
     char *msg="failed...\n";
    char *msg1="密码正确，登录成功";
    char *msg2="密码错误，登录失败";
    read(cfd,&code,sizeof(code));
     if(code==111111)
         write(cfd,msg1,strlen(msg1)+1);
      else
        write(cfd,msg2,strlen(msg2)+1);
    while(1){
    int choice=0;
     int r=read(cfd,&choice,sizeof(int));
     switch(choice){
         case 1:
         save=t_save(cfd);
         if(save==-1){
             write(cfd,msg,strlen(msg)+1);
         }
         break;
         case 2:
         t_select(cfd);
         break;
         case 3:
         t_delete(cfd);
         break;
         case 4:
        t_modify(cfd);
         break;
         case 5:
         t_select(cfd);
         default:
         break;
}
}
}
