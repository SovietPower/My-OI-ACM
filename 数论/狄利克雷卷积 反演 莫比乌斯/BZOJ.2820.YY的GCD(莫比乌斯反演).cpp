//131680kb	3380ms
//http://www.cnblogs.com/SovietPower/p/8709840.html
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e7+1;

int cnt,P[1000005],f[N+2],mu[N+2],sum[N+2];
bool Not_p[N+2];

void Make_Table()
{
	mu[1]=1;/*f[1]=0;*/
	for(int i=2; i<N; ++i)
	{
		if(!Not_p[i]) P[++cnt]=i,mu[i]=-1,f[i]=1;
		for(int j=1; j<=cnt&&i*P[j]<N; ++j)
		{
			Not_p[i*P[j]]=1;
			if(i%P[j]) mu[i*P[j]]=-mu[i], f[i*P[j]]=mu[i]-f[i];
			else {mu[i*P[j]]=0, f[i*P[j]]=mu[i]; break;}
		}
	}
	for(int i=1; i<N; ++i) sum[i]=sum[i-1]+f[i];
//	for(int i=1; i<=cnt; ++i)
//		for(int j=1; j*P[i]<N; ++j)
//			sum[j*P[i]]+=mu[j];
//	for(int i=2; i<N; ++i) sum[i]+=sum[i-1];
}

int main()
{
	Make_Table();
	int T,n,m; LL res;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m), res=0;
		if(n>m) std::swap(n,m);
		for(int nxt,i=1; i<=n; i=nxt+1)
		{
			nxt=std::min(n/(n/i),m/(m/i));
			res+=1ll*(sum[nxt]-sum[i-1])*(n/i)*(m/i);
		}
		printf("%lld\n",res);
	}
	return 0;
}
