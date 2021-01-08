#include<stdio.h>
#include<string.h>
#define MAXL 234
int main(){
    char s[MAXL];
    int k=0;
    char c;
    while((c=getchar())!='\n' && c!=EOF)
        s[k++] = c;
    s[k] = '\0';
    int i,j;
    i = 0;
    j = k-1;
    char temp;
    while(i<j){
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
        i++;
        j--;
    }
    i = 0;
    while(s[i]!='\0')
        printf("%c",s[i++]);
    return 0;
}
