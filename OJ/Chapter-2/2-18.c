#include<stdio.h>
#include<stdlib.h>
typedef struct a{
    int data;
    struct a* p;
}node,*pnode;

int main(){
    pnode h,q,t;
    node head;
    head.p = NULL;
    h = t = &head;
    int length,position;
    scanf("%d%d",&length,&position);
    for(int i=0;i<length;i++){
        q = (pnode)malloc(sizeof(node));
        int temp;
        scanf("%d",&temp);
        q->data = temp;
        q->p = NULL;
        t->p = q;
        t = q;
    }
    if(length==1){
        printf("NULL");
        return 0;
    }
    int i=0;
    q = h->p;
    while(i<position-1){
        i++;
        q = q->p;
    }
    q->p = q->p->p;
    for(q=h->p;q->p!=NULL;q=q->p)
        printf("%d ",q->data);
    printf("%d",q->data);
    return 0;

}
