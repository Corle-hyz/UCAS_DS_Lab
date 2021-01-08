#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXL 100
int horse(int array[MAXL][MAXL],int i,int j,int row,int column);
void sort(int answer[MAXL],int length);
int main(){
    int array[MAXL][MAXL];
    int answer[MAXL];
    memset(array,0,sizeof(array));
    memset(answer,0,sizeof(answer));
    int row=0,column=0;
    char c;
    while((c=getchar())!='\n' && c!=EOF){
        if(c==','){
            column++;
            continue;
        }else if(c==';'){
            row++;
            column = 0;
            continue;
        }else{
            array[row][column] = array[row][column]*10 + c - '0';
        }
    }
    int i=0,j=0,k=0;
    for(i=0;i<=row;i++)
        for(j=0;j<=column;j++)
            if(horse(array,i,j,row,column))
                answer[k++] = array[i][j];
    if(k==0)
        printf("null");
    else{
        sort(answer,k);
        int first = 1;
        for(int l=0;l<k;l++)
            if(first==1){
                printf("%d",answer[l]);
                first++;
            }
            else 
                printf(",%d",answer[l]);
    }
    return 0;
}
int horse(int array[MAXL][MAXL],int i,int j,int row,int column){
    int sign = 1;
    for(int k=0;k<=column;k++)
        if(array[i][k] < array[i][j])//判断是否是第i行的最小值
            sign = 0;
    for(int k=0;k<=row;k++)
        if(array[k][j] > array[i][j])//判断是否是第j列的最大值
            sign = 0;
    return sign;
}

void sort(int answer[MAXL],int length){
    for(int i=0;i<length;i++)
        for(int j=i;j<length;j++)
            if(answer[i] < answer[j]){
                answer[i] += answer[j];
                answer[j] = answer[i] - answer[j];
                answer[i] = answer[i] - answer[j];
            }
}
