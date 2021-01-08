#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define TElemType int
#define MAXL 42

int top = 0;
int Biarr[MAXL];
char c;
int firstnum,secondnum;

void getArr(int arr[]);
int getnum(void);
void Initialize(int arr[]);
void displayElem(int pos);
int searchPre(int m,int n);

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void Initialize(int arr[]){
    memset(arr,0,MAXL*sizeof(int));
}

void getArr(int arr[]){
    extern char c;
    extern int firstnum,secondnum;
    int i = 1;
    int state = 0;
    int mid;
    while (c!=EOF && c!='\n')
    {
        if(c==',')
            i++;
        if(c==';')
            state++;
        mid = getnum();
        switch(state){
            case 0:
                while(mid!=-1 && i!=1 && arr[i/2]==-1)
                    i++;
                arr[i] = mid;
                break;
            case 1:
                firstnum = mid;
                break;
            case 2:
                secondnum = mid;
                break;
            default:
                return;
        }
        
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
        return -1;
    }
    return num*sign;
}

int searchPre(int m,int n){
    int i,j;
    i = j = 0;
    for(int k=1;k<MAXL;k++){
        if(Biarr[k] == m)
            i = k;
        if(Biarr[k] == n)
            j = k;
        if(i!=0 && j!=0)
            break;
    }
    while(i!=j){
        if(i<j)
            j /= 2;
        else 
            i /= 2;
    }
    return i;
}

int main(){
    Initialize(Biarr);
    getArr(Biarr);
    printf("%d",Biarr[searchPre(firstnum,secondnum)]);
    return 0;
}
