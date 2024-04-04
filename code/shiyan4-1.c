#include<stdio.h>
void main()
{
    int a=0,b=0,h=0;
    scanf("%d%d%d",&a,&b,&h);
    if (a==b&&b==h&&h==a)
        printf("这是正方体");
    else
        printf("这是长方体");

}

