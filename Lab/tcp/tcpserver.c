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
	struct sockaddr_in saddr,caddr;
	int sid,cid,k;
	unsigned int n;
	char buf[32],buff[32],*tim;
	int l,i,j;
	struct tm *t=NULL;
	sid=socket(PF_INET,SOCK_STREAM,0);
	if(sid==-1)
	perror("socket Failed\n");
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(2068);
	saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(bind(sid,(struct sockaddr *)&saddr, sizeof(saddr))<0)
		perror("\n Bind Failed");
	printf("server started!! Waiting for client to connect");
	if(listen(sid,0)<0)
		perror("Listen Failed");
	n=sizeof(caddr);
	if((cid=accept(sid,(struct sockaddr *)&caddr,&n))<0)
		perror("\n Accept Failed");
	do
	{
	strncpy(buf,"",32);
	if(l=(recv(cid,buf,31,0))<=0)
	perror("\n receive failed\n");
	if(strcmp(buf,"quit")==0)
	break;
	printf("\n from client :%s",buf);
	l=strlen(buf);
	strncpy(buff,"",32);
	k=0;
	for(i=0;i<=l;i++)
	{
		if((buf[i]==' ')||(buf[i]=='\0'))
		{
		j=i-1;
		while((j>=0)&&(buf[i]=='\0'))
		{
			j=i-1;
			while((j>=0)&&(buf[j]!=' '))
			buff[k++]=buf[j--];
			buff[k++]=' ';
		}
		}
	}
	printf("\n");
	printf("%s",buff);
	send(cid,buff,strlen(buff),0);
	printf("message send to client");
	}while(1);
	shutdown(sid,2);
	close(sid);
}

