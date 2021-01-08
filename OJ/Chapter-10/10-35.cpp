#include <bits/stdc++.h>
using namespace std;
char c = '.';
#define MAXL 100
int getnum(void);
void swap(int &a,int &b);
void heapSort(int arr[]);
void display(int arr[]);


int main(){
    int i=1;
    int arr[MAXL];
    memset(arr,9999,MAXL*sizeof(int));
    while(c!='\n' && c!=EOF)
        arr[i++] = getnum();
    arr[0] = i - 1;
    for(int k=1;k<arr[0]/2;k++){
        swap(arr[2*k],arr[2*k+1]);
        heapSort(arr);
    }
    display(arr);
    return 0;
}

void heapSort(int arr[]){
    for(int j=arr[0]/2;j>0;j--){
        if(arr[j] > arr[2*j]){
            if(arr[2*j] < arr[2*j+1])
                swap(arr[j],arr[2*j]);
            else
                swap(arr[j],arr[2*j+1]);
        }else if(arr[j] > arr[2*j+1]){
            if(arr[2*j] > arr[2*j+1])
                swap(arr[j],arr[2*j+1]);
            else
                swap(arr[j],arr[2*j]);
        }
    }
}


void display(int arr[]){
    for(int i=1;i<=arr[0];i++)
        for(int j=i;j<=arr[0];j++)
            if(arr[i] > arr[j])
                swap(arr[i],arr[j]);
    int i,j,k;
    i = 0;
    j = k = 1;
    while(i<arr[0]){
        if(i)
            cout<<",";
        cout<<arr[i+1];
        i++;
    }

}

void swap(int &a,int &b){
    a = a + b;
    b = a - b;
    a = a - b;
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
