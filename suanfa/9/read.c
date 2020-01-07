#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<sys/sem.h>


#define PRI_SHM_ID 1000
#define PATH_SHM "/test/suanfa/9"

int main()
{
	key_t keyVal=0;
	int nShmid=0;
	char *pchShm=NULL;

	keyVal=ftok(PATH_SHM,PRI_SHM_ID);
	
	nShmid= shmget(keyVal,10,IPC_CREAT|0666);
	if(nShmid ==-1)
	{
		printf("create share memory failed\n");
		return 0;
	}
	
	pchShm =(char*)shmat(nShmid,0,0);
	if(NULL==pchShm)
	{
 		printf("get share pointer failed\n");
		return 1;
	}

	printf("%s\n",pchShm);
	
	shmdt(pchShm);

	return 0;
}
