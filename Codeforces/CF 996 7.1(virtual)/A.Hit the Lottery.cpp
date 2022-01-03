#include <cstdio>
#include <cctype>
#define gc() getchar()
const int val[]={1,5,10,20,100};

int n;

int main()
{
	scanf("%d",&n);
	int res=0;
	for(int i=4; ~i&&n; --i)
		res+=n/val[i], n-=(n/val[i])*val[i];
	printf("%d",res);
	
	return 0;
}
