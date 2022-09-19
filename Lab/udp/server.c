//Program for UDP Server
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
struct sockaddr_in cin,caddr;
int cid,n,i,byrc,b,pno,len;
char buf[32],c,echobuf[32];
printf("\n Enter the port number : ");
scanf("%d",&pno);
cid=socket(AF_INET,SOCK_DGRAM,0);
if(cid==-1)
{
printf("\n Socket Error !!!\n");
return 0;
}
cin.sin_family=AF_INET;
cin.sin_port=htons(pno);
cin.sin_addr.s_addr=htons(INADDR_ANY);
n=sizeof(cin);
caddr.sin_family=AF_INET;
caddr.sin_addr.s_addr=htons(INADDR_ANY);
if(bind(cid,(struct sockaddr *)&cin,n)<0)
{
printf("\n Binding Error !!!\n");
return 0;
}
b=sizeof(caddr);
printf("\n Server Started ...\n");
do
{
strncpy(echobuf,"",32);
if((byrc=recvfrom(cid,echobuf,31,0,(struct sockaddr *)&caddr,&b))<=0)
{
printf("\n Receiving Error !!!\n");
return 0;
}
if(strcmp(echobuf,"quit")==0)
{
printf("\n Server Stoped... \n");
break;
}
printf("\n From Client : ");
printf("%s",echobuf);
strncpy(buf,"",32);printf("\n To Client : ");
scanf("%s",buf);
sendto(cid,buf,strlen(buf),0,(struct sockaddr *)&caddr,sizeof(caddr));
if(strcmp(buf,"quit")==0)
{
printf("\n Server Stoped... \n");
break;
}
}while(1);
close(cid);
}
//End of the program
