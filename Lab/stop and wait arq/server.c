//Program for Stop and Wait ARQ_Server
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
char msg[50];
int svrfd,clnfd,err,totfram,fsnd,ack,pno;
socklen_t sclen;
struct sockaddr_in server,client;
printf("\n Enter the port number : ");
scanf("%d",&pno);
memset(&server,0,sizeof(server));
memset(&client,0,sizeof(client));
svrfd = socket(AF_INET,SOCK_DGRAM,0);
if(svrfd == -1)
{
printf("\n Socket creation error !!! \n");
exit(0);
}
server.sin_family = AF_INET;
server.sin_port = htons(pno);
server.sin_addr.s_addr = INADDR_ANY;
if(bind(svrfd,(struct sockaddr *)&server,sizeof(server)) == -1)
{
printf("\n Binding error !!! \n");
exit(0);
}
printf("\n Server waiting for connection ... \n");
sclen = sizeof(client);
recvfrom(svrfd,msg,sizeof(msg),0,(struct sockaddr *)&client,&sclen);
printf("\n Client connected ... \n");
totfram = 5;
printf("\n Total packet frame to transmitted \n");
sendto(svrfd,(char *)&totfram,sizeof(totfram),0,(struct sockaddr *)&client,sclen);
sleep(1);
fsnd = 1;
ack = 1;
while(fsnd <= totfram)
{
if(ack == 1)
printf("\n Transmitted frame #%d\n",fsnd);
else
printf("\n Retransmitting frames #%d\n",fsnd);
sendto(svrfd,(char *)&fsnd,sizeof(fsnd),0,(struct sockaddr *)&client,sclen);
printf("\n Waiting for Acknowledgment");sleep(1);
recvfrom(svrfd,&ack,sizeof(ack),0,(struct sockaddr *)&client,&sclen);
printf("\n Received As \n");
if(ack == -1)
printf("\n Negative \n");
else
{
printf("\n Positive \n");
fsnd++;
}
sleep(1);
}
printf("\n All frames are transmitted successfully \n Closing Connection \n");
close(svrfd);
return 0;
}
//End of the program
