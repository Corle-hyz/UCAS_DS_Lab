#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdarg.h>
#define MAXL 8

typedef struct a{
    int data;
    struct a* pre;
    struct a* next;
}node,*pnode;

void display(int dim,int len,int* position,int *p);
int getsize(int dim,int len);
int power(int len,int times);

int main(){
    int i=0;
    int dim=0,len=0;
    char c;
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
    int size = 0;
    size = getsize(dim,len);
    int *postion,*p,*q;
    postion = (int*)malloc((size+1) * sizeof(int));
    if(!postion)
        return -1;
    p = postion;
    int count = 0;
    int state = 1;
    while((c=getchar())!='\n' && c!=EOF){
        if(isdigit(c) && state==0)
            *p = (*p)*10 + c - '0';
        else if(isdigit(c) && state==1){
            *p = c-'0';
            state = 0;
            //p++;
        }
        else{
            if(state==0)
                p++;
            state = 1;
        }
    }
    p--;
    display(dim,len,postion,p);
    return 0;
}

int getsize(int dim,int len){
    int i=0,temp=1;
    while(i++<dim)
        temp *= len;
    return temp;
}

void display(int dim,int len,int* position,int *p){
    int times = getsize(dim,len);
    //times = len*len*a + len*b + c + 1
    int a,b,c;
    int sign = 0;
    for(int i=times-1;i>=0;i--,p--){
        if(*p != 0){
            if(sign)
                printf("+");
            sign = 1;
            if(*p != 1 || i==0)
                printf("%d",*p);
            for(int j=1;j<=dim;j++){
                int temp = (i/power(len,dim-j))%len;
                switch(temp){
                    case 0: break;
                    case 1: printf("x%d",j);
                            break;
                    default:
                        printf("x%dE%d",j,temp);
                }
            }
        }
    }
}

int power(int len,int times){
    int result = 1;
    for(int i=0;i<times;i++)
        result *= len;
    return result;
}
