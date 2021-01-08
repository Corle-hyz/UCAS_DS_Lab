#include<stdio.h>
#include<stdlib.h>
#define MAXL 100
typedef struct a{
    int data;
    struct a* p;
}node,*pnode;

int main(){
    pnode h,q,t;
    node head;
    head.p = NULL;
    head.data = MAXL;
    h = t = &head;
    pnode back1,back2;//记录最后两个数的值
    int temp;
    back1 = back2 = &head;
    while(scanf("%d",&temp) != EOF){
        q = (pnode)malloc(sizeof(node));
        q->data = temp;
        q->p = NULL;
        t->p = q;
        t = q;
        back2 = back1;
        back1 = t;
    }
    int mink = back2->data;
    int maxk = back1->data;
    pnode search;
    search = h;
    //printf("\n");
    while(search->p){
        int temp2 = search->p->data;
        if((temp2>mink && temp2<maxk) || (search->p==back2 || search->p==back1))
            search->p = search->p->p;
        else
        	search = search->p;
    }
    search = h->p;
    while(search->p){
        printf("%d ",search->data);
        search = search->p;
    }
    printf("%d",search->data);
    return 0;
}
