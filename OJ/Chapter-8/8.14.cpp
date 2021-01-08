#include <bits/stdc++.h>
using namespace std;
#define MAX 20
typedef struct Buddy{
	int size;
	int pos;
	struct Buddy *llink;
	struct Buddy *rlink;
}Buddy,*pBuddy;
void display(pBuddy h[]);

int getline(int s[]){
        int i=0;
        int lim = MAX;
        char c;
        while(--lim>0&&(c=getchar())!=EOF&&c!='\n')
		if(c!=' '){	
			s[i++]=c-'0';
			if((c=getchar())>='0' && c<='9')		
		        	s[i-1]=s[i-1]*10+c-'0';
			else if(c=='\n' || c==EOF) break;
		}	
        s[i]='\0';
        return i;
}

int power(int n){
	int k=0,op=1;
	for(k=0;k<n;k++)
		op*=2;
	return op;
}

int main(){
	int i=0,j,bpos=0,sign=0,t;
	int mi0,mi1,re;
	int s[MAX];
	pBuddy h[MAX];
	for(i=0;i<MAX;i++)
		h[i]=NULL;
	pBuddy p,q;
	int k=0;
	while(getline(s)>1){	
		j=s[0];
		p=(pBuddy)malloc(sizeof(Buddy));
		p->size=j;
		p->pos=s[1];
		p->llink=NULL;
		p->rlink=NULL;
		h[j]=p;
		for(i=2;s[i]!='\0' && s[i]!='\n';i++){	
			q=(pBuddy)malloc(sizeof(Buddy));
			q->size=j;
			q->pos=s[i];
			q->rlink=NULL;
			q->llink=p;
			p->rlink=q;
			p=q;
		}
		for(k=0;k<MAX;k++)
			s[k]='\0';
	}
	while(getline(s)>1){
		j=s[0];
		k=s[1];
		sign=0;
		do{
			mi0=power(j);
			mi1=power(j+1);
			if(k%mi1==0)
				re=mi0+k;
			else 
				re=k-mi0;
			bpos=re;
			p=h[j];
			while(p!=NULL && p->pos!=bpos)
				p=p->rlink;
			if(p==NULL){	
				q=(Buddy*)malloc(sizeof(Buddy));
				q->size=j; q->pos=k;
				if(h[j]!=NULL){
					for(p=h[j];p->rlink!=NULL && p->rlink->pos<k;p=p->rlink)
						;
					if(p->pos<k){
						q->rlink=p->rlink;
						if(p->rlink!=NULL)
							p->rlink->llink=q;
						q->llink=p;
						p->rlink=q; 
						sign=1;
					}
					else if(p->rlink==NULL && p->pos>k){
						q->rlink=p;
						q->llink=NULL;
						p->llink=q;
						h[j]=q;
						sign=1;
					}
				}
				else{
					q->llink=NULL;
					q->rlink=NULL;
					h[j]=q;
					sign=1;
				}
			}
			else{
				j=j+1; 
				if(p->pos<k)			
					k=p->pos;
				if(p->rlink!=NULL)
					p->rlink->llink=p->llink;
				if(p->llink!=NULL)			
					p->llink->rlink=p->rlink;
				else
					h[j-1]=p->rlink;
				free(p);
			}
		}while(sign==0);
		for(t=0;t<MAX;t++)
			s[t]='\0';
	}
	display(h);
	return 0;		
}

void display(pBuddy h[]){
	pBuddy p;
	for(int i=0;i<MAX;i++){
		if(h[i]!=NULL)
		{	printf("%d ",i);
			for(p=h[i];p->rlink!=NULL;p=p->rlink)
				printf("%d ",p->pos);
			printf("%d\n",p->pos);		
		}
	}
}

