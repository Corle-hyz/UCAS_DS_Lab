#include<stdio.h>//auto save is a piece of warm light!!!
#include<stdlib.h>
#define MAXL 100
typedef struct a{
    char data;
    struct a* p;
}node,*pnode;

int main(){
    pnode h,q,t;
    node head;
    head.p = NULL;
    head.data = MAXL;
    h = t = &head;
    char temp;
    while((temp=getchar()) != EOF && temp!='\n'){
        q = (pnode)malloc(sizeof(node));
        q->data = temp;
        q->p = t;
        t = q;
    }
    while(t->p){
        printf("%c",t->data);
        t = t->p;
    }
    return 0;
}
