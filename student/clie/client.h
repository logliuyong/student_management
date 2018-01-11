#ifndef T_NET_H_
#define T_NET_H_
#include <sys/types.h>
#include <sys/socket.h>
#include<unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
typedef struct sockaddr_in  SA4;
typedef struct sockaddr SA;
typedef struct Student{
    int no;
    int age;
    char name[10];
   struct Student *p_next;
}stu;
typedef stu *link_t;
int t_connect(char*,int);
void mystudent(int);
int add_stu(int);
int query_stu(int);
int delete_stu(int);
int  modify_stu(int);
int download_stu(int);
#endif
