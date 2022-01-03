/*
220140kb	7192ms(好慢啊)
$Description$
给定一棵树，每个点有一种特产$a_i$（可相同）。$q$次询问，每次给$2\leq c\leq 5$个人及其位置，他们会走到他们的公共LCA处。
每个人可以从他走的路径上带一些特产，但需满足：所有人带的特产数量相同；不能有两种相同特产。
求最多一共能带多少种特产。
$n\leq 3\times 10^5,\ q\leq 5\times 10^4$，特产种数$\leq 1000$。
$Solution$
只有指向父节点的单向道路，所以c个人肯定在LCA处汇合。那么就成了有c条到LCA的路径，求最大的x，满足能从c条路径中各选出x个数，且它们不同。
先要维护一条路径的数的种类数，可以树剖+每条链维护一个bitset解决。用vector一条链加一个bitset，SDOI R2现场测过我记得空间还不算特别大。。当然本题数字只有1000种，一个点开一个bitset没问题。最后合并时还要通过线段树。
假设答案是x，那么c个人都要从可选特产中不重复地选x个，把每个人拆成x个点就是一个二分图完备匹配。
由Hall定理，左边集合(c*x个点)任意一个子集与右边集合相邻的点数应不小于该子集大小。因为每个人的x个点的连边相同(复制了x次)，所以对每个人只需判断x个都选的子集。
c很小，2^c枚举子集。与右边集合相邻点数就是选中人的bitset的并的大小size。设枚举了s个人，那么每次枚举有 x*s <= size。
所以 x = min{size/s}。
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bitset std::bitset<M>
const int N=3e5+3,M=1002;

int n,m,Q,A[N],num[100],H[N],Enum,to[N],nxt[N],fa[N],dep[N],sz[N],son[N],top[N],dfn[N],Index;
Bitset bit[N];//prefix
char IN[MAXIN],*SS=IN,*TT=IN;//,OUT[N*30],*O=OUT;
struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	int col[N];
	Bitset t[N<<2];

	#define Update(rt) t[rt]=t[lson]|t[rson]
	void Build(int l,int r,int rt)
	{
		if(l==r) t[rt][col[l]]=1;
		else Build(l,l+r>>1,rt<<1), Build((l+r>>1)+1,r,rt<<1|1), Update(rt);
	}
	Bitset Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return t[rt];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(ToL,L,R)|Query(ToR,L,R);
			else return Query(ToL,L,R);
		return Query(ToR,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
//inline void print(int x)
//{
//	if(x>9) print(x/10);
//	*O++ = x%10+'0';
//}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
	{
		fa[v=to[i]]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
		if(sz[v]>mx) mx=sz[v], son[x]=v;
	}
}
void DFS2(int x,int tp)
{
	top[x]=tp, dfn[x]=++Index, T.col[Index]=A[x];
	bit[x][A[x]]=1;
	if(son[x])
	{
		bit[son[x]]|=bit[x], DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=son[x]) DFS2(to[i],to[i]);
	}
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
Bitset Query(int u,int w)
{
	Bitset s;
	while(top[u]!=top[w]) s|=bit[u], u=fa[top[u]];
	return s|T.Query(1,n,1,dfn[w],dfn[u]);
}

int main()
{
	for(int i=1,s=0; i<1<<5; num[i++]=s,s=0)
		for(int j=0; j<5; ++j) if(i>>j & 1) ++s;
	n=read(),m=read(),Q=read();
	for(int i=2; i<=n; ++i) AddEdge(read(),i);
	for(int i=1; i<=n; ++i) A[i]=read();
	DFS1(1), DFS2(1,1), T.Build(1,n,1);
	for(int c,p[7],lca,ans; Q--; )
	{
		c=read();
		for(int i=1; i<=c; ++i) p[i]=read();
		lca=LCA(p[1],p[2]);
		for(int i=3; i<=c; ++i) lca=LCA(lca,p[i]);
		ans=m;
		for(int s=1; s<1<<c; ++s)
		{
			Bitset tmp;
			for(int i=1; i<=c; ++i)
				if(s>>i-1 & 1) tmp|=Query(p[i],lca);
			ans=std::min(ans,(int)(tmp.count()/num[s]));
		}
		printf("%d\n",ans*c);
//		print(ans*c), *O++='\n';
	}
//	fwrite(OUT,O-OUT,1,stdout);

	return 0;
}
