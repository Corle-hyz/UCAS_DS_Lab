#include <bits/stdc++.h>
using namespace std;
char c = '.';
#define BIT 3
#define MAXL 10
typedef struct a{
    int key[BIT];
    int value;
    struct a* next;
}Node,*pNode;

Node head[MAXL];
void distribute(Node input[],int num);
void baseSort(Node input[]);
void collect(Node input[]);
int getnum(void);
void display(Node input[]);


int main(){
    Node input[MAXL];
    int i=0;
    while(c!='\n' && c!=EOF && i<MAXL){
        input[i].value = getnum();
        input[i].key[0] = (input[i].value/1)%10;
        input[i].key[1] = (input[i].value/10)%10;
        input[i].key[2] = (input[i].value/100)%10;
        input[i].next = NULL;
        i++;
    }
    baseSort(input);
    display(input);
    return 0;
}

void baseSort(Node input[]){
    for(int i=0;i<3;i++){
        distribute(input,i);
        collect(input);
    }
}

void distribute(Node input[],int num){
    int k=0;
    for(int i=0;i<MAXL;i++)
        for(int j=0;j<MAXL;j++)
            if(input[j].key[num] == i)
                head[k++] = input[j];
    return;
}

void collect(Node input[]){
    memcpy(input,head,MAXL*sizeof(Node));
    return;
}

void display(Node input[]){
    int i;
    for(i=0;i<MAXL;i++){
        if(i)
            printf(" ");
        printf("%03d",input[i].value);
    }
}

int getnum(void){
    extern char c;
    char m;
    int num = 0;
    int sign = 1;
    while((c=getchar())!=EOF && c!='\n' && (isdigit(c) || c=='-')){
        if(c=='-')
            sign = -1;
        else
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
