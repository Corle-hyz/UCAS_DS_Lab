#include <bits/stdc++.h>
using namespace std;

 typedef struct space{
     int tag;
     int pos;
     int size;
     struct space* next;
 }Space,*pSpace;

 int main(){
    pSpace head,temp,p;
    head = (pSpace)malloc(sizeof(Space));
    temp = head;
    p = head;
    int tag,pos,size,state;
    while(1){
        if(scanf("%d %d %d",&tag,&pos,&size)==EOF)
            break;
        switch(tag){
            case 0:
                if(!temp)
                    temp = (pSpace)malloc(sizeof(Space));
                temp->tag = 0;
                temp->pos = pos;
                temp->size = size;
                if(p!=temp)
                    p->next = temp;
                p = temp;
                temp = temp->next;
                break;
            case 1:
                p = head;
                state = 0;
                while(p){
                    if(p->pos==pos+size){
                        p->pos = pos;
                        p->size += size;
                        state = 1;
                        break;
                    }else if(p->pos+p->size==pos){
                        p->size += size;
                        state = 1;
                        break;
                    }
                    p = p->next;
                }
                if(!state){
                    p = head;
                    while(p){
                        if(p->pos<pos && (!p->next || p->next->pos>pos)){
                            pSpace q;
                            q = (pSpace)malloc(sizeof(Space));
                            q->pos = pos;
                            q->size = size;
                            q->tag = 0;
                            q->next = p->next;
                            p->next = q;
                            break;
                        }else if(p==head && p->pos>pos){
                            pSpace r;
                            r = head;
                            head = (pSpace)malloc(sizeof(Space));
                            head->pos = pos;
                            head->size = size;
                            head->tag = 0;
                            head->next = r;
                            break;
                        }
                        p = p->next;
                    }
                }
                break;
            default:
                break;
        }
    }
    pSpace t;
    t = head;
    while(t && t->next){
        if(t->pos+t->size == t->next->pos){
            t->size += t->next->size;
            temp = t->next;
            t->next = t->next->next;
            free(temp);
        }else 
            t = t->next;
    }
    for(t=head;t;t=t->next)
        printf("0 %d %d\n",t->pos,t->size);
    return 0;
 }
