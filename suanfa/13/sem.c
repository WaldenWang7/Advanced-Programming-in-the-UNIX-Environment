#include <string.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
 
union semun 
{ 
    int val; 
    struct semid_ds *buf; 
    unsigned short int *array; 
    struct seminfo *__buf; 
}; 
 
int main(void) 
{ 
    char* buf_child[]={"the", "is", "sunzi,", "cao","ma"}; 
    char* buf_father[]={"father", "say:", "wo", "ni","a"}; 
    int i = 0, semid, fd; 
    pid_t pid; 
    struct sembuf sb; //�ź�������
    union semun sem; 
    semid = semget(1000, 2, 0666 | IPC_CREAT); //�����ź����飬����2���ź���
 
    sem.val = 0; 
    semctl(semid, 0, SETVAL, sem); //��ʼ��0���ź���Ϊ0
    sem.val = 1; 
    semctl(semid, 1, SETVAL, sem); //��ʼ��1���ź���Ϊ1
 
    fd=open("tmp",O_CREAT|O_TRUNC|O_WRONLY,0666); 
 
    pid = fork(); 
    switch (pid) { 
        case -1: 
            perror("fork fail"); 
            break; 
        case 0: /* child consume */ 
            srand((unsigned int)getpid()); 
            while (i < 5) { 
                sb.sem_num = 1; //��1���ź���
                sb.sem_op = -1; //��1
                sb.sem_flg = sb.sem_flg & ~IPC_NOWAIT; 
                semop(semid, &sb, 1); 
 
                write(fd,buf_child[i], strlen(buf_child[i])); 
  //              sleep(rand()); 
                write(fd,&" ", 1); 
                i++; 
 
                sb.sem_num = 0; //��0���ź���
                sb.sem_op = 1;  //��1
                sb.sem_flg = sb.sem_flg & ~IPC_NOWAIT; 
                semop(semid, &sb, 1); //�����ź���
            } 
            break; 
        default:/* parent production  */ 
            srand((unsigned int)getpid()); 
            while (i < 5) { 
                sb.sem_num = 0; //��0���ź���
                sb.sem_op = -1; //��1
                sb.sem_flg = sb.sem_flg & ~IPC_NOWAIT; 
                semop(semid, &sb, 1); //�����ź���
 
                write(fd,buf_father[i], strlen(buf_father[i])); 
//                sleep(rand()); 
                write(fd,&" ", 1); 
                i++; 
 
                sb.sem_num = 1; 
                sb.sem_op = 1; 
                sb.sem_flg = sb.sem_flg & ~IPC_NOWAIT; 
                semop(semid, &sb, 1); 
            } 
            break; 
    } 
    return 0; 
} 
