#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXL 100
#define UPPER 123456
#define LOWER 135790
int getnum(void);

int getnum(void){
    char m;
    int num = 0;
    while((m=getchar())!=EOF && m!='\n' && isdigit(m))
        num = num*10 + m - '0';
    return num;
}

int main(){
	int vnum,v0;
	char c;
    vnum = getnum();
    v0 = getnum();
	char list[MAXL][MAXL];
	int matrix[MAXL][MAXL];
    int* const final = (int*)malloc((vnum+1) * sizeof(int));
    int* const arr = (int*)malloc((vnum+1) * sizeof(int));
    int i,j;
    i = 0;
	while((c=getchar()) != EOF){
		list[i][0] = c;
		j = 1;
		while((c=getchar()) != '\n')
			list[i][j++] = c;
		list[i][j] = 0;
		i++;
	}
	int k = i;
    int a,b,l,m;
	for(i=0;i<MAXL;i++)
		for(j=0;j<MAXL;j++)
			matrix[i][j] = UPPER;
	for(j=0;j<k;j++){
		a = list[j][0] - '0';
		b = list[j][2] - '0';
		l = 0;
		for(m=4;list[j][m]!=0;m++)
			l = 10*l + list[j][m] - '0';
		matrix[a-1][b-1] = l;
	}
    int v,min,w;
	for(v=1;v<=vnum;v++){
		final[v] = 0;
		arr[v] = matrix[v0-1][v-1];	
	}
	arr[v0] = 0;
	final[v0] = 1;
	for(i=1;i<vnum;i++){
		min = LOWER;
		for(w=1;w<=vnum;w++){
			if(final[w] == 0)
				if(arr[w] < min){
					v = w;
					min = arr[w];
				}
		}
		final[v] = 1;
		for(w=1;w<=vnum;w++){
			if(final[w]==0 && (min+matrix[v-1][w-1] < arr[w])){
				arr[w] = min + matrix[v-1][w-1];
			}
		}
	}
	for(w=1;w<vnum;w++)
		if(w!=v0)
			printf("%d,",arr[w]);
	printf("%d",arr[w]);
	return 0;
}
