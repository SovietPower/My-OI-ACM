/*
对每个限制，可以发现能拆成若干不等式。
然后就是差分约束了（但是要判的情况有点多）。
注意$i\rightarrow i+1$连边。
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=5e3+5,M=4e5+5;
const LL INF=1e16;

int Enum,H[N],nxt[M],to[M],val[M],tm[N];
LL dis[N];
bool inq[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
}
bool SPFA(int n)//0~n-1
{
	std::queue<int> q;
	for(int i=0; i<=n; ++i) dis[i]=-INF, tm[i]=0;
	tm[0]=dis[0]=0, q.push(0);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]<dis[x]+val[i])
			{
				dis[v]=dis[x]+val[i];
				if(!inq[v])
				{
					if(++tm[v]>n+1) return 0;
					inq[v]=1, q.push(v);
				}
			}
	}
	return 1;
}

int main()
{
	for(int Ts=1,TS=read(); Ts<=TS; ++Ts)
	{
		int n=read(),m=read(),K=read();
		Enum=0, memset(H,0,n+2<<2), memset(inq,0,N+2), memset(tm,0,N+2<<2);
		for(int i=1; i<=m; ++i)
		{
			int A=read(),B=read(),C=read(),D=read();
			if(A==B)
			{
				if(C==D) AE(A-1,C-1,K), AE(C-1,A-1,-K);
				else A==C?AE(A-1,C,K+1):(AE(C-1,A-1,-(K-1)),AE(A-1,C,K+1));
			}
			else
			{
				if(C==D) B==C?AE(A-1,C-1,K+1):(AE(C-1,A,-(K-1)),AE(A-1,C-1,K+1));
				else if(B==C) AE(A-1,B,K+1);
				else if(A==C) AE(A-1,A,K+1);
				else AE(C-1,A,-(K-1)),AE(A-1,C,K+1);
			}
		}
		for(int i=1; i<n; ++i) AE(i-1,i,1), AE(i,i-1,-2e9);

		printf("Case #%d:",Ts);
		int f=SPFA(n);
		if(!f) puts(" IMPOSSIBLE");
		else
		{
			for(int i=0; i<n-1; ++i) printf(" %lld",std::min(dis[i+1]-dis[i],(LL)2e9));
			puts("");
		}
	}

	return 0;
}
