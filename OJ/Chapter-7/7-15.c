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

void displayVex(int array[MAXL][MAXL],int number);
void Initialize(int arr[MAXL][MAXL]);
void getEdge(int array[MAXL][MAXL]);
void displayGraph(int array[MAXL][MAXL],int number,int remain);
int getop(char s[]);
int getop2(char s[]);
int getnum(void);
void displayVex(int array[MAXL][MAXL],int number);

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

void displayGraph(int array[MAXL][MAXL],int number,int remain){
    int playnum = 1;
    int inLineNum = 0;
    for(int i=1-zeroSign;i<=number-zeroSign;i++){
        if(array[i][0]==-1)
            continue;
        inLineNum = 0;
        for(int j=1-zeroSign;j<=number-zeroSign;j++){
            if(array[i][j]!=-1){
                printf("%d",array[i][j]);
                inLineNum++;
                if(inLineNum < remain)
                    printf(",");
            }
        }
        if(playnum < remain)
            printf("\n");
        playnum++;
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


MODE getCommand(){
    char cmd[CMDL];
    if(scanf("%s",cmd)==EOF)
        return ERR;
    MODE command;
    switch(cmd[0]){
        case 'I':
            if(cmd[1]=='V'){
                command = IV;
                operator1 = getop(cmd);
            }
            else{
                command = IA;
                operator1 = getop(cmd);
                operator2 = getop2(cmd);
            }
            break;
        case 'D':
            if(cmd[1]=='V'){
                command = DV;
                operator1 = getop(cmd);
            }
            else{
                command = DA;
                operator1 = getop(cmd);
                operator2 = getop2(cmd);
            }
            break;
        default:
            command = ERR;
    }
    return command;
}
int main(){
    int vexNum,edgeNum,reduce;
    vexNum = getnum();
    reduce = 0;
    getEdge(Digraph);
    MODE command;
    while((command=getCommand())!=ERR){
        switch(command){
            case IV:
                vexNum++;
                break;
            case IA:
                Digraph[operator1][operator2] = 1;
                break;
            case DV:
                for(int i=0;i<MAXL;i++){
                    Digraph[operator1][i] = -1;
                    Digraph[i][operator1] = -1;
                }
                reduce++;
                break;
            case DA:
                Digraph[operator1][operator2] = 0;
                break;
            default:
                break;
        }
    }
    displayGraph(Digraph,vexNum,vexNum-reduce);
    return 0;
}
