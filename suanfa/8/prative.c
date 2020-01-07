#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct msgbuf{
	long mtype;
	char mtext[500];
};
int main (int argc,char *argv[])
{
	int queue_id;
	struct msgbuf  *msg,*recv_msg;
	int  rc;
	int msgsz;
	queue_id=msgget(IPC_PRIVATE,IPC_CREAT|0600);
	if (queue_id==-1){
		perror("main's msgget");
		exit(1);
	}
	printf("the created message's id= '%d'.\n",queue_id);
	msg = (struct msgbuf *) malloc(sizeof(struct msgbuf)+strlen("hello,world"));
	msg->mtype=1;
	strcpy(msg->mtext,"hello,wordl");
	rc = msgsnd(queue_id,msg,strlen(msg->mtext)+1,0);
	if(rc==-1){
		perror("msgsnd");
		exit(1);
	}
	else
	printf("%d\n",rc);
	free(msg);
	printf("message is placed on message's queue\n");
	recv_msg= (struct msgbuf*) malloc(sizeof(struct msgbuf)+strlen("hello,world")+1);
	msgsz=strlen(recv_msg->mtext)+1;
	rc = msgrcv (queue_id,recv_msg,msgsz,0,0);
	if(rc==-1){
		perror("msgrcv");
		exit(1);
	}
	printf("received message's mtype is '%ld';mtext if '%s' \n",recv_msg->mtype,recv_msg->mtext);
	msgctl(queue_id,IPC_RMID,NULL);
	return 0;
}
