#include <bits/stdc++.h>
using namespace std;
char c;
#define MAXL 100
int getnum(void);
int main(){
    int num;
    int arr[4];
    memset(arr,0,4*sizeof(int));
    c = '.';
    while(c!='\n' && c!=EOF){
        num = getnum();
        arr[num] += 1;
    }
    int count = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<arr[i];j++){
            if(count)
                cout<<",";
            cout<<i;
            count++;
        }
    }
    return 0;;
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
