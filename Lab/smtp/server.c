//Program for SMTP_Server
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
struct sockaddr_in server,client;
int sock_desc,temp_sock_desc,pno,i=0,j,m=0;
socklen_t len;
char buf[100],domain[20],snd[26];
memset(&server,0,sizeof(server));
memset(&client,0,sizeof(client));
printf("\n Enter the port number : ");
scanf("%d",&pno);
if((sock_desc=socket(AF_INET,SOCK_DGRAM,0))==-1)
{
printf("\n Socket creation failed !!!\n");
exit(1);
}
server.sin_family=AF_INET;
server.sin_port=pno;
server.sin_addr.s_addr=INADDR_ANY;
if((bind(sock_desc,(struct sockaddr *)&server,sizeof(server)))==-1)
{
printf("\n Binding error !!!\n");
exit(1);
}
len=sizeof(server);
if((recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr *)&server,&len))==-1)
{
printf("\n Error in receiving !!!\n");
exit(1);
}
strcpy(snd,buf);
while(i<strlen(buf))
{
if(buf[i]=='0')
{
for (j=i+1;strlen(buf);j++)
domain[m++]=buf[j];
break;
}
i++;
}
domain[m]='\0';
printf("\n Reveiving mail ...");
printf("\n Domain verified <<%s>> ...\n",domain);len=sizeof(server);
if((recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr *)&server,&len))==-1)
{
printf("\n Error in receiving !!!\n");
exit(1);
}
printf("\n From : %s\n",buf);
len=sizeof(server);
if((recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr *)&server,&len))==-1)
{
printf("\n Error in receiving !!!\n");
exit(1);
}
while(strcmp(buf,".")!=0)
{
printf("%s\t\n\t",buf);
len=sizeof(server);
if((recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr *)&server,&len))==-1)
{
printf("\nError in receiving..\n");
exit(1);
}
}
printf("\n Mail received to: %s \n",snd);
close(temp_sock_desc);
return(0);
}
//End of the program
