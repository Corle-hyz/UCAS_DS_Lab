#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
//#define MAXL 100
typedef struct a{
    char c;
    struct a* pre;
    struct a* next;
}node,*pnode;
int main(){
    node head,tail;
    pnode t,p,q;
    t = &head;
    head.c = tail.c = 'a';
    char get;
    while((get=getchar())!='\n' && get!=EOF){
        q = (pnode)malloc(sizeof(node));
        q->c = get;
        t->next = q;
        q->pre = t;
        t = q;
    }
    q->next = &tail;
    tail.pre = q;
    int sign = 0;
    for(p=&head,q=&tail; p!=q && p!=q->next;p=p->next,q=q->pre)
        if(p->c != q->c)
            sign = 1;
    if(sign==0)
        printf("Yes");
    else 
        printf("No");
    return 0;
}
