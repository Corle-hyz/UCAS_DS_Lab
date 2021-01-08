#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#define MAXL 100

char c = '0';
int getnum(void);
int search(int s[],int t[],int a,int b);
int getnum(void){
    extern char c;
    int num = 0;
    int sign = 1;
    while((c=getchar())!=EOF && c!='\n' && (isdigit(c)||c=='-')){
        if(c=='-')
            sign = -1;
        num = num*10 + c - '0';
    }
    return num*sign;
}

int main(){
    int leftArr[MAXL],rightArr[MAXL];
    int i=0,j=0;
    int flag = 0;
    int a,b;
    extern char c;
    while(c!=EOF && c!='\n'){
        if(c==';')
            flag++;
        switch(flag){
            case 0:
                leftArr[i++] = getnum();
                break;
            case 1:
                rightArr[j++] = getnum();
                break;
            case 2:
                b = getnum();
            case 3:
                a = getnum();
            default:
                break;
        }
    }

    if(search(leftArr,rightArr,a,b))
        printf("1");
    else
        printf("0");
    return 0;
}

int search(int s[],int t[],int a,int b){
    if(s[a]==0 && t[a]==0)
        return 0;
    if(s[a]==b || t[a]==b)
        return 1;
    int exist;
    exist = (search(s,t,s[a],b) || search(s,t,t[a],b))?1:0;
    return exist;
}
