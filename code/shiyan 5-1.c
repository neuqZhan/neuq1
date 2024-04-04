#include<stdio.h>
int main()
{
	float a,b;
	char c;
	printf("please input:\n");
	scanf("%f%c%f",&a,&c,&b);
	switch(c){
	case '+':printf("a+b=%f\n",a+b);break;
	case '-':printf("a-b=%f\n",a-b);break;
	case '*':printf("a*b=%f\n",a*b);break;
	case '/':printf("a/b=%f\n",a/b);break;
	default:printf("input error!\n");
	}

} 
