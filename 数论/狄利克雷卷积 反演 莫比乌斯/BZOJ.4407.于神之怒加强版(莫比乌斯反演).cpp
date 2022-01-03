//49648kb	16248ms
//https://www.cnblogs.com/SovietPower/p/9521715.html
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define MAX 5000000
#define mod (1000000007)
const int N=5e6+5;

int cnt,P[N>>3],mu[N],F[N],pw[N>>3];
bool not_P[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
void Pre(int K)
{
	F[1]=mu[1]=1;
	for(int i=2; i<=MAX; ++i)
	{
		if(!not_P[i])
			P[++cnt]=i, mu[i]=-1, pw[cnt]=FP(i,K), F[i]=(pw[cnt]-1)%mod;
		for(int v,j=1; j<=cnt&&(v=i*P[j])<=MAX; ++j)
		{
			not_P[v]=1;
			if(i%P[j]) mu[v]=-mu[i], F[v]=1ll*F[i]*F[P[j]]%mod;
			else {mu[v]=0, F[v]=1ll*F[i]*pw[j]%mod; break;}
		}
	}
	for(int i=2; i<=MAX; ++i) F[i]+=F[i-1], F[i]>=mod&&(F[i]-=mod);
}

int main()
{
	int T=read(),K=read(); Pre(K);
	for(int n,m; T--; )
	{
		n=read(), m=read();
		long long res=0;
		for(int i=1,nxt,lim=std::min(n,m); i<=lim; i=nxt+1)
		{
			nxt=std::min(n/(n/i),m/(m/i));
			res+=1ll*(F[nxt]-F[i-1])*(n/i)%mod*(m/i)%mod;
		}
		printf("%lld\n",(res%mod+mod)%mod);
	}
	return 0;
}
