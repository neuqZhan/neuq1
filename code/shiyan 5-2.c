#include<stdio.h>
void main()
{
	float a,b;
	char c;
	printf("please input three numbers:\n");
	scanf("%f%c%f",&a,&c,&b);
	if(c=='+')
		printf("a+b=%f\n",a+b);
	else if(c=='-')
		printf("a-b=%f\n",a-b);
	else if(c=='*')
		printf("a*b=%f\n",a*b);
	else if(c=='/')
		printf("a/b=%f\n",a/b);
	else
		printf("input error!\n");
	

} 
