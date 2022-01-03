/*
656ms	84.03MB
$Description$
给定连通无向图，$q$次询问，每次询问给定$S,T,L,R$，你需要从$S$走到$T$，但在过程中需在任意点恰好切换一次形态（可在$S,T$）。
切换形态前，你不能走$[1,L-1]$号点；切换形态后，你不能走$[R+1,n]$号点。求是否有合法$S\to T$的路径。
$n,q\leq 2\times 10^5,\ m\leq 4\times 10^5$。
$Solution$
$Kruskal$重构树（具体是所有点按从小到大/从大到小的顺序，依次加入这些点的边），我们可以得到两棵树（和那两题不一样的是这题的权值在点上，不需要新建节点）。
对于询问$(S,T,L,R)$，可以倍增找出$S,T$可以在哪棵子树中随便走。
那么只需要判断两棵子树是否有交就可以惹。
注意到子树的DFS序是连续的，我们可以在第一个子树的某个数据结构上，查第二个子树的DFS序区间。用主席树就可以了，主席树的下标是每个点在第二棵树上的DFS序。判断第一个子树在第二个子树的DFS序区间中是否有值即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BIT 17
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,M=8e5+5;

int n,root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Graph
{
	int Enum,H[N],nxt[M],to[M];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
}G;
struct Tree
{
	int fg,fa[N][BIT+1],F[N],H[N],nxt[N],L[N],R[N],Index;
	int Find(int x)
	{
		return x==F[x]?x:F[x]=Find(F[x]);
	}
	inline void AE(int u,int v)
	{
		nxt[v]=H[u], H[u]=v;
	}
	inline int Jump(int x,int k)
	{
		if(fg)
		{
			for(int i=BIT; ~i; --i)
				if(fa[x][i]&&fa[x][i]<=k) x=fa[x][i];
		}
		else
		{
			for(int i=BIT; ~i; --i)
				if(fa[x][i]>=k) x=fa[x][i];
		}
		return x;
	}
	void DFS(int x,int dep)
	{
		L[x]=++Index;
		for(int i=1; 1<<i<=dep; ++i) fa[x][i]=fa[fa[x][i-1]][i-1];
		for(int v=H[x]; v; v=nxt[v]) fa[v][0]=x, DFS(v,dep+1);
		R[x]=Index;
	}
	void Build(const int n)
	{
		for(int i=1; i<=n; ++i) F[i]=i;
		if(fg)
		{
			for(int x=1,k=1; x<=n; ++x)
				for(int i=G.H[x],v; i; i=G.nxt[i])
					if((v=G.to[i])<x)
					{
						int r1=Find(x),r2=Find(v);//r1==x
						if(r1!=r2)
						{
							F[r2]=r1, AE(r1,r2);
							if(++k==n) break;
						}
					}
		}
		else
		{
			for(int x=n,k=1; x; --x)
				for(int i=G.H[x],v; i; i=G.nxt[i])
					if((v=G.to[i])>x)
					{
						int r1=Find(x),r2=Find(v);
						if(r1!=r2)
						{
							F[r2]=r1, AE(r1,r2);
							if(++k==n) break;
						}
					}
		}
		DFS(fg?n:1,0);
	}
}T1,T2;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,son[y][0],l,m
	#define rson rs,son[y][1],m+1,r
	#define S N*19
	int tot,sz[S],son[S][2];
	#undef S
	void Modify(int &x,int y,int l,int r,int p)
	{
		sz[x=++tot]=sz[y]+1;
		if(l==r) return;
		int m=l+r>>1;
		p<=m?(rs=son[y][1],Modify(lson,p)):(ls=son[y][0],Modify(rson,p));
	}
	int Query(int x,int y,int l,int r,int L,int R)//y-x
	{
		if(sz[y]-sz[x]<=0) return 0;
		if(L<=l && r<=R) return 1;
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)||Query(rson,L,R);
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void DFS(int x)
{
	static int Index=0;
	++Index, T.Modify(root[Index],root[Index-1],1,n,T2.L[x]);
	for(int v=T1.H[x]; v; v=T1.nxt[v]) DFS(v);
}

int main()
{
	int n=read(),m=read(),Q=read(); ::n=n;
	for(int i=1; i<=m; ++i) G.AE(read()+1,read()+1);
	T1.Build(n), T2.fg=1, T2.Build(n), DFS(1);
	for(int s,t; Q--; )
		s=read()+1,t=read()+1,s=T1.Jump(s,read()+1),t=T2.Jump(t,read()+1),
		putchar(T.Query(root[T1.L[s]-1],root[T1.R[s]],1,n,T2.L[t],T2.R[t])?'1':'0'), putchar('\n');

	return 0;
}
