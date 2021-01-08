#include <bits/stdc++.h>
using namespace std;

#define MAXL 50
char c;
int count = 0;
typedef struct a{
    int key;
    struct a* pre;
    struct a* next;
}Node,*pNode;
int getnum(void);
void buildList(pNode T);
void display(int arr[]);
void sort(pNode T,int arr[]);


int main(){
    int arr[MAXL];
    pNode T;
    T = (pNode)malloc(sizeof(Node));
    T->next = T->pre = NULL;
    T->key = 0;
    buildList(T);
    sort(T,arr);
    display(arr);
    return 0;
}

void sort(pNode T,int arr[]){
    pNode p,q,temp;
    if(!T)
        return;
    temp = T->next;
    int pre = -999;
    int i=1;
    pNode Min;
    Min = (pNode)malloc(sizeof(Node));
    Min->key = 888;
    Min->next = Min->pre = NULL;
    while(temp){
        for(p=T->next,q=Min;p;p=p->next){
            if(p->key<=q->key && p->key>=pre)
                q = p;
        }
        if(q->key<pre){
            for(p=T->next,q=Min;p;p=p->next)
                if(p->key>=q->key && p->key>=pre)
                    q = p;
        }
        arr[i++] = q->key;
        pre = q->key;
        q->key = 888;
        temp = temp->next;
    }
    arr[0] = i-1;
}

void display(int arr[]){
    for(int i=1;i<=arr[0];i++){
        if(i-1)
            printf(" ");
        printf("%d",arr[i]);
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
    while((c=getchar())!=EOF && c!='\n' && (isdigit(c) || c=='-')){
        if(c=='-')
            sign = -1;
        else
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
