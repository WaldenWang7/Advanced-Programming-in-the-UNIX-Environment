#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<string.h>
#include<fcntl.h>


#define PRI_SHM_ID 1000
#define PATH_SHM "/test/suanfa/9"

int main()
{
	key_t keyVal=0;
	int nShmid =0;
	char *pchShm=NULL;

	keyVal=ftok(PATH_SHM,PRI_SHM_ID);
 	
	nShmid=shmget(keyVal,10,IPC_CREAT|0777);
	if(nShmid==-1){
		printf("create share memory failed\n");
		return 1;
	}
	
	pchShm=(char*)shmat(nShmid,0,0);
	if(NULL==pchShm){
		printf("get share pointer failed\n");
		return 1;
	}

	strncpy(pchShm,"wanghzong",20);
	
	shmdt(pchShm);

	return 0;
}
