#include<stdio.h>
main()
{
	int i,a[3];
	int min;
	printf("input three numbers:"); 
	for(i=0;i<3;i++)
	{
		scanf("%d",&a[i]);
		
	}
	min=a[0];
	for(i=0;i<3;i++)
	{
		
			if(min>a[i])
			min=a[i];
	}
	printf("��С����Ϊ:%d",min); 
}
