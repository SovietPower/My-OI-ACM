#include <cstdio>
const int N=3e6+6;

int n,p,inv[N];

int main()
{
	scanf("%d%d",&n,&p);
	inv[1]=1, puts("1");
	for(int i=2; i<=n; ++i)
		printf("%d\n",inv[i]=1ll*(p-p/i)*inv[p%i]%p);

	return 0;
}
