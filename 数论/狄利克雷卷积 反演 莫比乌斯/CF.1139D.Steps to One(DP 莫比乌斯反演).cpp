/*
140ms	10900KB
https://www.cnblogs.com/SovietPower/p/10692976.html
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#define mod 1000000007
typedef long long LL;
const int N=1e5+5;

int P[N>>2],mu[N],f[N],inv[N];
bool notP[N];
std::vector<int> fac[N];

inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod) k&1&&(t=1ll*t*x%mod);
	return t;
}
inline int G(int n,int k)
{
	LL ans=0;
	for(int i=0,l=fac[k].size(); i<l; ++i) ans+=mu[fac[k][i]]*(n/fac[k][i]);
	return ans%mod;
}
void Init(const int n)
{
	mu[1]=1;
	for(int i=2,cnt=0; i<=n; ++i)
	{
		if(!notP[i]) P[++cnt]=i, mu[i]=-1;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<=n; ++j)
		{
			notP[v]=1;
			if(i%P[j]) mu[v]=-mu[i];
			else break;
		}
	}
	for(int i=1; i<=n; ++i)
		for(int j=i; j<=n; j+=i) fac[j].push_back(i);
}

int main()
{
	int n; scanf("%d",&n);
	Init(n);
	f[1]=1, inv[1]=1;
	for(int i=2; i<=n; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int x=2; x<=n; ++x)
	{
		LL tmp=n;
		const std::vector<int> &v=fac[x];
		for(int i=0,l=v.size(),d; i+1<l; ++i) d=v[i], tmp+=1ll*f[d]*G(n/d,x/d);
		f[x]=tmp%mod*inv[n-n/x]%mod;
	}
	LL ans=0;
	for(int i=1; i<=n; ++i) ans+=f[i];
	printf("%d\n",int(ans%mod*inv[n]%mod));

	return 0;
}
