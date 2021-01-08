#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define TElemType int
#define MAXL 100
typedef enum {Link,Thread} PointerTag;
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    PointerTag LTag,RTag;
}BiThrNode,*BiThrTree;

BiThrTree pre;
int Biarr[MAXL];
char c;

void BuildBiTree(BiThrTree T,int pos,int Biarr[]);
void Initialize(int arr[]);
void getArr(int arr[]);
int getnum(void);
int isSortBiTree(BiThrTree T);

void BuildBiTree(BiThrTree T,int pos,int Biarr[]){
    if(Biarr[pos]==-1 || pos>=MAXL || !T)
        return;
    T->data = Biarr[pos];
    if(2*pos<MAXL && Biarr[2*pos]!=-1)
        T->lchild = (BiThrTree)malloc(sizeof(BiThrNode));
    else
        T->lchild = NULL;
    if(2*pos+1<MAXL && Biarr[2*pos+1]!=-1)
        T->rchild = (BiThrTree)malloc(sizeof(BiThrNode));
    else
        T->rchild = NULL;
    //T->LTag = T->RTag = Link;
    BuildBiTree(T->lchild,2*pos,Biarr);
    BuildBiTree(T->rchild,2*pos+1,Biarr);
    return;
}


void Initialize(int arr[]){
    memset(arr,-1,MAXL*sizeof(int));
}

void getArr(int arr[]){
    extern char c;
    c = '.';
    int i = 1;
    int mid;
    while (c!=EOF && c!='\n' && c!=';')
    {
        if(c==',')
            i++;
        mid = getnum();
        while(i!=1 && arr[i/2]==-1)
            i++;
        arr[i] = mid;
    }
    arr[0] = i;
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

int main(){
    Initialize(Biarr);
    getArr(Biarr);
    BiThrTree T;
    T = (BiThrTree)malloc(sizeof(BiThrNode));
    BuildBiTree(T,1,Biarr);
    printf("%d",isSortBiTree(T));
    return 0;
}

int isSortBiTree(BiThrTree T){
    if(!T)
        return 1;
    if(T->lchild && T->lchild->data>=T->data)
        return 0;
    if(T->rchild && T->rchild->data<=T->data)
        return 0;
    BiThrTree q;
    q = T->lchild;
    while(q && q->rchild){
        q = q->rchild;
    }
    if(q && T->data<=q->data)
        return 0;
    q = T->rchild;
    while(q && q->lchild){
        q = q->lchild;
    }
    if(q && T->data>=q->data)
        return 0;
    return (isSortBiTree(T->lchild) && isSortBiTree(T->rchild));
}

