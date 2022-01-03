#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,sz[N],A[N],Enum,H[N],nxt[N<<1],to[N<<1];
std::set<int> st[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
bool Solve()
{
	if(A[1]!=1) return 0;
	int h=1,t=1,now=2; vis[1]=1;
	for(int i=H[1]; i; i=nxt[i]) st[1].insert(to[i]);
	while(now<=n && h<=t)
	{
		int x=A[now++]; if(vis[x]) return 0;
		if(!st[h].count(x)) return 0;
		++t, ++sz[h], vis[x]=1;
		for(int i=H[x]; i; i=nxt[i]) if(!vis[to[i]]) st[t].insert(to[i]);
		if(st[t].empty()) --t;
		if(sz[h]==st[h].size()) ++h;
	}
	return now>n;
}

int main()
{
	n=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	for(int i=1; i<=n; ++i) A[i]=read();
	puts(Solve()?"Yes":"No");

	return 0;
}
