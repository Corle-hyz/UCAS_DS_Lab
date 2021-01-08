#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdarg.h>

typedef struct olnode{
	int i,j;
	int e;
	struct olnode *right,*down;
}olnode, *olink;
olnode *p,*pre;

typedef struct{
	olink *rhead,*chead;
	int mu,nu;
}crosslist;
crosslist a,b;

int m,n;
struct data{
	int i,j,e;
}adata[1000],bdata[1000];
int tua=0,tub=0;

int d1[1000],d2[1000];
int d[1000][1000];

crosslist* addrA = &a;
crosslist* addrB = &b;

void createsmatrixa(crosslist* a);
void createsmatrixb(crosslist* b);
void add(void);

int main(){
	char c;
	scanf("%d%c%d%c",&m,&c,&n,&c);
	int len=0;
	while((c=getchar())!='+'){
		if(c=='['||c==']')
			continue;
		else if(c==';'||c==',')
			len++;
		else if(c=='-'){
			scanf("%d",&d1[len]);
			d1[len]=-1*d1[len];
		}else
			d1[len]=d1[len]*10+c-'0';
	}
	for(int i=0;i<=len;i++){					
		if(d1[i]!=0){
			++tua;
			adata[tua].e=d1[i];
			adata[tua].i=i/n;
			adata[tua].j=i-(i/n)*n;
		}
	}
	len=0;
	while((c=getchar())!='\n'){
		if(c=='['||c==']')
			continue;
		else if(c==';'||c==',')
			len++;
		else if(c=='-'){
			scanf("%d",&d2[len]);
			d2[len]=-1*d2[len];
		} else
			d2[len]=d2[len]*10+c-'0';
	}
	for(int i=0;i<=len;i++){					
		if(d2[i]!=0){
			++tub;
			bdata[tub].e=d2[i];
			bdata[tub].i=i/n;
			bdata[tub].j=i-(i/n)*n;
		}
	}
	createsmatrixa(addrA);
	createsmatrixb(addrB);
	add();
	for(int i=0;i<a.mu;i++)
		for(p=a.rhead[i];p!=NULL;p=p->right)
			d[p->i][p->j]=p->e;
	printf("[");
	for(int i=0;i<m;i++){
		if(i!=0)
			printf(";");
		printf("[");
		for(int j=0;j<n;j++){
			if(j!=0)
				printf(",");
			printf("%d",d[i][j]);
		}
		printf("]");
	}
	printf("]");
	return 0;
}

void createsmatrixa(crosslist* a){
	a->mu=m; a->nu=n;
	a->rhead=(olink *)malloc((m+1)*sizeof(olink));
	a->chead=(olink *)malloc((n+1)*sizeof(olink));
	for(int t=0;t<m;t++)
		a->rhead[t]=NULL;
	for(int t=0;t<n;t++)
		a->chead[t]=NULL;
	for(int t=tua;t>0;t--){
		p=(olnode *)malloc(sizeof(olnode));
		int i=adata[t].i,j=adata[t].j;
		p->i=i;
		p->j=j;
		p->e=adata[t].e;
		p->right=a->rhead[i];
		a->rhead[i]=p;
		p->down=a->chead[j];
		a->chead[j]=p;
	}
}
void createsmatrixb(crosslist* b){
	b->mu=m;
	b->nu=n;
	b->rhead=(olink *)malloc((m+1)*sizeof(olink));
	b->chead=(olink *)malloc((n+1)*sizeof(olink));
	for(int t=0;t<m;t++)
		b->rhead[t]=NULL;
	for(int t=0;t<n;t++)
		b->chead[t]=NULL;
	for(int t=tub;t>0;t--){
		p=(olnode *)malloc(sizeof(olnode));
		int i=bdata[t].i,j=bdata[t].j;
		p->i=i;
		p->j=j;
		p->e=bdata[t].e;
		p->right=b->rhead[i];
		b->rhead[i]=p;
		p->down=b->chead[j];
		b->chead[j]=p;
	}
}

void add(){
	olnode *pa,*pb,*hl[1000];
	for(int j=0;j<n;j++) hl[j]=a.chead[j];
	for(int i=0;i<m;i++){
		pa=a.rhead[i]; pb=b.rhead[i]; pre=NULL;
		while(pb!=NULL){
			if(pa==NULL||pa->j>pb->j){
				p=(olnode *)malloc(sizeof(olnode));
				p->i=pb->i; p->j=pb->j; p->e=pb->e;
				if(pre==NULL)
					a.rhead[p->i]=p;
				else
					pre->right=p;
				p->right=pa;
					pre=p;
				if(a.chead[p->j]==NULL||a.chead[p->j]->i>p->i){
					p->down=a.chead[p->j];
					a.chead[p->j]=p;
				}
				else{
					p->down=hl[p->j]->down;
					hl[p->j]->down=p;
				}
				hl[p->j]=p;
				pb=pb->right;
			}else if(pa!=NULL&&pa->j<pb->j){
				pre=pa;
				pa=pa->right;
			}else if(pa->j==pb->j){
				pa->e=pa->e+pb->e;
				pre=pa;
				pa=pa->right;
				pb=pb->right;
			}
		}
	}
}
