#include<stdio.h>
#include<string.h>
#define MAXL 100
int charInString(char c,char* s);
void displayChar(char* s);
void displayInt(int i,int* s);
int main(){
    char s[MAXL],t[MAXL],r[MAXL];
    int pos[MAXL];
    for(int p=0;p<MAXL;p++)
        s[p] = t[p] = r[p] = '\0';
    memset(pos,0,sizeof(pos));
    char c;
    int k = 0;
    while((c=getchar())!=' ' && c!='\n' && c!=EOF)
        s[k++] = c;
    k = 0;
    while((c=getchar())!=' ' && c!='\n' && c!=EOF)
        t[k++] = c;
    int i=0,m=0,n=0;
    while(s[i]){
        if(charInString(s[i],t) || charInString(s[i],r)){
            i++;
            continue;
        }
        pos[n++] = i;
        r[m++] = s[i++];
    }
    if(r[0]=='\0'){
        printf("-1");
        return 0;
    }
    displayChar(r);
    printf(" ");
    displayInt(n,pos);
    return 0;
}

int charInString(char c,char* s){
    int j = 0;
    while(s[j])
        if(s[j++]==c)
            return 1;
    return 0;
}

void displayChar(char* s){
    int i=0;
    while(s[i])
        printf("%c",s[i++]);
}

void displayInt(int i,int* s){
    for(int k=0;k<i;k++)
        printf("%d",s[k]);
}
