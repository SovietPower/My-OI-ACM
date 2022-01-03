//贪心策略显然 但可能要注意特殊情况(比如D=N-1,K=1)。
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=4e5+7,M=N<<1;

int n,D,K,now,dgr[N],Enum,H[N],nxt[M],to[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	++dgr[u], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[v], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Link(int x,int dep)
{
	if(!dep) return;
	for(int i=K-dgr[x]; i>0&&now<n; --i) AddEdge(x,++now), Link(now,dep-1);
}
bool Solve()
{
	if(D>=n) return 0;
	for(int i=1; i<=D; ++i) AddEdge(i,i+1);
	now=D+1;
	for(int i=2; i<=D&&now<n; ++i) Link(i,D-std::max(i-1,D+1-i));
	for(int i=1; i<=n; ++i) if(dgr[i]>K) return 0;
//	DFS1(1,1,0), Max=0, DFS1(V,V,0);
//	if(Max!=D) return 0;
	return now>=n;
}
void DFS_for_Ans(int x,int f)
{
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) printf("%d %d\n",x,to[i]), DFS_for_Ans(to[i],x);
}

int main()
{
	n=read(), D=read(), K=read();
	if(Solve()) puts("YES"), DFS_for_Ans(1,1);
	else puts("NO");

	return 0;
}
