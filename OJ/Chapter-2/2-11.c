#include<stdio.h>
#define MAXL 50
int main(){
    int arr[MAXL];
    int i=0;
    while(scanf("%d",&arr[i]) != EOF) i++;
    int temp = arr[i-1];
    int j=i-2;
    while(arr[j] > temp){
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = temp;
    for(int k=0;k<i-1;k++)
        printf("%d ",arr[k]);
    printf("%d",arr[i-1]);
    return 0;
}
