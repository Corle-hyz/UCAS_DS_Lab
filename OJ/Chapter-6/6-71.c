#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 100

char Biarr[MAXL];

void Initialize(char arr[]);
void getArr(char arr[]);
char getnum(void);
void display(int pos,int depth);

void Initialize(char arr[]){
    for(int i=0;i<MAXL;i++)
        arr[i] = '$';
}

void getArr(char arr[]){
    int i = 1;
    char mid;
    mid = '.';
    while (mid!=EOF && mid!='\n' && mid!=';')
    {
        mid = getnum();
        if(mid == '\n')
            break;
        if(mid==',')
            i++;
        else{
            while(i!=1 && arr[i/2]=='$')
                i++;
            arr[i] = mid;
        }
    }
}

char getnum(void){
    char m;
    if((m=getchar())!=EOF && m!='\n' && m!='n' && isalpha(m)){
        return m;
    }
    if(m=='n'){
        m = getchar();
        m = getchar();
        m = getchar();
        return '$';
    }
    return m;
}

void display(int pos,int depth){
    if(pos>=MAXL || Biarr[pos]=='$')
        return;
    if(depth>0)
        for(int k=0;k<depth;k++)
            printf(" ");
    printf("%c\n",Biarr[pos]);
    display(2*pos,depth+1);
    display(2*pos+1,depth);
    return;
}


int main(){
    Initialize(Biarr);
    getArr(Biarr);
    display(1,0);
    return 0;
}

