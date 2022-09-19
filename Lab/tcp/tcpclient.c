#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
int main()
{
	struct sockaddr_in caddr;
	int cid,rec;
	char buf[32],temp[32],msg[30];
	unsigned int l;
	cid=socket(PF_INET,SOCK_STREAM,0);
	if(cid==-1)
	 perror("socket error \n");
	memset(&caddr,0,sizeof(caddr));
	caddr.sin_family=AF_INET;
	caddr.sin_port=htons(2068);
	caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(cid,(struct sockaddr *)&caddr,sizeof(caddr))<0)
	perror("\n connection is not possible");
	do
	{
	printf("enter the message to send\n");
	scanf("%s",temp);
	strncpy(msg,"",32);
	strcpy(msg,temp);
	l=strlen(msg);
	send(cid,msg,l,0);
	if(strcmp(msg,"quit")==0)
	break;
	strncpy(buf,"",32);
	if((rec=recv(cid,buf,31,0))<0)
	perror("receive failed");
	printf("from server:\n");
	printf("%s",buf);
	printf("reversed message received\n");
	}while(1);
	shutdown(cid,1);
	close(cid);
	}
