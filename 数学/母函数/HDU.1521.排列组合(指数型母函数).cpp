//0MS 1524K
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=13;

int n,m,num[N],fac[N];
double f[N],tmp[N];

int main()
{
	fac[0]=1;
	for(int i=1; i<=11; ++i) fac[i]=fac[i-1]*i;
	while(~scanf("%d%d",&n,&m))
	{
		for(int i=1; i<=n; ++i) scanf("%d",&num[i]);
		memset(f,0,sizeof f);
		for(int i=0; i<=num[1]; ++i) f[i]=1.0/fac[i];
		for(int i=2; i<=n; ++i)
		{
			memset(tmp,0,sizeof tmp);
			for(int j=0; j<=m; ++j)
				if(f[j])
					for(int k=0; k<=num[i]&&j+k<=m; ++k)
						tmp[j+k]+=f[j]/(double)fac[k];//要乘的系数为1/k! 
			memcpy(f,tmp,sizeof f);
		}
		printf("%.0lf\n",1.0*fac[m]*f[m]);//f:组合数 
	}
	return 0;
}
