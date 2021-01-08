#include <bits/stdc++.h>
using namespace std;
#define MAXL 50
int tr1[MAXL];
char c = '.';
void display(int arr[],int num);
void merge(int sr[],int tr[],int i,int m,int n);
int getnum(void);
void MergeSort(int sr[],int tr1[],int s,int t);


void merge(int sr[],int tr[],int i,int m,int n){
    int j,k;
    for(j=m+1,k=i;i<=m && j<=n;k++){
        if(sr[i]<=sr[j])
            tr[k] = sr[i++];
        else 
            tr[k] = sr[j++];
    }
    if(i<=m){
        for(int p=k,q=i;q<=m;q++,p++)
            tr[p] = sr[q];
    }
    if(j<=n){
        for(int p=k,q=j;q<=n;q++,p++)
            tr[p] = sr[q];
    }
    return;
}

void MergeSort(int sr[],int tr1[],int s,int t){
    int tr2[MAXL];
    if(s==t)
        tr1[s] = sr[s];
    else{
        int m = (s+t)/2;
        MergeSort(sr,tr2,s,m);
        MergeSort(sr,tr2,m+1,t);
        merge(tr2,tr1,s,m,t);
    }
}

int main(){
    int i=1;
    int arr[MAXL];
    memset(arr,0,MAXL*sizeof(int));
    while(c!='\n' && c!=EOF)
        arr[i++] = getnum();
    arr[0] = i - 1;
    MergeSort(arr,tr1,1,arr[0]);
    display(tr1,arr[0]);
    return 0;
}

void display(int arr[],int num){
    int i;
    i = 0;
    while(i<num){
        if(i)
            cout<<" ";
        cout<<arr[i+1];
        i++;
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
