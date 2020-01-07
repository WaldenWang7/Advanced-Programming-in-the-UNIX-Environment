#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<sys/ipc.h>
int main()
{
	int semid;
	semid=semget(1234,1,IPC_CREAT|0666);
	printf("semid='%d'\n",semid);
	return 0;
}
