//Program for Stop and Wait ARQ_Client
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
int main()
{
char msg[50];
int pno,clnfd,totfram = 5,frcvd,bufr,ack,err,first;
socklen_t sclen;
struct sockaddr_in client;
printf("\n Enter the port number : ");
scanf("%d",&pno);
memset(&client,0,sizeof(client));
clnfd = socket(AF_INET,SOCK_DGRAM,0);
if(clnfd == -1)
{
printf("\n Socket creation error !!! \n");
exit(1);
}
client.sin_family = AF_INET;
client.sin_port = htons(pno);
client.sin_addr.s_addr = inet_addr("127.0.0.1");
sclen = sizeof(client);
printf("\n Sending connection confirmation ... \n");
sprintf(msg,"ready to receive packet frames ...");
sendto(clnfd,msg,sizeof(msg),0,(struct sockaddr*)&client,sclen);printf("\n Waiting for sender response ... \n");
sleep(1);
recvfrom(clnfd,msg,sizeof(totfram),0,(struct sockaddr*)&client,&sclen);
first=1;
bufr=1;
while(bufr <= totfram)
{
recvfrom(clnfd,&frcvd,sizeof(frcvd),0,(struct sockaddr*)&client,&sclen);
if(first == 1 && frcvd == 3)
{
frcvd++;
first = 0;
}
if(bufr == frcvd)
{
ack = 1;
printf("\n frame # %d receive",frcvd);
bufr++;
}
else
{
ack = -1;
printf("\n frame # %d received",frcvd);
}
printf("\n sending ack to server \n");
if(ack == 1)
printf("\n Positive");
else
printf("\n Negative");
sendto(clnfd,(char*)&ack,sizeof(ack),0,(struct sockaddr*)&client,sclen);
sleep(2);
}
printf("\n All frames are transmitted successfully \n Closing connection \n");
close(clnfd);
return 0;
}
//End of the program
