#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 100
int Digraph[MAXL][MAXL];
int zeroSign = 0;//zeroSign==1表示从0开始

void displayVex(int array[MAXL][MAXL],int number);
void Initialize(int arr[MAXL][MAXL]);
void getEdge(int array[MAXL][MAXL],int number);
void displayGraph(int array[MAXL][MAXL],int number);

void Initialize(int arr[MAXL][MAXL]){
    memset(arr,0,MAXL*MAXL*sizeof(int));
}

int getnum(void){
    char m;
    int num = 0;
    while((m=getchar())!=EOF && m!='\n' && isdigit(m)){
        num = num*10 + m - '0';
    }
    return num;
}

void getEdge(int array[MAXL][MAXL],int number){
    int row,column;
    for(int i=0;i<number;i++){
        row = getnum();
        column = getnum();
        if(row==0 || column==0)
            zeroSign = 1;
        array[row][column] = 1;
    }
}

void displayGraph(int array[MAXL][MAXL],int number){
    for(int i=0;i<number;i++){
        for(int j=0;j<number;j++){
            printf("%d",array[i][j]);
            if(j!=0 && j!=number-1)
                printf(",");
        }
        if(i!=number-1)
            printf("\n");
    }
}

void displayVex(int array[MAXL][MAXL],int number){
    for(int i=1-zeroSign;i<=number-zeroSign;i++){
        printf("%d",i);
        int count = 0;
        for(int j=number-zeroSign;j>0-zeroSign;j--)
            if(array[i][j]==1){
                if(!count){
                    printf(" %d",j);
                    count++;
                }
                else 
                    printf(",%d",j);
            }
        if(i!=number-zeroSign)
            printf("\n");
    }
}

int main(){
    int vexNum,edgeNum;
    vexNum = getnum();
    edgeNum = getnum();
    getEdge(Digraph,edgeNum);
    displayVex(Digraph,vexNum);
    return 0;
}
