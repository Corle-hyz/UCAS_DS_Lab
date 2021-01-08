#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 42
int space[MAXL];

int main(){
    memset(space,1,MAXL*sizeof(int));
    int low,high,size,temp;
    scanf("%d %d %d",&low,&high,&size);
    int num = (high-low)/size;
    for(int i=0;i<num;i++)
        scanf("%d",&space[i]);
    //space[num] = -1;
    int j=0;
    int count = 0;
    int pos = -1;
    int out = 0;
    while(j<MAXL){
        if(space[j]==0){
            if(count==0)
                pos = j;
            count += size;
        }else if(count!=0){
            printf("0 %d %d\n",2*pos+low,count);
            count = 0;
            out = 1;
        }
        j++;
    }
    if(!out)
        printf("0 0 0");
    return 0;
}
