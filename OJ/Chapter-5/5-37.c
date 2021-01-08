#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define AtomType char
#define MAXSIZE 1024
#define ElemTag int
#define OK 1
#define ERROR 0

int compare(char* first,char* second,int len);

typedef struct GLNode{
    ElemTag tag;
    union{
        AtomType atom;
        struct GLNode *hp;
    }atom_hp;
    struct GLNode *tp;
}GLNode,*GList;

void Disastr(char *s,char *hstr){
    int i,j,k,r;
    char rstr[MAXSIZE];
    i=j=k=0;
    while(s[i] && (s[i] != ',' || k)){
        if(s[i]=='('){k++;}
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
    while(s[i]){
        rstr[r] = s[i];
        r++;
        i++;
    }
    rstr[r] = '\0';
    strcpy(s,rstr);
}
GLNode* GLCreate(char *s){
    GLNode *p,*q,*r,*head;
    char substr[MAXSIZE],hstr[MAXSIZE];
    int len;
    len = strlen(s);
    if ( !strcmp(s,"()") || !len){head = NULL;}
    else if(len==1){
        head=(GLNode *)malloc(sizeof(GLNode));
        if(!head)
            return NULL;
        head->tag=0;
        head->atom_hp.atom = *s;
        head->tp = NULL;
    }
    else{
        head = (GLNode *)malloc(sizeof(GLNode));
        if (!head) return NULL;
        head->tag = 1;
        p = head;
        s++;
        strncpy(substr,s,len-2);
        substr[len-2] = '\0';
        do{
            Disastr(substr,hstr);
            r = GLCreate(hstr);
            p->atom_hp.hp = r;
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
            while (q && p && p->tag == 0){
                printf("%c,",p->atom_hp.atom);
                p = q->atom_hp.hp;
                q = q->tp;
            }
            if (p && !p->tag){
                printf("%c",p->atom_hp.atom);
                break;
            }
            else{
                if (!p) printf("()");
                else DisplayList(p);
                if(q) printf(",");
                head = q;
            }
        } while (head);
        printf(")");
    }
}

GList GetHead(GList L){
    if(!L)
        return (NULL);
    if(L->tag == 0)
        exit(0);
    else return(L->atom_hp.hp);
}

GList GetTail(GList L){
    if (!L)
        return(NULL);
    if (L->tag == 0) 
        exit(0);
    else return(L->tp);
}

int main(){
    char c,cc;
    char pattern[MAXSIZE];
    char s[MAXSIZE],a[MAXSIZE];
    for(int k=0;k<MAXSIZE;k++)
        s[k] = a[k] = pattern[k] = '\0';
    GList head;
    GList L;
    int m=0;
    while((c=getchar())!=';')
        pattern[m++] = c;
    scanf("%s",s);
    int i=0;
    char* position;
    int length = strlen(pattern);
    int shiftNum = 0;
    while(s[i]!='\0'){
        shiftNum = 0;
        if(compare(&s[i],pattern,length)==0){
            if(s[i+length]==',')
                shiftNum = 2;
            else 
                shiftNum = 1;
        
            int j=i;
            if(shiftNum==1 && s[i-1]==','){
                j--;
                shiftNum++;
            }
            for(;s[j] != '\0';j++)
                s[j] = s[j+length+shiftNum-1];
            i--;
        }
        i++;
    }
    printf("%s",s);
    // head = GLCreate(s);
    // DisplayList(head);
    return 0;
}

int compare(char* first,char* second,int len){
    int i = -1;
    while((++i)<len){
        if(first[i]>second[i]){
            //printf("1");
            return 1;
        }
        else if(first[i]<second[i]){
            //printf("-1");
            return -1;
        }
    }
    return 0;
}
