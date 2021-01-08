#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int result = 1;
    while(n!=0){
        result *= n;
        n /= 2;
    }
    printf("%d",result);
    return 0;
}
