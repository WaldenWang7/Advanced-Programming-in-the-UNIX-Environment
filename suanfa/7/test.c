#include<stdio.h>
int main()
{
	double number1,number2;
	printf("请输入两个浮点数\n");
	scanf("%lf %lf",&number1,&number2);
	printf("结果=%.21f",number1*number2);
	return 0;
}
