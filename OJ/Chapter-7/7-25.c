#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 100
#define CMDL 20
typedef enum{IV,IA,DV,DA,ERR} MODE;
int endSign;
int Digraph[MAXL][MAXL];
int loopJudge(int graph[MAXL][MAXL],int vexNum,int start,int depth);
void Initialize(int arr[MAXL][MAXL]);
int getnum(void);
void buildEdge(int graph[MAXL][MAXL],int s[],int f[],int l[],int vexNum);

void Initialize(int arr[MAXL][MAXL]){
    memset(arr,0,MAXL*MAXL*sizeof(int));
}

void getArr(int s[]){
    endSign = 0;
    for(int i=0;i<MAXL;i++){
        s[i] = getnum();
        if(endSign)
            return;
    }
}

int getnum(void){
    char m;
    int num = 0;
    while((m=getchar())!=EOF && m!='\n' && isdigit(m)){
        num = num*10 + m - '0';
    }
    if(m == '\n' || m == EOF)
        endSign = 1;
    return num;
}

void buildEdge(int graph[MAXL][MAXL],int s[],int f[],int l[],int vexNum){
    for(int i=1;i<=vexNum;i++){
        int p = f[i];
        int q = l[i];
        if(p>=q)
            continue;
        for(int j=p;j<q;j++)
            graph[i][s[j]] = 1;
    }
}

int loopJudge(int graph[MAXL][MAXL],int vexNum,int start,int depth){
    if(depth > vexNum)
        return 1;
    for(int i=1;i<=vexNum;i++)
        if(graph[start][i]==1)
            if(loopJudge(graph,vexNum,i,depth+1))
                return 1;
    return 0;
}

int main(){
    int s[MAXL],f[MAXL],l[MAXL];
    Initialize(Digraph);
    int vexNum;
    vexNum = getnum();
    getArr(s);
    getArr(f);
    getArr(l);
    buildEdge(Digraph,s,f,l,vexNum);
    for(int temp=1;temp<vexNum;temp++){
        if(loopJudge(Digraph,vexNum,temp,1)){
            printf("yes");
            return 0;
        }
    }
    printf("no");
    return 0;
}
