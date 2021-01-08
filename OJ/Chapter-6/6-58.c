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
int secArr[MAXL];
char c;
int traverseNum = 0;

void InOrderThreading(BiThrTree Thrt, BiThrTree T);
void BuildBiTree(BiThrTree T,int pos,int Biarr[]);
void InOrderTraverse(BiThrTree Thrt);
int Visit(BiThrTree p);
void InThreading(BiThrTree T);
void Initialize(int arr[]);
void getArr(int arr[]);
int getnum(void);
BiThrTree searchNode(BiThrTree T,int opnode);
void sortTree(BiThrTree T,BiThrTree secTree,int opnode);


void InOrderThreading(BiThrTree Thrt, BiThrTree T){
    if(!Thrt)
        return;
    Thrt->LTag = Link;
    Thrt->RTag = Thread;
    Thrt->rchild = Thrt;
    if(!T)
        Thrt->lchild = Thrt;
    else{
        Thrt->lchild = T;
        pre = Thrt;
        InThreading(T);
        pre->rchild = Thrt;
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
    return;
}

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
    T->LTag = T->RTag = Link;
    BuildBiTree(T->lchild,2*pos,Biarr);
    BuildBiTree(T->rchild,2*pos+1,Biarr);
    return;
}

void InOrderTraverse(BiThrTree Thrt){
    BiThrTree p;
    p = Thrt->lchild;
    while(p!=Thrt){
        while(p->LTag==Link)
            p = p->lchild;
        if(!Visit(p))
            return;
        while(p->RTag==Thread && p->rchild!=Thrt){
            p = p->rchild;
            Visit(p);
        }
        p = p->rchild;
    }
    return;
}

int Visit(BiThrTree p){
    extern int traverseNum;
    if(!p || !(p->lchild) || !(p->rchild))
        return 0;
    else{
        if(!traverseNum){
            printf("%d,%d,%d,%d",p->LTag,p->lchild->data,p->RTag,p->rchild->data);
            traverseNum++;
        }
        else
            printf(";%d,%d,%d,%d",p->LTag,p->lchild->data,p->RTag,p->rchild->data);
        return 1;
    }
}

void InThreading(BiThrTree T){
    if(T){
        InThreading(T->lchild);
        if(!(T->lchild)){
            T->LTag = Thread;
            T->lchild = pre;
        }
        if(!(pre->rchild)){
            pre->RTag = Thread;
            pre->rchild = T;
        }
        pre = T;
        InThreading(T->rchild);
    }
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
        while(mid!=-1 && i!=1 && arr[i/2]==-1)
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

void sortTree(BiThrTree T,BiThrTree secTree,int opnode){
    BiThrTree temp;
    temp = searchNode(T,opnode);
    if(!temp->lchild)
        temp->lchild = secTree;
    else {
        secTree->rchild = temp->lchild;
        temp->lchild = secTree;
    }
    return;
}

BiThrTree searchNode(BiThrTree T,int opnode){
    if(!T || T->data == opnode)
        return T;
    else{
        BiThrTree temp;
        temp = searchNode(T->lchild,opnode);
        return temp?temp:searchNode(T->rchild,opnode);
    }
}

int main(){
    Initialize(Biarr);
    getArr(Biarr);
    Initialize(secArr);
    getArr(secArr);
    BiThrTree T,Thrt,secTree;
    int opnode;
    T = (BiThrTree)malloc(sizeof(BiThrNode));
    Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    secTree = (BiThrTree)malloc(sizeof(BiThrNode));
    Thrt->data = 0;
    BuildBiTree(T,1,Biarr);
    BuildBiTree(secTree,1,secArr);
    opnode = getnum();
    sortTree(T,secTree,opnode);
    InOrderThreading(Thrt,T);
    InOrderTraverse(Thrt);
    return 0;
}

