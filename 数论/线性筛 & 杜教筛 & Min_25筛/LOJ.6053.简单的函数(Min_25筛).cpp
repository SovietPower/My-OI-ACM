//1214ms	4.12M
//https://www.cnblogs.com/SovietPower/p/10101497.html
#include <cmath>
#include <cstdio>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=2e5+5;

int Sqr,cnt,P[N>>2],sp[N],id1[N],id2[N],g[N],h[N];
LL n,w[N];
bool notP[N];

void Init(int n)
{
	notP[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!notP[i]) P[++cnt]=i, sp[cnt]=sp[cnt-1]+i, Mod(sp[cnt]);
		for(int j=1; j<=cnt && i*P[j]<=n; ++j)
		{
			notP[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
int S(LL x,int y)
{
	if(x<=1||(y!=cnt+1&&P[y]>x)) return 0;//注意y=cnt+1时也需要计算！
	int k=x<=Sqr?id1[x]:id2[n/x];
	LL res=g[k]-sp[y-1]-h[k]+y-1;//g-h
	if(y==1) res+=2;//f(2)还是就放到里面算吧 否则要判下n<2。
	for(int i=y; /*i<=cnt&&*/1ll*P[i]*P[i]<=x; ++i)
	{
		LL p=P[i],p1=p,p2=p*p;
		for(int e=1; p2<=x; ++e,p1=p2,p2*=p)
			res+=1ll*(p^e)*S(x/p1,i+1)%mod+(p^(e+1));
		res%=mod;
	}
	return res%mod;
}

 main()
{
	scanf("%lld",&n); Init(Sqr=sqrt(n+0.5));
	int m=0;
	for(LL i=1,j; i<=n; i=j+1)
	{
		w[++m]=n/i, j=n/w[m];
		if(w[m]<=Sqr) id1[w[m]]=m;
		else id2[j]=m;
		g[m]=w[m]&1?w[m]%mod*((w[m]+1>>1)%mod)%mod-1:(w[m]>>1)%mod*(w[m]%mod+1)%mod-1;//w乘之前要取模！
		h[m]=(w[m]-1)%mod;
	}
	P[cnt+1]=1e9, w[m+1]=-1;
	for(int j=1; j<=cnt; ++j)
	{
		int pj=P[j]; LL lim=1ll*pj*pj;
		for(int i=1; lim<=w[i]; ++i)
		{
			int k=w[i]/pj<=Sqr?id1[w[i]/pj]:id2[n/(w[i]/pj)];//n/(w/pj)! id1[x]=x，但id2[x]的编号是对[n/x]的。
			(g[i]-=1ll*pj*(g[k]-sp[j-1])%mod)%=mod;//g[k]-sp[j-1]有可能是负的，如果+mod会爆int！
			h[i]+=mod-h[k]+j-1, Mod(h[i]);
		}
	}
	printf("%d\n",((S(n,1)+1)%mod+mod)%mod);

	return 0;
}
