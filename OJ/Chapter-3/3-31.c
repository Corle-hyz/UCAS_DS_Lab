#include<stdio.h>
#include<string.h>
#define MAXL 100
int main(){
    char s[MAXL];
    scanf("%s",s);
    int len,i,j;
    int sign = 1;
    len = strlen(s);
    for(i=0,j=len-2;i<j;i++,j--){
        if(s[i] == s[j])
            continue;
        else{
            sign = 0;
            break;
        }
    }
    printf("%d",sign);
    return 0;
}
