/**** cchat.c ***/


#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h> 
#include <unistd.h>
#include<string.h> 
#include<strings.h>
#include <arpa/inet.h>


void main()
{
int b,sockfd,sin_size,con,n,len;

char msg[100];
if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
printf("socket created sucessfully\n");

struct sockaddr_in servaddr;

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=5003;

sin_size = sizeof(struct sockaddr_in);
if((con=connect(sockfd,(struct sockaddr *) &servaddr, sin_size))==0); //initiate a connection on a socket
printf("connect sucessful\n");
printf("Enter the message:\n");
scanf("%s",msg);

write(sockfd,&msg,sizeof(msg));
 
 
close(sockfd);
}
/*
Output:-
gescoe@gescoe-OptiPlex-3020:~/Desktop/a$ gcc cchat.c
gescoe@gescoe-OptiPlex-3020:~/Desktop/a$ ./a.out
socket created sucessfully
connect sucessful
Enter the message:
hii
gescoe@gescoe-OptiPlex-3020:~/Desktop/a$ 
*/


/***** schat.c */

#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h> 
#include <unistd.h>

#include<string.h> 
#include <arpa/inet.h>

void main()
{
int b,sockfd,connfd,sin_size,l,n,len;
char msg[10];
if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
printf("socket created sucessfully\n");  //socket creation


struct sockaddr_in servaddr;              
struct sockaddr_in clientaddr;

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=5003;

if((bind(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)))==0)
printf("bind sucessful\n");   //bind() assigns the
     //  address  specified  by  addr  to  the  socket  referred  to by the file
      // descriptor sockfd.  addrlen  specifies  the  size,  in  bytes,  of  the
     //  address structure pointed to by addr.  Traditionally, this operation is
      // called “assigning a name to a socket”.



if((listen(sockfd,5))==0) //listen for connections on a socket
printf("listen sucessful\n");


sin_size = sizeof(struct sockaddr_in);
if((connfd=accept(sockfd,(struct sockaddr *)&clientaddr,&sin_size))>0);
printf("accept sucessful\n");

read(connfd, &msg,10);
write(connfd,&msg,sizeof(msg));
printf("The entered message is :%s\t",msg);    
close(sockfd);
}
/*
Output:-
gescoe@gescoe-OptiPlex-3020:~/Desktop/a$ gcc schat.c
gescoe@gescoe-OptiPlex-3020:~/Desktop/a$ ./a.out
socket created sucessfully
bind sucessful
listen sucessful
accept sucessful
The entered message is :hii	gescoe@gescoe-OptiPlex-3020:~/Desktop/a$ 

*/


