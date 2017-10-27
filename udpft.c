
/****  cftp.c ****/
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>
void main()
{
    struct sockaddr_in server,client;
    int s,n,ret;size_t fp;
    char filename[20],downloaded[10],filedata[100],c[25];
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    s=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_port=2000;
    server.sin_addr.s_addr=inet_addr("192.168.43.191");
    n=sizeof(server);
    printf("Enter the name of the file: ");
    scanf("%s",filename);
    printf("\nEnter a name to save: ");
    scanf("%s",downloaded);
    printf("\nDownloading...\n");
    sendto(s,filename,sizeof(filename),0,(struct sockaddr *)&server,n);
    fp = open(downloaded, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if(fp==-1)
    {
        printf("\nError...");
        exit(0);
    }
    recvfrom(s,filedata,sizeof(filedata),0,NULL,NULL);
    printf("\nProcessing Contents...\n");
    while(1)
    {
        if(strcmp(filedata,"end")==0)
            break;
    printf("%s",filedata);
        ret=write(fp,filedata,strlen(filedata));
        bzero(filedata,100);
        recvfrom(s,filedata,sizeof(filedata),0,NULL,NULL);
    }
    printf("\nFile downloaded successfully...\n");
}
/*
OUTPUT:
gescoe@ubuntu-desktop:~/Desktop gcc cftp.c
gescoe@ubuntu -desktop:~/Desktop ./a.out
Enter the name of the file: mybtech.txt

Enter a name to save: t1.txt

Downloading...

Processing Contents...
~~My Btech~~
A Computer Science & Engineering Portal
www.2k8cs.tk
www.2k8618.blogspot.com
2008-2012


File downloaded successfully...
gescoe@ubuntu -desktop:~/Desktop
*/



/**** mybetech.txt  

~~My Btech~~
A Computer Science & Engineering Portal
www.2k8cs.tk
www.2k8618.blogspot.com
2008-2012
*/


/********  scftp.c ****/

#include <unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>

void main()
{
    struct sockaddr_in server,client;
    int serversock,n,fp,end;
    char filename[20],buffer[100];
    serversock=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_port=2000;
    server.sin_addr.s_addr=inet_addr("192.168.43.191");
    bind(serversock,(struct sockaddr *)&server,sizeof(server));
    n=sizeof(client);
    recvfrom(serversock,filename,sizeof(filename), 0,(struct sockaddr *)&client,&n);
    fp=open(filename,O_RDONLY);
    while(1)
    {
        end=read(fp,buffer,sizeof(buffer));
        if(end==0)
            break;
        sendto(serversock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,n);
        bzero(buffer,100);
    }
    strcpy(buffer,"end");
    sendto(serversock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,n);
}
/*
OUTPUT:
tanmay@tanmay-desktop:~/Desktop gcc scftp.c
tanmay@tanmay-desktop:~/Desktop ./a.out
tanmay@tanmay-desktop:~/Desktop

*/

