#include<stdio.h>
int main()
{
	int grade;
	printf("�����������");
	scanf("%d",&grade);
	if(grade<60)
		printf("������");
	else if(grade<70) 
		printf("����");
	else if(grade<80) 
		printf("�е�");
	else if(grade<90) 
		printf("����");
	else 
		printf("����");
 } 
