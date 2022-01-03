/*
6016kb	500ms
$Description$
给定一张无向带边权图(存在自环和重边)。求一条1->n的路径，使得路径经过边的权值的Xor和最大。可重复经过点/边，且边权和计算多次。
$Solution$
来找一些性质。从一个点出发，到达任意一个点后原路返回，那么得到的和仍为0。但是如果走完一个环后原路返回，则会得到这个环的Xor和。
那么从1点就可以得到任何一个环的Xor和。我们还需要一条1->n的路径，使得搭配上某些环后答案最大。于是我们就可以对环的权值构造线性基，拿路径Xor和在上面求最大值。
选取哪条路径呢？如果存在多条1->n的路径，实际上任意两条也构成了一个环，我们也已统计在内了。
即我们可以任意选取一条1->n的路径(反复走显然没啥用)，如果它不更优，会在与某个环Xor后换成一条更优的路径。(同理，对于路径上点的选择也是任意的。所有环都要算上)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e4+5,M=2e5+5;

int n,Enum,H[N],nxt[M],to[M];
LL base[69],len[M],val[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(LL w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline void Insert(LL x)
{
	for(int i=60; ~i; --i)
		if(x&(1ll<<i))
		{
			if(base[i]) x^=base[i];
			else {base[i]=x; break;}
		}
}
inline LL Query(LL x)
{
	for(int i=60; ~i; --i)
		x=std::max(x,x^base[i]);
	return x;
}
void DFS(int x,int f)
{
	vis[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) val[v]=val[x]^len[i], DFS(v,x);
		else if(v!=f) Insert(val[v]^val[x]^len[i]);
}

int main()
{
	n=read();
	for(int i=1,m=read(); i<=m; ++i) AddEdge(readll(),read(),read());
	DFS(1,1);
	printf("%lld\n",Query(val[n]));

	return 0;
}
