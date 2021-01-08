#include<stdio.h>
int main()
{
	int a[3];
	while(scanf("%d%d%d",&a[0],&a[1],&a[2]) != EOF){
		for(int i=0;i<3;i++)
			for(int j=i;j<3;j++)
				if(a[i]<a[j])
				{
					int temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
		printf("%d %d %d",a[0],a[1],a[2]);
	}
	return 0;
}
