/*
61ms	43900KB
容易想到拓扑一下分配数字。对于等号，就先把它们合并成一个连通块，再拓扑。
不合法情况就是同一连通块中出现了`>`或`<`。
*/
#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e6+5,M=1e3+5;

int dgr[N],bel[N],fa[N],Ans[N];
char s[M][M];
struct Graph
{
	int Enum,H[N],nxt[N],to[N];
	inline void AE(int u,int v,int f)
	{
		dgr[v]+=f, to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
}G,T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool Check(int n,int m,int cnt)
{
	static int q[N];
	int tot=n+m,h=0,t=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(bel[i]==bel[j+n]&&s[i][j]!='=') return 0;
	for(int i=1; i<=cnt; ++i) if(!dgr[i]) q[t++]=i, Ans[i]=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=T.H[x],v; i; i=T.nxt[i])
		{
			v=T.to[i], Ans[v]=std::max(Ans[v],Ans[x]+1);
			if(!--dgr[v]) q[t++]=v;
		}
	}
	if(t<cnt) return 0;
	puts("Yes");
	for(int i=1; i<=n; ++i) printf("%d ",Ans[bel[i]]);
	puts("");
	for(int i=n+1; i<=tot; ++i) printf("%d ",Ans[bel[i]]);
	return t==cnt;
}

int main()
{
	int n=read(),m=read(),tot=n+m;
	for(int i=1; i<=tot; ++i) fa[i]=i;
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s[i]+1);
		for(int j=1; j<=m; ++j)
			if(s[i][j]=='>') G.AE(j+n,i,0);
			else if(s[i][j]=='<') G.AE(i,j+n,0);
			else fa[Find(i)]=Find(j+n);
	}
	int cnt=0;
	for(int i=1; i<=tot; ++i) if(fa[i]==i) bel[i]=++cnt;
	for(int i=1; i<=tot; ++i) if(fa[i]!=i) bel[i]=bel[Find(i)];
	for(int x=1; x<=tot; ++x)
		for(int i=G.H[x],v; i; i=G.nxt[i])
			if(bel[x]!=bel[v=G.to[i]]) T.AE(bel[x],bel[v],1);
	if(!Check(n,m,cnt)) puts("No");

	return 0;
}
