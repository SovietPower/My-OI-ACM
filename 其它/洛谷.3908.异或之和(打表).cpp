//打表找规律!! 
#include<cstdio>
using namespace std;

void Make_Table()
{
	freopen("t.txt","w",stdout);
	int now=1;
	printf("1:1\n");
	for(int i=2;i<=666;++i)
		now^=i,printf("%d:\t%d\n",i,now);
}

int main()
{
//	Make_Table();
	long long n;
	scanf("%lld",&n);
	switch(n%4)
	{
		case 0:printf("%lld",n);
			   break;
		case 1:printf("%d",1);
			   break;
		case 2:printf("%lld",n+1);
			   break;
		case 3:printf("%d",0);
			   break;
	}
	return 0;
}
