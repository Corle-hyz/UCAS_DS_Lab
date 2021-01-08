#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define AtomType char
#define MAXSIZE 1024
#define ElemTag int
#define OK 1
#define ERROR 0

typedef struct GLNode{
    ElemTag tag;
    union{
        AtomType atom;
        struct GLNode *hp;
    }atom_hp;
    struct GLNode *tp;
}GLNode,*GList;


//功能：分离出广义表中表头部分
//返回：分离后剩下的字符串，不包括逗号
void Disastr(char *s,char *hstr){
    int i,j,k,r;
    char rstr[MAXSIZE];
    i=j=k=0;
    while(s[i] && (s[i] != ',' || k)){
        if(s[i]=='('){k++;}//k 作为括号计数器       
        else if(s[i]==')'){
            k--;
        }
        if(s[i]!=','||s[i]==','&&k){
            hstr[j]=s[i];
            i++;
            j++;
        }
    }
    hstr[j] = '\0';
    if (s[i] == ',') {i++;}
    r=0;
    while(s[i]){// 处理剩余的表尾部分
        rstr[r] = s[i];
        r++;
        i++;
    }
    rstr[r] = '\0';
    strcpy(s,rstr);
}

//功能：根据输入的字符串，建立广义表
//返回：成功则返回建立的广义表的表头，否则，返回NULL
GLNode* GLCreate(char *s){
    GLNode *p,*q,*r,*head;
    char substr[MAXSIZE],hstr[MAXSIZE];//rstr[MAXSIZE];
    int len;
    len = strlen(s);
    if ( !strcmp(s,"()") || !len){head = NULL;}// (1) 空表情况
    else if(len==1){// (2) 原子情况
        head=(GLNode *)malloc(sizeof(GLNode));// 建立一个新结点
        if(!head)
            return NULL;
        head->tag=0;//构造原子结点
        head->atom_hp.atom = *s;
        head->tp = NULL;
    }
    else{//(3) 子表情况
        head = (GLNode *)malloc(sizeof(GLNode));
        if (!head) return NULL;
        head->tag = 1;
        p = head;
        s++;
        strncpy(substr,s,len-2);//剥去外层的()
        substr[len-2] = '\0';
        do{
            Disastr(substr,hstr);//分离出表头
            r = GLCreate(hstr);
            p->atom_hp.hp = r;//尾插法建表
            q=p;
            len = strlen(substr);
            if (len > 0){
                p = (GLNode*)malloc(sizeof(GLNode));
                if (!p) return NULL;
                p->tag = 1;
                q->tp=p;
            }
        } while (len > 0);
        q->tp=NULL;
    }
    return head;
}

void DisplayList(GList head){
    GLNode *p,*q;
    if(!head) return;
    if (head->tag==0){
        printf("%c",head->atom_hp.atom);
        return;
    }
    printf("(");
    if (head){
        do{
            p = head->atom_hp.hp;
            q = head->tp;
            while (q && p && p->tag == 0){//同一层的原子结点
                printf("%c,",p->atom_hp.atom);
                p = q->atom_hp.hp;
                q = q->tp;
            }
            if (p && !p->tag){//最后一个原子结点
                printf("%c",p->atom_hp.atom);
                break;
            }
            else{// 子表情况
                if (!p) printf("()");
                else DisplayList(p);
                if(q) printf(",");
                head = q;
            }
        } while (head);
        printf(")");
    }
}

//功能：取出广义表的表头部分
//返回：成功则返回广义表的表头，否则，返回空或退出
GList GetHead(GList L){
    if(!L)
        return (NULL);// 空表无表头
    if(L->tag == 0)
        exit(0);// 原子结点不是表
    else return(L->atom_hp.hp);
}

//功能：取出广义表的表尾部分
//返回：成功返回广义表的表尾部分，否则，返回空或者退出
GList GetTail(GList L){
    if (!L)
        return(NULL);
    if (L->tag == 0) 
        exit(0);
    else return(L->tp);
}

//功能:求出广义表的长度
//返回值:广义表的长度
int Length(GList L){
    int k=0;
    GLNode *s;
    if (!L) return 0;//空表的长度为零
    if (L->tag == 0)
        exit(0);//原子不是表
    s=L;
    while(s){//统计表的最上层的长度
        k++;
        s=s->tp;
    }
    return k;
}


//功能：求得广义表的深度
//输入：需求深度的广义表的指针
int Depth(GList L){
    int d,max;
    GLNode *s;
    if(!L)return (1);//空表的深度为 1
    if(L->tag==0)return 0;//原子的深度为 0
    s=L;
    max=0;
    while(s){// 递归求每个子表深度的最大值
        d=Depth(s->atom_hp.hp);
        if(d>max)max=d;
        s=s->tp;
    }
    return(max+1);// 表的深度为子表深度加一
}


