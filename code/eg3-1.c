#include<stdio.h>
int main()
{
	int grade;
	printf("请输入分数：");
	scanf("%d",&grade);
	if(grade<60)
		printf("不及格");
	else if(grade<70) 
		printf("及格");
	else if(grade<80) 
		printf("中等");
	else if(grade<90) 
		printf("良好");
	else 
		printf("优秀");
 } 
