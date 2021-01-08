#include<stdio.h>
#include<string.h>
#define MAXL 100
int main(){
    char s[MAXL];
    char c;
    int i = 0;
    memset(s,sizeof(s),0);
    s[0] = '$';
    while((c=getchar()) != EOF && c!='\n'){
        switch(c){
            case '(':
                s[++i] = 1;
                break;
            case ')':
                if(i>0)
                    s[i--] = 0;
                else
                    printf("0");
                    return 0;
                break;
            default:
                break;
        }
    }
    printf("%d",i==0?1:0);
    return 0;
}
