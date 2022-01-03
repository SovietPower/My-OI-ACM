/*
17912kb	33888ms
注意本题特殊在是次幂=-=：mu[]可能等于-1，即乘一个F[]的逆元；指数要对mod-1取模。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=1e6+2;

int sum[N],F[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
void Init()
{
	static int cnt,P[N>>3],mu[N],invF[N];
	static bool notP[N];
	F[0]=0, F[1]=F[2]=invF[1]=invF[2]=1;
	for(int i=3; i<N; ++i) F[i]=F[i-1]+F[i-2], Mod(F[i]), invF[i]=FP(F[i],mod-2);
	mu[1]=1;
	for(int i=2; i<N; ++i)
	{
		if(!notP[i]) P[++cnt]=i, mu[i]=-1;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<N; ++j)
		{
			notP[v]=1;
			if(i%P[j]) mu[v]=-mu[i];
			else {mu[v]=0; break;}
		}
	}
	for(int i=0; i<N; ++i) sum[i]=1;//sum[0]=1，因为询问的时候要用到*inv(sum[0]) = =
	for(int d=1; d<N; ++d)//可以先枚举这个mu[d]，就可以在循环外写if了=v= 
		if(mu[d]==1)
			for(int T=0,i=1; (T+=d)<N; ++i) sum[T]=1ll*sum[T]*F[i]%mod;
		else if(mu[d]==-1)
			for(int T=0,i=1; (T+=d)<N; ++i) sum[T]=1ll*sum[T]*invF[i]%mod;
	for(int i=2; i<N; ++i) sum[i]=1ll*sum[i]*sum[i-1]%mod;
}

int main()
{
	Init();
	for(int T=read(); T--; )
	{
		const int n=read(),m=read();
		LL ans=1;
		for(int i=1,l=std::min(n,m),nxt; i<=l; i=nxt+1)
		{
			nxt=std::min(n/(n/i),m/(m/i));
			ans=ans*FP(1ll*sum[nxt]*FP(sum[i-1],mod-2)%mod,1ll*(n/i)*(m/i)%(mod-1))%mod;
		}
		printf("%lld\n",ans);
	}

	return 0;
}
