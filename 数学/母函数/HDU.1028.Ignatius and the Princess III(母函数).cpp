//0MS 1500K
//ĸ��������������DP���С���
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N=122;

int n,f[N],tmp[N];

int main()
{
	while(~scanf("%d",&n))
	{
		memset(f,0,sizeof f), f[0]=1;//or ���ߣ���n����
		for(int i=1; i<=n; ++i) f[i]=1;
		for(int i=2; i<=n; ++i)
		{
			memset(tmp,0,sizeof tmp);
			for(int j=0; j<=n; ++j)
				for(int k=0; j+k<=n; k+=i)
					tmp[j+k]+=f[j];
			memcpy(f,tmp,sizeof f);
		}
		printf("%d\n",f[n]);
	}
	return 0;
}
