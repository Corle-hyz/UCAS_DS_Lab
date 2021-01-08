#include<stdio.h>
#include<stdlib.h>
#define MAXL 100
int find(int data,char arrb[],char arrc[]);
typedef struct a{
    char data;
    struct a* p;
}node,*pnode;

int main(){
    pnode h,q,t,pr;
    node head;
    head.p = NULL;
    head.data = MAXL;
    h = t = &head;
    char temp;
    char b[MAXL],c[MAXL];
    while((temp=getchar()) != EOF && temp!='\n' && temp!=';'){
        q = (pnode)malloc(sizeof(node));
        q->data = temp;
        q->p = NULL;
        t->p = q;
        t = q;
    }
    int i = 0;
    while((temp=getchar()) != EOF && temp!='\n' && temp!=';'){
        b[i++] = temp;
    }
    b[i] = '\0';
    i = 0;
    while((temp=getchar()) != EOF && temp!='\n' && temp!=';'){
        c[i++] = temp;
    }
    c[i] = '\0';
    pr = h;
    t = h->p;
    while(t->p){
        if(find(t->data,b,c)){
            pr->p = t->p;
            t = t->p;
        }
        else{
            //printf("%c,",t->data);
            pr = t;
            t = t->p;
        }
    }
    if(find(t->data,b,c))
        pr->p = NULL;
    q = h->p;
    while(q->p){
        printf("%c,",q->data);
        q = q->p;
    }
    printf("%c",q->data);
    return 0;
}

int find(int data,char arrb[],char arrc[]){
    int in = 0;
    for(int i=0;arrb[i]!='\0';i++){
        if(data == arrb[i]){
            in++;
            break;
        }
    }
    for(int i=0;arrc[i]!='\0';i++){
        if(data == arrc[i]){
            in++;
            break;
        }
    }
    return in==2?1:0;
}
