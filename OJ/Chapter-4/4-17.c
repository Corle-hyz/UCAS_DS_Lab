#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXL 100

int compare(char* first,char* second,int len);
void initialize(char* s,int i);
void displayChar(char* s);
void move(char* a,char* b,int length);


int main(){
    char s[MAXL],t[MAXL],v[MAXL],res[MAXL];
    initialize(s,MAXL);
    initialize(t,MAXL);
    initialize(v,MAXL);
    initialize(res,MAXL);
    int i=0,k=0;
    char c;
    while((c=getchar())!=' ' && c!='\n' && c!=EOF)
        s[k++] = c;
    k = 0;
    while((c=getchar())!=' ' && c!='\n' && c!=EOF)
        t[k++] = c;
    k = 0;
    while((c=getchar())!=' ' && c!='\n' && c!=EOF)
        v[k++] = c;
    k = 0;
    int lent,lenv;
    int pres = 0;
    lent = strlen(t);
    lenv = strlen(v);
    int j=0;
    int sign = 0;
    while(s[j])
        if(!compare(&s[j++],t,lent))
            sign = 1;
    if(sign == 0){
        printf("");
        return 0;
    }
    while(s[i]){
        if(!compare(&s[i],t,lent)){
            move(&res[pres],v,lenv);
            i += lent;
            pres += lenv;
        }
        else
            res[pres++] = s[i++];
    }
    displayChar(res);
    return 0;


}


void initialize(char* s,int i){
    for(int j=0;j<i;j++)
        s[j] = '\0';
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

void move(char* a,char* b,int length){
    int i = 0;
    while(i < length){
        a[i] = b[i];
        i++;
        }
    return;
}
void displayChar(char* s){
    int i=0;
    while(s[i])
        printf("%c",s[i++]);
}
