//17912kb	35060ms
//http://www.cnblogs.com/SovietPower/p/8718273.html
//F[]用int，FP()中的长式子放到外面，优化还是~~比较明显~~有的。
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod (1000000007)
typedef long long LL;
const int N=1e6+2;

int cnt,P[N>>3],mu[N+2],f[N+2],inv_f[N+2],F[N+2];
bool Not_p[N+2];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}
void Init()
{
	mu[1]=f[1]=inv_f[1]=1;//f[0]=0!
	for(int i=2; i<N; ++i)
		f[i]=(f[i-1]+f[i-2])%mod, inv_f[i]=FP(f[i],mod-2);
	for(int i=2; i<N; ++i)
	{
		if(!Not_p[i]) P[++cnt]=i,mu[i]=-1;
		for(int v,j=1; j<=cnt&&(v=i*P[j])<N; ++j)
		{
			Not_p[v]=1;
			if(i%P[j]) mu[v]=-mu[i];
			else {mu[v]=0; break;}
		}
	}
	for(int i=0; i<N; ++i) F[i]=1;//F[0]=1
	for(int i=1; i<N; ++i)
		if(mu[i]==1)
			for(int d=1,T=0; (T+=i)<N; ++d) F[T]=1ll*F[T]*f[d]%mod;
		else if(mu[i]==-1)
			for(int d=1,T=0; (T+=i)<N; ++d) F[T]=1ll*F[T]*inv_f[d]%mod;
	for(int i=2; i<N; ++i) F[i]=1ll*F[i]*F[i-1]%mod;
}
inline int inv(int x){
	return FP(x,mod-2);
}
int Calc(int n,int m)
{
	if(n>m) std::swap(n,m);
	int res=1;
	for(int nxt,tmp,i=1; i<=n; i=nxt+1)
	{
		nxt=std::min(n/(n/i),m/(m/i)),
		tmp=1ll*F[nxt]*inv(F[i-1])%mod,//存次数就没用啦？大概是留一个式子比较好？
		res=1ll*res*FP(tmp,1ll*(n/i)*(m/i)%(mod-1))%mod;//注意次幂是模(mod-1)。
	}
	return res;
}

int main()
{
	Init();
	int T,n,m; scanf("%d",&T);
	while(T--)
		scanf("%d%d",&n,&m),printf("%d\n",Calc(n,m));

	return 0;
}
