#include <stdio.h>

#define BUFFER_SIZE 30

int main()
{
 int x;
 int fd[2];
 char buf[BUFFER_SIZE];
 char s[BUFFER_SIZE];
 pipe(fd);//�����ܵ�

 while((x=fork())==-1);//�����ܵ�ʧ��ʱ������ѭ��
 
 /*�����ӽ��̣��ӽ�����ܵ���д��һ���ַ���*/
 if(x==0)
 {
  sprintf(buf,"This is an example of pipe!/n");
  write(fd[1],buf,BUFFER_SIZE);
  exit(0);
 }

 

 /*���븸���̣������̴ӹܵ�����һ�˶����ղ�д����ַ���*/
 else
 {
  wait(0);//�ȴ��ӽ��̽���
  read(fd[0],s,BUFFER_SIZE);//�����ַ����������䴢����char s[]��
  printf("%s",s);//��ӡ�ַ���
 }
 return 0;
}