#include <bits/stdc++.h>
using namespace std;

#define MAXL 100
char c;
int count = 0;

int getnum(void);
void display(int arr[]);
void quickSort(int arr[],int stack[],int& pos);
int PartSort(int* array,int left,int right);
void swap(int &a,int &b);
void inputNum(int arr[]);

int main(){
    int stack[MAXL],arr[MAXL];
    int pos = 0;
    inputNum(arr);
    quickSort(arr,stack,pos);
    display(arr);
    return 0;
}

void display(int arr[]){
    int i = 1;
    while(i<=arr[0]){
        if(i!=1)
            cout<<",";
        cout<<arr[i++];
    }
}

void quickSort(int arr[],int stack[],int& pos){
    stack[pos++] = 1;
    stack[pos++] = arr[0];
    while(pos!=0){
        int right = stack[--pos];
        int left = stack[--pos];
        int base = PartSort(arr,left,right);
        int llen = base - left;
        int rlen = right - base;
        if(llen < rlen){
            if((base - 1) > left){
                stack[pos++] = left;
                stack[pos++] = base - 1;
            }
            if((base + 1) < right){
                stack[pos++] = base + 1;
                stack[pos++] = right;
            }
        }else{
            if((base + 1) < right){
                stack[pos++] = base + 1;
                stack[pos++] = right;
            }
            if((base - 1) > left){
                stack[pos++] = left;
                stack[pos++] = base - 1;
            }
        }
    }
}

int PartSort(int* array,int left,int right){
    int pivotkey = array[left];
    while(left < right){
        while(left<right && array[right]>=pivotkey)
            right--;
        array[left] = array[right];
        while(left<right && array[left]<=pivotkey)
            left++;
        array[right] = array[left];
    }
    array[left] = pivotkey;
    return left;
}

void swap(int &a,int &b){
    a = a + b;
    b = a - b;
    a = a - b;
}

void inputNum(int arr[]){
    int i = 1;
    c = '.';
    while (c!=EOF && c!='\n')
        arr[i++] = getnum();
    arr[0] = i-1;
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
