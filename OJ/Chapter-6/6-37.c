#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define TElemType int
#define MAXL 42

int top = 0;
int Biarr[MAXL];
char c;

void getArr(int arr[]);
int getnum(void);
int getTop(int a[]);
void Initialize(int arr[]);
void push(int a[],int pos);
void pop(void);
void displayElem(int pos);
void PreOrderTraverse(void);

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void Initialize(int arr[]){
    memset(arr,0,MAXL*sizeof(int));
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
        while(mid!=0 && i!=1&& arr[i/2]==0)
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
        return 0;
    }
    return num*sign;
}

void push(int a[],int pos){
    a[top++]=pos;
}

void pop(void){
    if (top==0) {
        return;
    }
    top--;
}

void displayElem(int pos){
    printf(",%d",Biarr[pos]);
}

int getTop(int a[]){
    if(top!=0)
        return a[top-1];
    else 
        return 0;
}
//先序遍历非递归算法
void PreOrderTraverse(void){
    int a[MAXL];
    int k = 0;
    int temp;
    push(a,1);
    while(top!=0){
        temp = getTop(a);
        pop();
        while(Biarr[temp]){
            if(k==0){
                printf("%d",Biarr[temp]);
                k++;
            }
            else
                displayElem(temp);
            if(Biarr[2*temp+1])
                push(a,2*temp+1);
            temp *= 2;
        } 
    }
}

int main(){
    Initialize(Biarr);
    getArr(Biarr);
    //printf("先序遍历: \n");
    PreOrderTraverse();
    return 0;
}
