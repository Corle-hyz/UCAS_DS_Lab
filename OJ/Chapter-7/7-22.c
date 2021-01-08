#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 100
#define CMDL 20
typedef enum{IV,IA,DV,DA,ERR} MODE;

int Digraph[MAXL][MAXL];
int zeroSign = 0;//zeroSign==1表示从0开始
int operator1,operator2;
int search(int arr[MAXL][MAXL],int vexNum,int start,int end);

void Initialize(int arr[MAXL][MAXL]);
void getEdge(int array[MAXL][MAXL]);
int getop(char s[]);
int getop2(char s[]);
int getnum(void);

void Initialize(int arr[MAXL][MAXL]){
    memset(arr,0,MAXL*MAXL*sizeof(int));
}

int getop(char s[]){
    char m;
    int num = 0;
    int i=0;
    while(s[i]!='\0' && s[i]!='\n' && s[i]!=','){
        if(!isdigit(s[i])){
            i++;
            continue;
        }
        num = num*10 + s[i++] - '0';
    }
    return num;
}

int getop2(char s[]){
    char m;
    int num = 0;
    int i=0;
    while(s[i++]!=',')
        ;
    while(s[i]!='\0' && s[i]!='\n' && s[i]!=')'){
        num = num*10 + s[i++] - '0';
    }
    return num;
}

int getnum(void){
    char m;
    int num = 0;
    while((m=getchar())!=EOF && m!='\n' && isdigit(m)){
        num = num*10 + m - '0';
    }
    return num;
}

void getEdge(int array[MAXL][MAXL]){
    char c = '\0';
    int pos = 1;
    int num = 0;
    int row,column;
    row = column = 0;
    while(c!='\n'){
        c=getchar();
        if(c=='-'){
            pos = 2;
            continue;
        }
        if(c==',' || c=='\n')
            pos = 0;
        switch(pos){
            case 0:
                Digraph[row][column] = 1;
                if(row==0 || column==0)
                    zeroSign = 1;
                row = column = 0;
                pos = 1;
                break;
            case 1:
                row = row + c - '0';
                break;
            case 2:
                column = column + c - '0';
                break;
            default:
                break;
        }
    }
}

int search(int arr[MAXL][MAXL],int vexNum,int start,int end){
    if(arr[start][end]==1){
        return 1;
    }
    for(int i=0;i<=vexNum;i++){
        if(arr[start][i]==1)
            if(search(arr,vexNum,i,end))
                return 1;
    }
    return 0;
}


int main(){
    int vexNum;
    vexNum = getnum();
    getEdge(Digraph);
    int start,end;
    start = getnum();
    end = getnum();
    if(search(Digraph,vexNum,start,end))
        printf("yes");
    else
        printf("no");
    return 0;
}
