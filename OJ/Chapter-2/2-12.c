#include<stdio.h>
#define MAXL 42
int main(){
    char ar[MAXL],br[MAXL];
    int i=0,j=0,k=0;
    char temp;
    while((temp=getchar())!=';')
        ar[i++] = temp;
    ar[i] = '\0';
    //putchar(temp);
    while((temp=getchar())!= EOF && temp!='\n')
        br[j++] = temp;
    br[j] = '\0';
    while(ar[k]!='\0' && br[k]!='\0' && ar[k]==br[k]) k++;
    if(ar[k] < br[k])
        printf("1");
    else if(ar[k] > br[k])
        printf("2");
    else
        printf("0");
    return 0;
}
