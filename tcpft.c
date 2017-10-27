/**** cftp.c ***/

#include <unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>

void main()
{
    struct sockaddr_in serveraddr;
    int clientsock,n,rdret,length;
    char filename[20],filedata[300];
    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=2000;
    serveraddr.sin_addr.s_addr=inet_addr("192.168.43.191");
    clientsock=socket(AF_INET,SOCK_STREAM,0);
    if(connect(clientsock,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
    {
        printf("\nError:Cannot connect...");
        exit(0);
    }
    printf("Enter the name of the file : ");
    scanf("%s",filename);
    length=strlen(filename);
    write(clientsock,filename,length);
    rdret=read(clientsock,filedata,300);
    printf("\nThe contents of the file: \n\n");
    printf("%s",filedata);
    close(clientsock);
}
/*
OUTPUT:
tanmay@tanmay-desktop:~/Desktop gcc cftp.c
tanmay@tanmay-desktop:~/Desktop ./a.out
Enter the name of the file : fttp.txt

The contents of the file: 

FTP: the file transfer protocol
transfers file to/from remote host
client/server model
www.2k8618.blogspot.com
tanmay@tanmay-desktop:~/Desktop 

*/


/**** fttp.txt

FTP: the file transfer protocol
transfers file to/from remote host
client/server model
www.2k8618.blogspot.com*/


/***** sftc.c ****/
#include <unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
void main()
{
    struct sockaddr_in clientaddr,serveraddr;
    int serversock,newserversock,clientsize,n,f,rc;
    char filename[100],filedata[300];
    fflush(stdin);
    serversock=socket(AF_INET,SOCK_STREAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=2000;
    serveraddr.sin_addr.s_addr=inet_addr("192.168.43.191");
    bind(serversock,(struct sockaddr*)&serveraddr,sizeof(serveraddr));   
    sizeof(serveraddr);
    listen(serversock,5);
    while(1)
    {
        clientsize=sizeof(clientaddr);
        newserversock=accept(serversock,(struct sockaddr*)&clientaddr,&clientsize);
        n=read(newserversock,filename,100);
        filename[n]=0;
        printf("\nThe requested file from the client is  %s.\n",filename);
        
        f=open(filename,O_RDWR);
        n=read(f,filedata,300);
        printf("\nThe contents of the file: \n\n");
        printf("%s",filedata);
        write(newserversock,filedata,n);
    }
    close(serversock);
    close(newserversock);
}
/*
OUTPUT:
tanmay@tanmay-desktop:~/Desktop gcc sftc.c 
tanmay@tanmay-desktop:~/Desktop ./a.out

The requested file from the client is  fttp.txt.

The contents of the file: 

FTP: the file transfer protocol
transfers file to/from remote host
client/server model
www.2k8618.blogspot.com
*/


