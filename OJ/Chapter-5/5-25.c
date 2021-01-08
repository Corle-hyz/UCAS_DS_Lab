#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdarg.h>
#define MAXL 200

typedef struct a{
    int data;
    struct a* pre;
    struct a* next;
}node,*pnode;

int main(){
    int i=0;
    int dim=0,len=0;
    char c;
    char input[MAXL];
    while(i<2 && (c=getchar())!=EOF){
        if(c==';'){
            i++;
            continue;
        }
        else if(i==0)
            dim = dim*10 + c - '0';
        else
            len = len*10 + c - '0';
    }
    i = 0;
    while((c=getchar())!='\n' && c!=EOF)
        input[i++] = c;
    input[i] = '\0';
    int sign = 1;
    int order = 1;
    int state = 1;
    int j=0;
    int temp = 0;
    printf("[");
    while(input[j]!='\0'){
        if(input[j]=='-')
            sign = -1;
        if(isdigit(input[j]) && state==0)
            temp = temp*10 + input[j] - '0';
        else if(isdigit(input[j]) && state==1 && input[j]!='0'){
            temp = input[j]-'0';
            state = 0;
        }
        else if(temp!=0 && state==0){
            temp *= sign;
            sign = 1;
            if(order){
                printf("%d",temp);
                order = 0;
            }
            else
                printf(",%d",temp);
        }
        if(!isdigit(input[j]) && input[j]!='-'){
            temp = 0;
            state = 1;
        }
        j++;
    }
    printf("];");
    state = 1;
    j=0;
    temp = 0;
    while(input[j]!='\0'){
        if(isdigit(input[j]) && state==0)
            temp = temp*10 + input[j] - '0';
        else if(isdigit(input[j]) && state==1){
            temp = input[j]-'0';
            state = 0;
        }
        else{
            if(temp==0 && state==0)
                printf("0");
            else if(temp!=0 && state==0)
                printf("1");
        }
        if(!isdigit(input[j]) && input[j]!='-'){
            printf("%c",input[j]);
            temp = 0;
            state = 1;
        }
        j++;
    }
    return 0;
}
