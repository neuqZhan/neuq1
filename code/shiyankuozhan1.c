#include<stdio.h>
main()
{
	int a=0,b=0,c=0,t=0,s=0,q=0;
	printf("put three numbers:");
	scanf("%d%d%d",&a,&b,&c);
	if(a<b)
	{t=a;
	a=b;
	b=t;
	}
	if(a<c)
	{q=a;
	a=c;
	c=q;
	}
	if(b<c)
	{s=b;
	b=c;
	c=s;
	}
	printf("最小的数为%d",c);
}
