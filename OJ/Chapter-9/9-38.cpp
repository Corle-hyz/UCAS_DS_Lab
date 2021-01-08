#include <bits/stdc++.h>
using namespace std;
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
int Bisec[MAXL];
char c;
int count = 0;

void BuildBiTree(BiThrTree T,int pos,int Biarr[]);
void Initialize(int arr[]);
void getArr(int arr[]);
int getnum(void);
void merge(BiThrTree T,BiThrTree Q);
void inOrderDisplay(BiThrTree T);
void insert(BiThrTree T,int val);
int searchBST(BiThrTree T,int key,BiThrTree f,BiThrTree &p);


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

int main(){
    Initialize(Biarr);
    getArr(Biarr);
    BiThrTree T;
    T = (BiThrTree)malloc(sizeof(BiThrNode));
    BuildBiTree(T,1,Biarr);

    Initialize(Bisec);
    getArr(Bisec);
    BiThrTree Q;
    Q = (BiThrTree)malloc(sizeof(BiThrNode));
    BuildBiTree(Q,1,Bisec);
    merge(T,Q);
    inOrderDisplay(T);
    return 0;
}

void merge(BiThrTree T,BiThrTree Q){
    if(!Q)
        return;
    insert(T,Q->data);
    merge(T,Q->lchild);
    merge(T,Q->rchild);
}

void inOrderDisplay(BiThrTree T){
    extern int count;
    if(!T)
        return;
    inOrderDisplay(T->lchild);
    if(count)
        printf(",");
    printf("%d",T->data);
    count++;
    inOrderDisplay(T->rchild);
}

void insert(BiThrTree T,int val){
    BiThrTree p,s;
    searchBST(T,val,NULL,p);
    s = (BiThrTree)malloc(sizeof(BiThrNode));
    s->data = val;
    s->lchild = s->rchild = NULL;
    if(!p)
        T = s;
    else if(val <= p->data)
        p->lchild = s;
    else
        p->rchild = s;
    return;
}

int searchBST(BiThrTree T,int key,BiThrTree f,BiThrTree &p){
    if(!T){
        p = f;
        return 0;
    }else if(T->data >= key)
        return searchBST(T->lchild,key,T,p);
    else 
        return searchBST(T->rchild,key,T,p);
}

// else if(T->data == key){
//         p = T;
//         return 1;
//     }
