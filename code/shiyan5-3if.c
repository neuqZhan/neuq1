#include<stdio.h>
void main()
{
	int t;
	printf("please input time:\n");
	scanf("%d",&t);
	if(t>=6&&t<=10)
		printf("上午好");
	else if(t>=11&&t<=13)
		printf("中午好");
	else if(t>=14&&t<=18)
		printf("下午好");
	
	else
		printf("休息时间\n");
	

} 
