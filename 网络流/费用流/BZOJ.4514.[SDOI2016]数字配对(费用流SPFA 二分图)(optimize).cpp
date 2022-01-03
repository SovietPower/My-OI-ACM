/*
2840kb	28ms
常规做建二分图跑费用流很容易，但因为拆了点每对数之间可能选两次。但是既然选了一次那就一定会选第二次。最后费用即将变成负数时判一下还能选多少个，然后流量除以二即可。
因为匹配条件是$i$可整除$j$且结果是质数，那么$i,j$之间质因子次数一定相差一，可以直接判，同时根据质因子次数奇偶性可以分别连源点汇点，就没有之前的问题了。
另外这张二分图里费用就是$dis[T]$。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=205,M=(N*N+N)*2,INF=1<<30;
const LL INFll=1ll<<60;

int T,Enum,H[N],nxt[M],fr[M],to[M],cap[M],pre[N];
LL dis[N],cost[M];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w,LL c)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
int Calc(int x)
{
	int t=0;
	for(int i=2; 1ll*i*i<=x; ++i)
		if(!(x%i))
		{
			x/=i, ++t;
			while(!(x%i)) x/=i, ++t;
		}
	if(x!=1) ++t;
	return t;
}
bool SPFA()
{
	static bool inq[N];
	static std::queue<int> q;
	for(int i=1; i<=T; ++i) dis[i]=-INFll;
	q.push(0), dis[0]=0;
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]<dis[x]+cost[i] && cap[i])
				pre[v]=i, dis[v]=dis[x]+cost[i], !inq[v]&&(q.push(v),inq[v]=1);
	}
	return dis[T]>-INFll;
}
int Solve()
{
	int res=0; LL now=0;
	while(SPFA())
	{
		int mn=INF;
		for(int i=T; i; i=fr[pre[i]]) mn=std::min(mn,cap[pre[i]]);
		if(now+dis[T]*mn>=0)
		{
			now+=dis[T]*mn, res+=mn;
			for(int i=T; i; i=fr[pre[i]]) cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
		}
		else
		{
			res+=now/std::abs(dis[T]);//abs!!
			break;
		}
	}
	return res;
}

int main()
{
	static int A[N],B[N],C[N],tm[N];

	freopen("pair.in","r",stdin);
	freopen("pair.out","w",stdout);

	int n=read(); Enum=1, T=n+1;
	for(int i=1; i<=n; ++i) tm[i]=Calc(A[i]=read());
	for(int i=1; i<=n; ++i) B[i]=read();
	for(int i=1; i<=n; ++i) C[i]=read();
	for(int i=1; i<=n; ++i)
	{
		if(tm[i]&1)
		{
			AE(0,i,B[i],0);
			for(int j=1; j<=n; ++j)
				if(!(tm[j]&1) && tm[i]-tm[j]==1 && !(A[i]%A[j])) AE(i,j,INF,1ll*C[i]*C[j]);
		}
		else
		{
			AE(i,T,B[i],0);
			for(int j=1; j<=n; ++j)
				if(tm[j]&1 && tm[i]-tm[j]==1 && !(A[i]%A[j])) AE(j,i,INF,1ll*C[i]*C[j]);
		}
	}
	printf("%d\n",Solve());

	return 0;
}
