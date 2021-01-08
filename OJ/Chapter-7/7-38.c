#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 100

typedef struct node{
	char data;
	struct node* left;
	struct node* right;
}Node,*pNode;

void buildTree(pNode n,char op[MAXL][MAXL],int row);
void postOrderOut(pNode n);
int getnum(void);

int main(){
	char c,temp;
	int vexNum,j,k;
    int i = 0;
	Node list[MAXL];
	char op[MAXL][MAXL];
	pNode root;
	vexNum = getnum();
	while(i < vexNum){
		j = 0;
		while((c=getchar()) != '\n'){
			op[i][j++] = c;
		}
		op[i][j] = 0;
		i++;
	}
	for(j=0;j<vexNum;j++){
		if(op[j][1] == ' '){
			temp = op[j][2];
			op[j][2] = op[j][4];
			op[j][4] = temp;
		}
	}
	root = (pNode)malloc(sizeof(Node));
	root->data = op[0][0];
	root->left = NULL;
	root->right = NULL;
	buildTree(root,op,0);
	postOrderOut(root);
	return 0;
}
	
void buildTree(pNode n,char op[MAXL][MAXL],int row){
	pNode lchild;
	pNode rchild;
	int a,b;
	if(op[row][1] == ' '){
		lchild = (pNode)malloc(sizeof(Node));
		a = op[row][2] - '0';
		lchild->data = op[a][0];
		lchild->left = NULL;
		lchild->right = NULL;
		n->left = lchild;
		buildTree(lchild,op,a);
		rchild = (pNode)malloc(sizeof(Node));
		b = op[row][4] - '0';
		rchild->data = op[b][0];
		rchild->left = NULL;
		rchild->right = NULL;
		n->right = rchild;
		buildTree(rchild,op,b);
	}
	return;
}
	
void postOrderOut(pNode n){
	if(n->left)
		postOrderOut(n->left);
	if(n->right)
		postOrderOut(n->right);
	printf("%c",n->data);
	return;
}

int getnum(void){
    char m;
    int num = 0;
    while((m=getchar())!=EOF && m!='\n' && isdigit(m))
        num = num*10 + m - '0';
    return num;
}
