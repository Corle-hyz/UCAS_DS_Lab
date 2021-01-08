#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXL 100

int compare(char* first,char* second,int len);
void initialize(char* s,int i);
void displayChar(char* s);

int main(){
    char string[MAXL],answer[MAXL];
    initialize(string,MAXL);
    initialize(answer,MAXL);
    char c;
    int len = 0;
    while((c=getchar())!='\n' && c!=EOF)
        string[len++] = c;
    for(int i=len-1;i>0;i--){
        for(int j=0;j<=len-i;j++)
            for(int k=0;k<=len-i;k++)
                if(k>=j+i && !compare(&string[j],&string[k],i)){
                    memcpy(answer,&string[j],i);
                    printf("%s %d",answer,j);
                    return 0;
                }
    }
    printf("-1");
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

void displayChar(char* s){
    int i=0;
    while(s[i])
        printf("%c",s[i++]);
}

