#include<stdio.h>
#include<string.h>
#define MAXL 100
int compare(char* first,char* second,int MAXL);
void initialize(char* s,int i);
int main(){
    char first[MAXL],second[MAXL];
    char c;
    int k=0;
    initialize(first,MAXL);
    initialize(second,MAXL);
    while((c=getchar())!=' ' && c!='\n' && c!=EOF)
        first[k++] = c;
    k = 0;
    while((c=getchar())!=' ' && c!='\n' && c!=EOF)
        second[k++] = c;
    int i = -1;
    while((++i)<MAXL){
        if(first[i]>second[i]){
            printf("1");
            return 0;
        }
        else if(first[i]<second[i]){
            printf("-1");
            return 0;
        }
    }
    printf("0");
    return 0;
}

void initialize(char* s,int i){
    for(int j=0;j<i;j++)
        s[j] = '\0';
}

int compare(char* first,char* second,int MAXL){
    int i = -1;
    while((++i)<MAXL){
        if(first[i]>second[i]){
            printf("1");
            return 0;
        }
        else if(first[i]<second[i]){
            printf("-1");
            return 0;
        }
    }
    return 0;
}

/*void displayChar(char* s){
    int i=0;
    while(s[i])
        printf("%c",s[i++]);
}*/
