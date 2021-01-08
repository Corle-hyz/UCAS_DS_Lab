#include <bits/stdc++.h>
using namespace std;
#define MAXL 50
char c = '.';

void display(int arr[],int c[]);
void getFrequence(int arr[],int c[]);
int getnum(void);


int main(){
    int i=1;
    int arr[MAXL],brr[MAXL];
    memset(arr,0,MAXL*sizeof(int));
    while(c!='\n' && c!=EOF && i<MAXL)
        arr[i++] = getnum();
    arr[0] = i - 1;
    getFrequence(arr,brr);
    display(arr,brr);
    return 0;
}

void getFrequence(int arr[],int brr[]){
    for(int i=1;i<=arr[0];i++){
        int count = 0;
        for(int j=1;j<=arr[0];j++)
            if(arr[j]<arr[i])
                count++;
        brr[i] = count;
    }
}

void display(int arr[],int brr[]){
    int count = 0;
    while(count<arr[0]){
        int i=1;
        while(brr[i]!=count && i<=arr[0])
            i++;
        if(count)
            cout<<" ";
        cout<<arr[i];
        count++;
    }
}


int getnum(void){
    extern char c;
    char m;
    int num = 0;
    int sign = 1;
    while((c=getchar())!=EOF && c!='\n' && isdigit(c)){
        if(c=='-')
            sign = -1;
        num = num*10 + c - '0';
    }
    if(c=='n'){
        m = getchar();
        m = getchar();
        m = getchar();
        c = getchar();
        return -1;
    }
    return num*sign;
}