//功能：统计原子结点的个数
//输入：需统计的广义表指针
int CountAtom(GList L){
    int n1,n2;
    if (!L) return 0;// 空表无原子结点
    if (L->tag==0) return 1;// 原子结点
    n1 = CountAtom(L->atom_hp.hp);
    n2 = CountAtom(L->tp);
    return (n1+n2);
}

//功能：完成广义表的复制,将res复制到dest中
//返回：成功返回1，否则，返回0
bool CopyList(GList *dest,GList res)
{
    if (!res){
        *dest = NULL;
        return (OK);
    }
    *dest = (GLNode *)malloc(sizeof(GLNode));
    if (!*dest) return (ERROR);
    (*dest)->tag = res->tag;
    if (res->tag==0)
        (*dest)->atom_hp.atom = res->atom_hp.atom;
    else{
        CopyList(&(*dest)->atom_hp.hp,res->atom_hp.hp);
        CopyList(&(*dest)->tp,res->tp);
    }
    return (OK);
}

//功能：合并广义表，如果p为空，则申请空间，将q复制到p中
//例如：((a,b),c) 和(a,b)合并之后为：((a,b),c,a,b)
//算法描述：先找到第一个广义表的最后一个结点，将其链到第二个广义表的首元素即可
void Merge(GList *p,GLNode *q){
    GLNode *r;
    if (!q) return;//  如果复制的是个空表，返回
    if (!p){// p为空，申请空间
        *p = (GLNode*)malloc(sizeof(GLNode));
        if (!(*p)) return ;
        (*p)->tag = 1;
    }
    else{
        if ((*p)->tag){
            r=*p;
            while(r->tp) r=r->tp;// 找到最后一个子表的表尾指针
            if (q->tag) r->tp = q;// 修改表尾指针
        }
    }
}

//功能：类似二叉树的先序遍历遍历广义表L
//eg：例如(a,(b,(c),d))结果为：a,b,c,d
//算法描述：
//L若为原子结点，显示该数据，递归调用遍历后续元素，也即:write(L->atom_hp.atom);PreOrder(L->tp);
//L是子表结点，递归调用遍历该子表，遍历后续元素，也即:PreOrder(L->atom_hp.tp);PreOrder(L->tp);
void PreOrder(GList L)
{
    if (L){
        if (L->tag==0) printf("%c ",L->atom_hp.atom);// 打印原子结点
        else PreOrder(L->atom_hp.hp);// 往下遍历，类似二叉树中的左子树
        if (L->tp) PreOrder(L->tp);// 往右遍历，类似二叉树中的右子树
    }
}

// 判断两个广义表是否相等，相等，返回1，否则，返回0
// 相等的定义：两个广义表具有相同的存储结构，对应的原子结点的数据域也相等
//算法描述：
// 形式：条件
//Equal(p,q) = Equal(p->tp,q->tp) ; p->tag = 0 && q->tag = 0 && p->atom_hp.atom = q->atom_hp.atom
//Equal(p,q) = Equal(p->atom_hp.hp,q->atom_hp.hp) && Equal(p->tp,q->tp) ; p->tag = 1 && q->tag = 1
//Equal(p,q) = false     ; p->tag = 0 && q->tag = 0 p->atom_hp.atom != q->atom_hp.atom 或者 p->tag *p->tag + q->tag*q->tag =1
//Equal(p,q) = false      ; p q 其中之一为NULL
bool Equal(GList p,GList q)
{
    bool flags = true;
    if (!p && q) flags = false;
    if (p && !q) flags = false;
    if (p && q){
        if (p->tag == 0 && q->tag == 0 ){
            if (p->atom_hp.atom != q->atom_hp.atom)
                flags = false;
        }
        else if (p->tag == 1 && q->tag == 1){
            flags = Equal(p->atom_hp.hp,q->atom_hp.hp);
        }
        else flags = false;
        if (flags)
            flags = Equal(p->tp,q->tp);
    }
    return flags;
}

int main(){
    char s[MAXSIZE],a[MAXSIZE];
    GList head;
    GList L;
    printf("please input a string:");
    scanf("%s",s);
    head = GLCreate(s);
    DisplayList(head);
    printf("\n");
    printf("The Head is:");
    DisplayList(GetHead(head));
    printf("\n");
    printf("The Tail is: ");
    DisplayList(GetTail(head));
    printf("\n");
    printf("The Length is %d\n",Length(head));
    printf("The Depth is %d\n",Depth(head));
    printf("The Atom number is %d\n",CountAtom(head));
    printf("Copy the List:\n");
    CopyList(&L,head);
    DisplayList(L);
    printf("\n");
    printf("Merge the List\n");
    Merge(&L,head);
    DisplayList(L);
    printf("\n");
    printf("PreOrder:");
    PreOrder(head);
    printf("\n");
    printf("input a string:");
    scanf("%s",a);
    L = GLCreate(a);
    DisplayList(L);
    printf(" Eqaul ");
    DisplayList(head);
    printf(":");
    if (Equal(L,head)) printf("yes!\n");
    else printf("no!\n");
    return 0;
}
