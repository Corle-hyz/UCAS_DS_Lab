#include<stdio.h>
int recur(int m,int n);
int main(){
    int m,n;
    int result;
    char c;
    scanf("%d%c%d",&m,&c,&n);
    result = recur(m,n);
    printf("%d",result);
    return 0;
}

int recur(int m,int n){
    return m==0?0:recur(m-1,n*2)+n;
}
