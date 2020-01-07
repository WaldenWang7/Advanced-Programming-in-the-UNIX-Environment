#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#define SVKEY 75
#define REQ 1
struct msgform{
	long mtype;
	char mtext[256];
	};
int main()
{
	struct msgform msg;
	int msgid;
	int pid;
	int *pint;
	msgid=msgget(SVKEY,0777);
	pid=getpid();
	pint =(int *)msg.mtext;
	*pint=pid;
	msg.mtype=REQ;
	msgsnd(msgid,&msg,sizeof(int),0);
	msgrcv(msgid,&msg,256,pid,0);
	printf("client recevive server's service result is server's pid :%d.\n",*pint);
	return 0;
}

