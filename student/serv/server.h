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
struct flock lock;
 int t_listen(int,int);
 int t_accept(int);
 int t_delete(int);
 int t_save(int);
 int t_select(int);
 int t_modify(int);
void doit(int);
link_t read_link(int);
void save_link(link_t,int);
int lock_t(int);
 link_t destroy_link(link_t);
 stu *search_node(link_t,int);
 link_t link_add_node(link_t,stu *);
 link_t link_del_node(link_t,int);
#endif
