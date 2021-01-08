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

void BuildBiTree(BiThrTree T,int low,int high,int left,int right);
void Initialize(int arr[]);
void getArr(int arr[]);
int getnum(void);
int search(int secArr[],int node);


void BuildBiTree(BiThrTree T,int low,int high,int left,int right){
    int node = Biarr[low];
    T->data = node;
    int inOrderPos;
    inOrderPos = search(secArr,node);
    int N1 = inOrderPos - left;
    int N2 = right - inOrderPos;
    if(low==high){
        T->lchild = NULL;
        T->rchild = NULL;
        return;
    }
    if(inOrderPos==left)
        T->lchild = NULL;
    else{
        T->lchild = (BiThrTree)malloc(sizeof(BiThrNode));
        BuildBiTree(T->lchild,low+1,low+N1,left,inOrderPos-1);
    }
    if(inOrderPos==right)
        T->rchild = NULL;
    else{
        T->rchild = (BiThrTree)malloc(sizeof(BiThrNode));
        BuildBiTree(T->rchild,low+N1+1,high,inOrderPos+1,right);
    }
    return;
}

int search(int secArr[],int node){
    int i=1;
    while(secArr[i++] != node) ;
    return i-1;
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

void PoseOrderTraverse(BiThrTree T){
    if(!T)
        return;
    PoseOrderTraverse(T->lchild);
    PoseOrderTraverse(T->rchild);
    if(!traverseNum){
        printf("%d",T->data);
        traverseNum++;
    }else 
        printf(",%d",T->data);
    return;
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
    Initialize(secArr);
    getArr(secArr);
    BiThrTree T;
    T = (BiThrTree)malloc(sizeof(BiThrNode));
    BuildBiTree(T,1,Biarr[0],1,secArr[0]);
    PoseOrderTraverse(T);
    return 0;
}

