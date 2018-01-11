#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include<r_file.h>
#include<string.h>
extern struct flock lock;
link_t destroy_link(link_t h){//销毁链表
    stu *tmp;
    while(h){
        h=h->p_next;
        free(tmp);
        tmp=NULL;
    }
    return h;
}
stu *search_node(link_t h,int key){//根据索引查找节点
    stu *tmp=NULL;
    tmp=h;
    while(tmp!=NULL){
        if(tmp->no==key) return tmp;
        tmp=tmp->p_next;
    }
    return tmp;
}
link_t link_add_node(link_t h,stu *n){//将节点插入到链表的尾部
    stu *p=h;
    if(h==NULL){
        h=n;
        return h;
    }
    while(p->p_next){
        p=p->p_next;
    }
    p->p_next=n;
    return h;
}
link_t link_del_node(link_t h,int key){//删除节点
    stu *tmp,*pre;
    tmp=pre=h;
    while(tmp){
        if(tmp->no==key){
            if(tmp==pre){
                h=h->p_next;
                free(tmp);
                tmp=pre=NULL;
                return h;
            }else{
                pre->p_next=tmp->p_next;
                free(tmp);
                tmp=NULL;
                return h;
            }
        }else{
            if(tmp!=pre)pre=pre->p_next;
            tmp=tmp->p_next;
        }
    }
    return h;
}
link_t read_link(int fd){//把文件内容读取到链表中
    int r=0;
    link_t head=NULL;
    int  count=0;
while(1){
    stu *p_s=malloc(sizeof(stu));
   r=read(fd,p_s,sizeof(stu));
   if(p_s->no==0||r==0)break;
     head=link_add_node(head,p_s);
     p_s->p_next=NULL;
       count++;
}
    printf("count=%d\n",count);
    if(count==0)return NULL;
    printf("head->no=%d\n",head->no);
    return head;
}
void save_link(link_t h,int fd){//把链表内容存入到文件中，并销毁链表
    int savenum=0;
   stu *tmp=NULL;
   while(h){
       tmp=h;
     write(fd,tmp,sizeof(stu));
     savenum++;
     h=h->p_next;
     free(tmp);
     tmp=NULL;
   }
  printf("savenum=%d\n",savenum);
}
int lock_t(int fd){//创建一把锁
    int fc1=fcntl(fd,F_SETLK,&lock);
    if(fc1==-1){
       perror("fcntl");
       return -1;
    }
   return 0;
}
