#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXL 100
int order[MAXL];

typedef struct s{
    int data;
    int freq;
    struct s* pre;
    struct s* next;
}node,*pnode;

void search(int data,pnode h);
void print(pnode h);
void sort(pnode h);
void change(pnode i,pnode j);

int main(){
    memset(order,sizeof(order),0);
    pnode h,q,t;
    node head = {0,0,NULL,NULL};
    h = t = &head;
    int len = 0;
    int temp;
    scanf("%d",&len);
    for(int i=0;i<len;i++){
        scanf("%d",&temp);
        q = (pnode)malloc(sizeof(node));
        q->data = temp;
        q->freq = 0;
        q->pre = t;
        q->next = NULL;
        t->next = q;
        t = q;
    }
    t->next = h;
    int searchnum;
    int sequence = 1;
    while(scanf("%d",&searchnum) != EOF){
        search(searchnum,h);
        if(order[searchnum]==0)
            order[searchnum] = sequence++;
    }
    sort(h);
    print(h);
    return 0;
}

void search(int data,pnode h){
    pnode t = h->next;
    while(t != h){
        if(t->data == data)
            t->freq++;
        t = t->next;
    }
}

void print(pnode h){
    pnode t = h->next;
    while(t->next != h){
        printf("%d ",t->data);
        t = t->next;
    }
    printf("%d",t->data);
}

void sort(pnode h){
    pnode i,j;
    for(i=h->next;i!=h;i=i->next)
        for(j=i;j!=h;j=j->next)
            if(((i->freq)<(j->freq)) || (((i->freq)==(j->freq)) && (order[i->data]>order[j->data])))
                change(i,j);
    for(i=h->next;i!=h;i=i->next)
        for(j=i;j!=h;j=j->next)
            if(i->freq==0 && j->freq==0 && i->data>j->data)
                change(i,j);
}

void change(pnode i,pnode j){//交换结点实际上就是交换结点里的数据，没必要通过改变前驱和后继的指针来实现交换
    int dt_temp,fq_temp;
    dt_temp = i->data;
    fq_temp = i->freq;
    i->data = j->data;
    i->freq = j->freq;
    j->data = dt_temp;
    j->freq = fq_temp;
}
