//Program for SMTP_Client
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
struct sockaddr_in client;
int sock_desc,pno;
char buf[100];
memset(&client,0,sizeof(client));
printf("\n Enter the port number : ");
scanf("%d",&pno);
if((sock_desc=(socket(AF_INET,SOCK_DGRAM,0)))==-1)
{
printf("\n Socket creation failed !!!\n");
exit(1);
}client.sin_family=AF_INET;
client.sin_port=pno;
client.sin_addr.s_addr=inet_addr("127.0.0.1");
printf("\n To
: ");
scanf("%s",buf);
if((sendto(sock_desc,buf,sizeof(buf),0,(struct sockaddr *)&client,sizeof(client)))==-1)
{
printf("\nSending error !!!\n");
exit(1);
}
strcpy(buf,"\0");
printf("\n From : ");
scanf("%s",buf);
if((sendto(sock_desc,buf,sizeof(buf),0,(struct sockaddr *)&client,sizeof(client)))==-1)
{
printf("\n Error in sending !!!\n");
exit(1);
}
strcpy(buf,"\0");
printf("\n Subject : ");
scanf("%s",buf);
if((sendto(sock_desc,buf,sizeof(buf),0,(struct sockaddr *)&client,sizeof(client)))==-1)
{
printf("\n Error in sending !!!\n");
exit(1);
}
strcpy(buf,"\0");
printf("\n Message body : ");
while(strcmp(buf,".")!=0)
{
strcpy(buf,"\0");
scanf("%s",buf);
if((sendto(sock_desc,buf,sizeof(buf),0,(struct sockaddr *)&client,sizeof(client)))==-
1)
{
printf("\n Error in sending !!!\n");
exit(1);
}
}
close(sock_desc);
return 0;
}
//End of the program
