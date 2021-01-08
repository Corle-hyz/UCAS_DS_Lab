#include <bits/stdc++.h>
using namespace std;

#define MAXL 20
char c;
int count = 0;
typedef struct a{
    int key;
    struct a* pre;
    struct a* next;
}Node,*pNode;
int getnum(void);
void buildList(pNode T);
void display(pNode T);
void chooseSort(pNode T);
int main(){
    pNode T;
    T = (pNode)malloc(sizeof(Node));
    T->next = T->pre = NULL;
    T->key = 0;
    buildList(T);
    chooseSort(T);
    display(T);
    return 0;
}

void chooseSort(pNode T){
    pNode p,q,pos;
    pos = T->next;
    while(pos){
        p = q = pos;
        while(p){
            if(p->key < q->key)
                q = p;
            p = p->next;
        }
        if(q==pos){
            pos = pos->next;
            continue;
        }
        pos->key = pos->key + q->key;
        q->key = pos->key - q->key;
        pos->key = pos->key - q->key;
        pos = pos->next;
    }
}

void display(pNode T){
    extern int count;
    pNode p;
    if(!T || !T->next)
        return;
    p = T->next;
    while (p)
    {
        if(count)
            printf(",");
        printf("%d",p->key);
        count++;
        p = p->next;
    }
}

void buildList(pNode T){
    c = '.';
    pNode p,q;
    p = T;
    int mid;
    while (c!=EOF && c!='\n' && c!=';'){
        mid = getnum();
        if(mid==-1)
            return;
        q = (pNode)malloc(sizeof(Node));
        p->next = q;
        q->pre = p;
        p = q;
        q->key = mid;
        q->next = NULL;
    }
}

int getnum(void){
    extern char c;
    char m;
    int num = 0;
    int sign = 1;
    while((c=getchar())!=EOF && c!='\n' && isdigit(c)){
        if(c=='-')
            sign = -1;
        num = num*10 + c - '0';
    }
    if(c=='n'){
        m = getchar();
        m = getchar();
        m = getchar();
        c = getchar();
        return -1;
    }
    return num*sign;
}
