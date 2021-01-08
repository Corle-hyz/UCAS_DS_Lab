#include<stdio.h>
#define MAXINT 65535
#define ARRSIZE 300
#define BASE 2
#define FACT 7
#define LIM "46080"
int power(int base,int times);
int factor(int n);
int main()
{
    //char c1,c2;
    int n;
    scanf("%d",&n);
    int result = 1;
    result = power(BASE,n-1) * factor(n-1);
    if(n>FACT)
        printf(LIM);
    else
        printf("%d",result);
    return 0;
}

int power(int base,int times)
{
    int result = 1;
    for(int i=0;i<times;i++)
        result *= base;
    return result;
}

int factor(int n)
{
    int result = 1;
    for(int i=0;i<n;i++)
        result *= (i+1);
    return result;
}
