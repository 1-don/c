/**** ccalculator.c  ***/


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

char operator;
int op1,op2,result;
if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
printf("socket created sucessfully\n");

struct sockaddr_in servaddr;

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=5069;

sin_size = sizeof(struct sockaddr_in);
if((con=connect(sockfd,(struct sockaddr *) &servaddr, sin_size))==0); //initiate a connection on a socket
printf("connect sucessful\n");
printf("Enter operation:\n +:Addition \n -: Subtraction \n /: Division \n*:Multiplication \n");
scanf("%c",&operator);
printf("Enter operands:\n");
scanf("%d %d", &op1, &op2);

write(sockfd,&operator,10);
write(sockfd,&op1,sizeof(op1));
write(sockfd,&op2,sizeof(op2));
read(sockfd,&result,sizeof(result)); 
printf("Operation result from server=%d\n",result);  
close(sockfd);
}
/*
Output :-
gescoe@gescoe-OptiPlex-3020:~$ cd Desktop/
gescoe@gescoe-OptiPlex-3020:~/Desktop$ gcc ccalculator.c
gescoe@gescoe-OptiPlex-3020:~/Desktop$ ./a.out
socket created sucessfully
connect sucessful
Enter operation:
 +:Addition 
 -: Subtraction 
 /: Division 
*:Multiplication 
*
Enter operands:
10
2
Operation result from server=20
gescoe@gescoe-OptiPlex-3020:~/Desktop$ 
*/



/****** scalculator.c ****/


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
char operator;
int op1,op2,result;
if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
printf("socket created sucessfully\n");  //socket creation

struct sockaddr_in servaddr;              
struct sockaddr_in clientaddr;

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=5069;

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

read(connfd, &operator,10);
read(connfd,&op1,sizeof(op1));
read(connfd,&op2,sizeof(op2));
switch(operator) {
        case '+': result=op1 + op2;
         printf("Result is: %d + %d = %d\n",op1, op2, result);
         break;
        case '-':result=op1 - op2;
                printf("Result is: %d - %d = %d\n",op1, op2, result);
                break;
        case '*':result=op1 * op2;
                printf("Result is: %d * %d = %d\n",op1, op2, result);
                break;
        case '/':result=op1 / op2;
                printf("Result is: %d / %d = %d\n",op1, op2, result);
                break;
        default: 
                printf("ERROR: Unsupported Operation");
    }
  
write(connfd,&result,sizeof(result));   
close(sockfd);
}
/*
Output:-
gescoe@gescoe-OptiPlex-3020:~$ cd Desktop/
gescoe@gescoe-OptiPlex-3020:~/Desktop$ gcc scalculator.c
gescoe@gescoe-OptiPlex-3020:~/Desktop$ ./a.out
socket created sucessfully
bind sucessful
listen sucessful
accept sucessful
Result is: 10 * 2 = 20
gescoe@gescoe-OptiPlex-3020:~/Desktop$ 
*/

