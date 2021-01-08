#include <bits/stdc++.h>
using namespace std;

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
void insertSort(pNode T);
int main(){
    pNode T;
    T = (pNode)malloc(sizeof(Node));
    T->next = T->pre = NULL;
    T->key = 0;
    buildList(T);
    insertSort(T);
    display(T);
    return 0;
}

void insertSort(pNode T){
    pNode p,q,temp;
    int num;
    if(!T || !T->next || !T->next->next)
        return;
    p = T->next;
    while(p->next){
        if(p->key > p->next->key){
            q = p;
            num = p->next->key;
            while(q->key > num){
                q->next->key = q->key;
                q = q->pre;
            }
            q->next->key = num;
        }
        p = p->next;
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
            printf(" ");
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
