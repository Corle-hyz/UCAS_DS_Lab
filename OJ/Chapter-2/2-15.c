#include<stdio.h>
#include<stdlib.h>
typedef struct a{
    int data;
    struct a* p;
}node,*pnode;
int main(){
    int m,n;
    scanf("%d%d",&m,&n);
    node head1,head2;
    head1.data = head2.data = 0;
    head1.p = head2.p = NULL;
    pnode h1,h2,q1,q2,t1,t2;
    // h1 = (pnode)malloc(sizeof(node));
    // h2 = (pnode)malloc(sizeof(node));
    // q1 = (pnode)malloc(sizeof(node));
    // q2 = (pnode)malloc(sizeof(node));
    h1 = q1 = &head1;
    h2 = q2 = &head2;
    for(int i=0;i<m;i++){
        int temp;
        t1 = (pnode)malloc(sizeof(node));
        t1->p = NULL;
        scanf("%d",&temp);
        t1->data = temp;
        q1->p = t1;
        q1 = t1;
    }
    for(int i=0;i<n;i++){
        int temp;
        t2 = (pnode)malloc(sizeof(node));
        t2->p = NULL;
        scanf("%d",&temp);
        t2->data = temp;
        q2->p = t2;
        q2 = t2;
    }
    pnode pr;
    if(m<n){
        q1->p = h2->p;
        pr = head1.p;
    }
    else{
        q2->p = h1->p;
        pr = head2.p;
    }
    while(pr->p){
        printf("%d ",pr->data);
        pr = pr->p;
    }
    printf("%d",pr->data);
    return 0;
}
