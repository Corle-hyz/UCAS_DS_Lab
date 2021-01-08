#include<stdio.h>
#define MAX 100

int main()
{
	int k,m;
	while(scanf("%d%d",&k,&m) != EOF)
	{
		int arr[MAX];
		for(int i=0;i<MAX;i++)
			arr[i] = 0;
		arr[k-1] = 1;
		if(m<k)
		{
			printf("%d",arr[m]);
			continue;
		}
		for(int i=k;i<=m;i++)
			for(int j=1;j<=k;j++)
				arr[i]+=arr[i-j];
		printf("%d",arr[m]);
		continue;
	}
	return 0;
}
