#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXL 100
typedef struct a{
    char data;
    struct a* succ;
    struct a* next;
    int order;
}node,*pnode;

int KMP(pnode head1,pnode head2,int pos,int length2);
void get_nextval(pnode head,int length);

int main(){
    node head1,head2;
    head1.succ = head1.next = head2.succ = head2.next = NULL;
    pnode t,q;
    t = &head1;
    //int next[MAXL];
    char c;
    int k = 0;
    int length1 = 0;
    head1.order = head2.order = 0;
    while((c=getchar())!='\n' && c!=EOF){
        //ordernum++;
        q = (pnode)malloc(sizeof(node));
        q->data = c;
        t->succ = q;
        q->next = t;
        q->succ = NULL;
        t = q;
        length1++;
        q->order = length1;
    }
    //q->next->succ = NULL;
    //free(q);
    t = &head2;
    int length2 = 0;
    while((c=getchar())!='\n' && c!=EOF){
        q = (pnode)malloc(sizeof(node));
        q->data = c;
        t->succ = q;
        q->next = t;
        q->succ = NULL;
        t = q;
        length2++;
        q->order = length2;
    }
    //q->next->succ = NULL;
    //free(q);
    get_nextval(&head2,length2);
    //t = &head1;
    int num = 0;
    int pos = 1;
    /*int jump = 1,temp = 0;
    t = head2.succ;
    q = t->succ;
    while(q){
        if(q->data == t->data){
            jump += temp;
            break;
        }
        temp++;
        q = q->succ;
    }*/
    //int count = 0;
    int result;
    int test = -2;
    while(pos <= length1){
        result = KMP(&head1,&head2,pos,length2);
        if(result != -1 && result!=test){
            if(num==0)
                printf("%d",result);
            else 
                printf(" %d",result);
        }
        test = result;
        num++;
        pos++;
        //t = t->succ;
    }
    printf("\n");
    t = head2.succ;
    num = 0;
    while(t){
        if(num==0)
            printf("%d",t->next->order);
        else 
            printf(" %d",t->next->order);
        t = t->succ;
        num++;
    }
    return 0;
}

int KMP(pnode head1,pnode head2,int pos,int length2){
    pnode p,q;
    p = head1;
    q = head2;
    //pnode head1,head2;
    int i=0;
    while(i<pos){
        p = p->succ;
        i++;
    }
    q = q->succ;
    //int i=pos;
    while(p && q){
        if(q==head2 || p->data==q->data){
            q = q->succ;
            p = p->succ;
            i++;
        }else 
            q = q->next;
    }
    if(!q)
        return i-length2;
    else 
        return -1;
}

void get_nextval(pnode head,int length){
    //int i = 1;
    pnode p,q;
    p = head->succ;
    q =  head;
    p->next = q;
    while(p->succ){
        if(q==head || p->data==q->data){
            p = p->succ;
            q = q->succ;
            if(p->data!=q->data)
                p->next = q;
            else 
                p->next = q->next;
        }
        else 
            q = q->next;
    }
}
