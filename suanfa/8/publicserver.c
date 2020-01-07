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
	int i;
	int msgid;
	int pid;
	int *pint;
	msgid= msgget(SVKEY,0777|IPC_CREAT);
	for(;;)
	{
		msgrcv(msgid,&msg,256,REQ,0);
		printf("server is doing the service for a client.\n");
		pint=(int *)msg.mtext;
		pid=*pint;
		printf("server receive client's service request is client's pid:%d.\n",pid);
		msg.mtype=pid;
		*pint=getpid();
		msgsnd(msgid,&msg,sizeof(int),0);
	}
	return 0;
}
