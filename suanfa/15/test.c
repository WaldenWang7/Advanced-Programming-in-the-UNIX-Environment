#include<stdio.h>
int check()
{
	int a =1;	
	return *(char*)&a;
}
int main()

{
	int ret =check();
	if(ret ==1)
	{
	printf("xiao\n");
	}
	else
	{
	printf("da\n");
	}
	return 0;
}
