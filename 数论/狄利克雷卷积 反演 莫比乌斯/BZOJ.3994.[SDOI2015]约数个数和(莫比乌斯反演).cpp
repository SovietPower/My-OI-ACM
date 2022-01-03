//1772kb	6448ms
//https://www.cnblogs.com/SovietPower/p/9665103.html
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e4;

int cnt,P[N>>3],mu[N+3];
long long g[N+3];
bool not_P[N+3];

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Init()
{
	mu[1]=1;
	for(int i=2; i<=N; ++i)
	{
		if(!not_P[i]) P[++cnt]=i, mu[i]=-1;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<=N; ++j)
		{
			not_P[v]=1;
			if(i%P[j]) mu[v]=-mu[i];
			else break;//mu[v]=0;
		}
	}
	for(int i=1; i<=N; ++i) mu[i]+=mu[i-1];
	for(int i=1; i<=N; ++i)
	{
		long long ans=0;
		for(int j=1,nxt; j<=i; j=nxt+1)
		{
			nxt=i/(i/j);
			ans+=1ll*(nxt-j+1)*(i/j);
		}
		g[i]=ans;
	}
}

int main()
{
	Init();
	for(int T=read(),n,m; T--; )
	{
		n=read(),m=read();
		long long ans=0;
		for(int i=1,nxt,lim=std::min(n,m); i<=lim; i=nxt+1)
		{
			nxt=std::min(n/(n/i),m/(m/i));
			ans+=1ll*(mu[nxt]-mu[i-1])*g[n/i]*g[m/i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
