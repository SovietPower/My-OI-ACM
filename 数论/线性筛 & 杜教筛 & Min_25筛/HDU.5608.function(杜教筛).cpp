/*
http://www.cnblogs.com/SovietPower/p/8352820.html
注意：有μ所以会有负的！不能用Mod(x)，也不能直接取模(需先+mod) 
*/
#include<map>
#include<cstdio>
#include<cctype>
#define gc() getchar()
typedef long long LL;
const int N=600005,mod=1e9+7;

int n,mu[N+3],P[N>>1],f[N+3],cnt;
bool Not_P[N+3];
std::map<int,int> ref;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define Mod(x) x>=mod?x-=mod:0
void Init()
{
	mu[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!Not_P[i]) P[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*P[j]<N;++j)
		{
			Not_P[i*P[j]]=1;
			if(!(i%P[j])) {mu[i*P[j]]=0; break;}
			mu[i*P[j]]=-mu[i];
		}
	}
	for(int i=1;i<N;++i)
	{
		int t=((LL)i*i%mod-3*i%mod+2+mod)%mod;
		for(int j=i;j<N;j+=i)
			(f[j]+=mu[j/i]*t%mod)%=mod;
//		WA:	f[j]+=mu[j/i]*t%mod, Mod(f[j]);
	}
	for(int i=1;i<N;++i) f[i]=((f[i]+f[i-1])%mod+mod)%mod;
//WA:for(int i=1;i<N;++i) sum[i]=sum[i-1]+f[i]%mod, Mod(sum[i]);
}
int FP(LL x,int k)
{
	LL t=1;
	for(;k;k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}
const int inv3=FP(3,mod-2);//333333336
int Calc(int n)
{
	if(n<N) return f[n];
	if(ref.count(n)) return ref[n];
	int ans=(1LL*n*(n-1)%mod*(n-2)%mod*inv3%mod);
	for(int las,i=2;i<=n;i=las+1)
		las=n/(n/i),ans-=1ll*(las-i+1)*Calc(n/i)%mod,ans%=mod;
	return ref[n]=(ans+mod)%mod;
}

int main()
{
	Init();
	for(int t=read();t--;)
	{
		int n=read();
		printf("%d\n",Calc(n));
	}
	return 0;
}
