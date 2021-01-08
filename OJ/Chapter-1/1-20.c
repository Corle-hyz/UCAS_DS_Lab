#include<stdio.h>
#define MAXLEN 50
int power(int base,int times);
int main()
{
    int n,x;
    int result = 0;
    int arr[MAXLEN];
    scanf(" %d %d",&n,&x);
    for(int i=0;i<n;i++)
    {
        scanf(" %d",&arr[i]);
        result += arr[i]*power(x,i);
    }
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
