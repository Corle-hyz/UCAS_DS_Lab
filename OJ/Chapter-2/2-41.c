#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAXL 100
typedef struct a{
    int para;
    int power;
    struct a* next;
}node,*pnode;

void sort(pnode h);
void derv(pnode h);
void print(pnode h);
void change(pnode i,pnode j);
char temp[MAXL];
void stander(char* s);
void movespace(char* s);

int main(){
    char s[MAXL];
    // scanf("%s",s);
    int k=0;
    char input;
    memset(s,0,sizeof(s));
    while((input=getchar())!=EOF && input!='\n')
        s[k++] = input;
    s[k] = '\0';
    // printf("%ld",strlen(s));
    movespace(s);//get rid of the space and ^
    stander(s);//standerlize array s as axb&
    memcpy(s,temp,sizeof(temp));
    int state = 0;//-1:new_num; 0:para;  1:alpha;  2:power;  3:+
    char element;
    int i=0;
    // int para=0,power=0;
    int tempn=0;
    pnode h,t,q;//create the chainlist
    h = (pnode)malloc(sizeof(node));
    t = h;
    int pos = 1;
    while((element=s[i++]) != '\0'){
        if(element=='-')
            pos = -1;
        if(isdigit(element))
            tempn = tempn*10+element-'0';
        if(element=='x'){
            t->para = tempn*pos;
            tempn = 0;
            pos = 1;
        }
        if(element=='&'){
            t->power = tempn*pos;
            tempn = 0;
            q = (pnode)malloc(sizeof(node));
            t->next = q;
            t = q;
            t->power = 0;
            pos = 1;
        }
    }
    t->next = h;
    sort(h);
    derv(h);
    print(h);
    return 0;
}

// void merge(pnode h){
//     ;
// }
void movespace(char* s){
    int movenum=0;
    int i;
    for(i=0;s[i]!='\0';i++){
        if(s[i]==' ')// || s[i]=='^'
            movenum++;
        else
            s[i-movenum] = s[i];
    }
    for(int j=i-movenum;j<MAXL;j++)
        s[j] = '\0';
    // s[i-movenum] = '\0';
}

void stander(char* s){
    int state = 0;
    int i,j;
    for(i=0,j=0;s[i]!='\0';i++,j++){
        // if(state==-1)
        //     state = (isdigit(s[i]) || s[i]=='-')?0:;//para0 NOpara3
        switch(state){
            case 0://done nothing
                if(isdigit(s[i]) || s[i]=='-'){//para
                    temp[j] = s[i];
                    // state = 1;//with para
                    char c;
                    while((c=s[++i])!='x' && c!='+' && c!='-' && c!='\0')
                        temp[++j] = c;
                    temp[++j] = 'x';
                    if(c=='+')
                        i++;
                    if(c=='-'){
                        temp[++j] = c;
                        i++;
                    }
                    state = c=='x'?1:0;
                    i = s[i]=='x'?i:i-1;
                }
                else if(s[i]=='x' || s[i]=='X'){
                    state = 1;//without para
                    temp[j++] = '1';
                    temp[j] = s[i];
                }
                // else if(s[i] == '+' || s[i]=='-')
                //     j--;
                else{
                    state = 0;//power end
                    temp[j++] = '0';
                    temp[j++] = 'x';
                    temp[j++] = '0';
                    temp[j] = '&';
                }
                break;

            case 1://done the para and x
                if(s[i]=='^'){
                    state = 0;//with power
                    if(s[i+1]=='-')
                        s[j++] = s[++i];
                    char c;
                    while((c=s[++i])!='x' && c!='+' && c!='-' && c!='\0')
                        temp[j++] = c;
                    if(c=='+')
                        i++;
                    i--;////
                    temp[j] = '&';
                }
                // else if(s[i] == '+' || s[i]=='-')
                //     j--;
                else{//without power
                    if(s[i-1]=='x')
                        temp[j++] = '1';
                    else
                        temp[j++] = '0';
                    if(s[i]=='+')
                        i++;
                    // if(s[i]=='-')
                    //     temp[j++] = s[i++];
                    i--;
                    temp[j] = '&';
                    state = 0;//pow end
                }
                break;
            default: break;
        }
    }
}


void sort(pnode h){
    pnode i,j;
    for(i=h;i->next!=h;i=i->next)
        for(j=i->next;j->next!=h;j=j->next){
            if(i->power < j->power)
                change(i,j);
            if(i->power == j->power){
                (i->para) += (j->para);
                j->para = 0;
                j->power = 0;
            }
        }
}

void derv(pnode h){
    pnode temp;
    for(temp=h;temp->next!=h;temp=temp->next){
        (temp->para) = (temp->para) * (temp->power);
        temp->power -= 1;
    }
    // free(temp);
}

void print(pnode h){
    pnode empty;
    int judge=0;
    for(empty=h;empty->next!=h;empty=empty->next)
        if(empty->para!=0)
            judge = 1;
    if(judge==0){
        printf("0");
        return;
    }
    pnode temp;
    for(temp=h;temp->next!=h;temp=temp->next){
        if(temp->para == 0)
            continue;
        if(temp->power!=1 && temp->power!=0){
            if(temp->para > 1)
                printf("%dx^%d",temp->para,temp->power);
            else if(temp->para < 0)
                printf("- %dx^%d",-temp->para,temp->power);
            else
                printf("x^%d",temp->power);
        }
        else if(temp->power == 1){
            if(temp->para > 1)
                printf("%dx",temp->para);
            else if(temp->para < 0)
                printf("- %dx",-temp->para);
            else
                printf("x");
        }
        else if(temp->power == 0){
            if(temp->para > 0)
                printf("%d",temp->para);
            else
                printf("- %d",-temp->para);
        }
        if(temp->next->para>0 && temp->next->next != h)
            printf(" + ");
        if(temp->next->para < 0)
            printf(" ");
    }
}

void change(pnode i,pnode j){
    pnode temp;
    temp = (pnode)malloc(sizeof(node));
    temp->para = i->para;
    temp->power = i->power;
    i->para = j->para;
    i->power = j->power;
    j->para = temp->para;
    j->power = temp->power;
    free(temp);
}

