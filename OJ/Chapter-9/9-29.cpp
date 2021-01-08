#include <bits/stdc++.h>
using namespace std;
int getnum(char& m);
typedef struct a{
    int key;
    struct a* next;
}Node,*pNode;

int main(){
    pNode h,t,temp;
    h = (pNode)malloc(sizeof(Node));
    temp = t = h;
    char c = ',';
    int num;
    while(c!=';'){
        num = getnum(c);
        if(temp!=t){
            temp = (pNode)malloc(sizeof(Node));
            t->next = temp;
        }
        t = temp;
        temp->key = num;
        temp = temp->next;
    }
    t->next = h;
    t = h;
    while(c!='\n'){
        num = getnum(c);
        while(t->key != num){
            printf("%d,",t->key);
            if(t->key < num)
                t = t->next;
            else
                t = h;
        }
        printf("%d",t->key);
        if(c!='\n')
            printf(";");
    }
}

int getnum(char& m){
    int num = 0;
    int sign = 1;
    while((m=getchar())!=EOF && m!='\n' && (isdigit(m) || m=='-')){
        if(m=='-')
            sign = -1;
        else
            num = num*10 + m - '0';
    }
    return num*sign;
}
