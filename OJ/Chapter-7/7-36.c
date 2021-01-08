#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 100

typedef struct node{
	int data;
	struct node* next;
}Node,*pNode;
int endSign;
int getnum(void);
int getLength(struct node v[],int pos,int visit[]);

int main(){
	char c;
	char s[MAXL];
	int i=0;
    int j,a,vexNum;
	int visit[MAXL];
	int len[MAXL];
	pNode q;
	vexNum = getnum();
    pNode const v = (pNode)malloc(vexNum * sizeof(Node));
	for(i=0;i<vexNum;i++){
		v[i].data = i+1;
		v[i].next = NULL;
	}
	for(endSign=0;;){
			a = getnum();
			q = (pNode)malloc(sizeof(Node));
			q->data = getnum();
			q->next = v[a-1].next;
			v[a-1].next = q;
            if(endSign)
                break;
	}
	for(i=0;i<vexNum;i++){
		for(j=0;j<MAXL;j++)
			visit[j] = 0;
		visit[i+1] = 1;
		len[i] = getLength(v,i+1,visit);
	}
	for(i=0;i<vexNum-1;i++)
		printf("%d,",len[i]);
	printf("%d",len[i]);
	return 0;
}

int getLength(struct node v[],int pos,int visit[]){
	pNode p;
	int a,b,max = 0;
	p = (pNode)malloc(sizeof(Node));
	*p = v[pos-1];
	if(p->next == NULL)
		return 0;
	while(p->next != NULL){
		p = p->next;
		if(!visit[p->data]){
			visit[p->data] = 1;
			a = getLength(v,p->data,visit);
			visit[p->data] = 0;
			if(a > max)
				max = a;
		}
	}
	return max+1;
}

int getnum(void){
    char m;
    int num = 0;
    while((m=getchar())!=EOF && m!='\n' && isdigit(m)){
        num = num*10 + m - '0';
    }
    if(m == '\n' || m == EOF)
        endSign = 1;
    return num;
}
