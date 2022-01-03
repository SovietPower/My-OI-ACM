/*
57056kb	1440ms
考虑没有深度限制，对整棵子树询问怎么做。
对于同种颜色中DFS序相邻的两个点$u,v$，在$dfn[u],dfn[v]$处分别$+1$，$dfn[LCA(u,v)]$处$-1$，这样答案就是求子树和了（同种颜色多余贡献的会被减掉）。
对于深度的限制，考虑维护$\max\{dep\}$棵线段树$T_i$，分别表示只考虑深度在$1\sim i$之间的点的贡献（下标依旧是DFS序）。因为我们发现，对于询问$(x,k)$，求$T_{dep[x]+k}$这棵线段树中（也就是只考虑深度在$1\sim dep[x]+k$的点），区间$[dfn[x],ed\_dfn[x]]$的和，就是答案。因为可能的问题是会统计到区间中深度$<dep[x]$的点，但是区间$[dfn[x],ed\_dfn[x]]$中没有深度$<dep[x]$的点啊！
所以我们按深度维护出可持久化线段树就OK了。
对于深度由$d-1$变成$d$，考虑在$T_d$中深度为$d$的点$x$的贡献。
同样像最初提到的那样，找出与$x$颜色相同且DFS序相邻的两个点$pre,nxt$，把$LCA(pre,nxt)$的$-1$加回去，再减掉$LCA(pre,x),LCA(x,nxt)$的贡献即可（当然这两个LCA中有一个就是$LCA(pre,nxt)$）。对每种颜色用$set$维护一下前驱后继。
复杂度$O(n\log n)$。
注意下$dep[x]+k$对$\max\{dep\}$取$\min$。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int col[N],root[N],H[N],nxt[N],dep[N],fa[N],sz[N],son[N],top[N],Index,dfn[N],ref[N],R[N];
std::set<int> st[N];
std::vector<int> vec[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	#define S N*37//2logn!
	int tot,sum[S],son[S][2];
	#undef S
	void Modify(int &x,int y,int l,int r,int p,int v)
	{
		x=++tot, sum[x]=sum[y]+v;
		if(l==r) {ls=rs=0; return;}
		int m=l+r>>1;
		p<=m ? (rs=son[y][1],Modify(ls,son[y][0],l,m,p,v)) : (ls=son[y][0],Modify(rs,son[y][1],m+1,r,p,v));
	}
	int Query(int x,int l,int r,int L,int R)
	{
		if(!x) return 0;
		if(L<=l && r<=R) return sum[x];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)+Query(rson,L,R);
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
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
inline int LCA(int u,int v)
{
	if(u==-1||v==-1) return -1;
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1, son[x]=0;//!
	for(int v=H[x]; v; v=nxt[v])
		dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	top[x]=tp, ref[dfn[x]=++Index]=x, vec[dep[x]].push_back(x);
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int v=H[x]; v; v=nxt[v])
			if(v!=son[x]) DFS2(v,v);
	}
	R[x]=Index;
}
void Solve()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) col[i]=read();
	for(int i=2; i<=n; ++i) AE(fa[i]=read(),i);
	dep[1]=1, DFS1(1), DFS2(1,1);
	int mx=1;
	for(int i=1; i<=n; ++i) mx=std::max(mx,dep[i]);
	for(int i=1; i<=mx; ++i)
	{
		root[i]=root[i-1];
		for(int j=0,l=vec[i].size(); j<l; ++j)
		{
			int x=vec[i][j],c=col[x];
			if(!st[c].empty())
			{
				std::set<int>::iterator it=st[c].upper_bound(dfn[x]);
				int nxt=it==st[c].end()?-1:ref[*it];
				int pre=it==st[c].begin()?-1:ref[*(--it)];
				int r1=LCA(pre,nxt),r2=LCA(pre,x),r3=LCA(x,nxt);
				if(r1==r2 && r3!=-1) T.Modify(root[i],root[i],1,n,dfn[r3],-1);
				else if(r1==r3 && r2!=-1) T.Modify(root[i],root[i],1,n,dfn[r2],-1);
			}
			T.Modify(root[i],root[i],1,n,dfn[x],1), st[c].insert(dfn[x]);
		}
	}
	for(int i=1,ans=0; i<=m; ++i)
	{
		int x=read()^ans,k=read()^ans;
		printf("%d\n",ans=T.Query(root[std::min(mx,dep[x]+k)],1,n,dfn[x],R[x]));
	}
	T.tot=0, Index=0, memset(H,0,n+1<<2);
	for(int i=1; i<=n; ++i) std::set<int>().swap(st[i]);
	for(int i=1; i<=mx; ++i) std::vector<int>().swap(vec[i]);
}

int main()
{
	for(int T=read(); T--; Solve());
	return 0;
}
