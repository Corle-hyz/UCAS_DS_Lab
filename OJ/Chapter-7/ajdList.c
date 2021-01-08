#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 20
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{
    int data;
    ArcNode *firstarc;
    int MPL;
}VNode,AdjList[MAXL];

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
    int kind;
}ALGrapg;

int endSign;

int main(){

}

voidCreateALGraph(ALGrapg*Gp){
    int i,j,k;
    ArcNode*pe;
    Gp->vexnum = getnum();
    for(i=1;i<=Gp->vexnum;i++){
        Gp->vertices[i].data = i;
        Gp->vertices[i].firstarc = NULL;
    }
    for(endSign = 0;;){
        i = getnum();
        j = getnum();
        pe = (ArcNode*)malloc(sizeof(ArcNode));
        pe->adjvex = j;
        pe->nextarc = Gp->vertices[i].firstarc;
        Gp->vertices[i].firstarc = pe;
        pe = (ArcNode*)malloc(sizeof(ArcNode));
        pe->adjvex = i;
        pe->nextarc = Gp->vertices[j].firstarc;
        Gp->vertices[j].firstarc = pe;
        if(endSign)
            break;
    }
}

void 

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
