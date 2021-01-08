#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define TElemType int
#define MAXL 42

int Biarr[MAXL];
char c;

void getArr(int arr[]);
int getnum(void);
void Initialize(int arr[]);
int totalBiTree(void);

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
    while((c=getchar())!=EOF && c!='\n' && (isdigit(c)||c=='-')){
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

int totalBiTree(void){
    int state = 0;
    int i;
    for(i=1;i<MAXL;i++){
        if(state==0 && Biarr[i]==-1)
            state = 1;
        if(state==1 && Biarr[i]!=-1)
            state = -1;
    }
    return state==-1?0:1;
}

int main(){
    Initialize(Biarr);
    getArr(Biarr);
    printf("%d",totalBiTree());
    return 0;
}
