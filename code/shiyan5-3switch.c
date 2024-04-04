#include<stdio.h>
int main()
{
	int t;
	printf("请输入整数时间:\n");
	scanf("%d",&t);
	switch(t){
	case (6):
	case (7):
	case (8):	
	case (9):
	case (10): printf("上午好\n");break;
	case (11):
	case (12):	
	case (13): printf("中午好\n");break;
	case (14):
	case (15):
	case (16):	
	case (17):
	case (18):printf("下午好\n");break;
	
	default:printf("休息时间\n");
	}

} 
