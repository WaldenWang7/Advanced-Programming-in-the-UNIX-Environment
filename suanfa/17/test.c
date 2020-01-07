#include<stdio.h>

int main()
{
	char s[100];
	scanf("%s",s);
	for(int i=0;i<100;i++)
	{
		printf("%c的ASCII值是%d\n",s[i],s[i]);
	
	}
	return 0;
}
