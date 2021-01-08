#include<stdio.h>
#include<stdlib.h>
typedef struct a{
    char elem;
    struct a* next;
}Queue,*pQueue;

int main(){
    int num;
    scanf("%d",&num);
    getchar();
    pQueue tail,q;
    tail = (pQueue)malloc(sizeof(Queue));
    // q = (pQueue)malloc(sizeof(Queue));
    // tail->next = q;
    // tail = q;
    tail->next = tail;
    char c;
    while((c=getchar())!=EOF && c!='\n'){
        q = (pQueue)malloc(sizeof(Queue));
        q->elem = c;
        q->next = tail->next;
        tail->next = q;
        tail = q;
    }
    tail->next = tail->next->next;
    for(int i=0;i<num*2-1;i++){
        printf("%c",tail->next->elem);
        tail = tail->next;
    }
    return 0;

}
