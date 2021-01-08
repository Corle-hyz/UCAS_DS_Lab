#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define TElemType int
#define MAXL 99
#define PLUS -11
#define SUB -12
#define TIMES -13
#define DIV -14

int Biarr[MAXL];
char c;

void getArr(int arr[]);
int getnum(void);
void Initialize(int arr[]);
int levelCompare(int i,int j);
void Display(int k);
int IsOperation(int k);
void InOrderTraverse(int k);

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void Initialize(int arr[]){
    memset(arr,-1,MAXL*sizeof(int));
}

void getArr(int arr[]){
    extern char c;
    int i = 1;
    int mid;
    while (c!=EOF && c!='\n')
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
    if(c=='+' || c=='-' || c=='*' || c=='/'){
        int s = (c=='+'?PLUS:(c=='-'?SUB:(c=='*'?TIMES:DIV)));
        c = getchar();
        return s;
    }
    return num*sign;
}

int levelCompare(int i,int j){//i at left and j at right
    switch(Biarr[i]){
        case PLUS:
            return 0;
        case SUB:
            if(Biarr[j]==PLUS || Biarr[j]==SUB)
                return 1;
            else
                return 0;
        case TIMES:
            if(Biarr[j]==TIMES)
                return 0;
            else
                return 1;
        case DIV:
            return 1;
        default:
            return 1;
    }
}

void Display(int k){
    switch(Biarr[k]){
        case PLUS:
            printf("+");
            break;
        case SUB:
            printf("-");
            break;
        case TIMES:
            printf("*");
            break;
        case DIV:
            printf("/");
            break;
        default:
            printf("%d",Biarr[k]);
    }
}

int IsOperation(int k){
    if(Biarr[k]==PLUS || Biarr[k]==SUB || Biarr[k]==TIMES || Biarr[k]==DIV)
        return 1;
    else
        return 0;
}

void InOrderTraverse(int k){
    int para = 0;
    if(Biarr[k]==-1)
        return;
    if(IsOperation(k) && IsOperation(k/2))
        if(levelCompare(k/2,k))
            para = 1;
    if(para)
        printf("(");
    InOrderTraverse(2*k);
    Display(k);
    InOrderTraverse(2*k+1);
    if(para)
        printf(")");
    return;
}

int main(){
    Initialize(Biarr);
    getArr(Biarr);
    InOrderTraverse(1);
    return 0;
}
