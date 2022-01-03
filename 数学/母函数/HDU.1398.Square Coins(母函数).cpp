//0MS 1512K
#include <cstdio>
#include <cstring>
const int N=303;

int n,f[N],tmp[N]; //平方数。。实际方案数也不是那么多。

void Init()
{
	n=300;//N=300不是17*17。。
	for(int i=0; i<=n; ++i) f[i]=1;
	for(int i=2; i<=17; ++i)
	{
		memset(tmp,0,sizeof tmp);
		for(int j=0; j<=n; ++j)
			for(int k=0; j+k<=n; k+=i*i)
				tmp[j+k]+=f[j];
		memcpy(f,tmp,sizeof f);
	}
}

int main()
{
	Init();
	while(scanf("%d",&n),n) printf("%d\n",f[n]);
	return 0;
}
