/*
5869ms	213632K
拆式子，记$dis_i$为$i$到根节点的路径权值和，$Ans=\sum dis_{p_i}+\sum dis_k-2\sum dis_{LCA(p_i,k)}$。$\sum dis_{LCA(p_i,k)}$的求法类似[[LNOI2014]LCA]()，在每个$u\to v$路径上，每个$p_i$到根节点的路径上权值$+1$（本题就是下放点权，每次所有点的$sum$加上它的点权），然后求一遍$k$到根节点的路径权值和就是答案。
为了方便，再差分，原修改是$\sum_{i\in(u,v)}i\to root$，变成$\sum_{i\in(u,root)}i\to root+\sum_{i\in(v,root)}i\to root-\sum_{i\in(LCA(u,v),root)}i\to root-\sum_{i\in fa[(LCA(u,v)],root)}i\to root$。
对每个点$x$建一棵可持久化线段树，每次在这棵树上修改$p_x$到$root$的路径，就可以了。
需要树剖，也就是区间修改，可以标记永久化。
查询就在四棵线段树上查。复杂度$(n+q)\log^2n$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int n,P[N],Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],dep[N],fa[N],sz[N],son[N],top[N],dfn[N],ref[N],root[N];
LL w[N],dis[N],sump[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	#define S N*100
	int tot,son[S][2],tm[S];
	LL sum[S];
	#undef S
	void Modify(int &x,int y,int l,int r,int L,int R)
	{
		sum[x=++tot]=sum[y], tm[x]=tm[y], ls=son[y][0], rs=son[y][1];
		if(L<=l && r<=R) {++tm[x]; return;}
		sum[x]=sum[y]+w[std::min(r,R)]-w[std::max(l,L)-1];
		int m=l+r>>1;
		if(L<=m) Modify(ls,son[y][0],l,m,L,R);
		if(m<R) Modify(rs,son[y][1],m+1,r,L,R);
	}
	LL Query(int x,int l,int r,int L,int R)
	{
		if(!x) return 0;
		LL res=tm[x]*(w[std::min(r,R)]-w[std::max(l,L)-1]);
		if(L<=l && r<=R) return sum[x]+res;
		int m=l+r>>1;
		if(L<=m) res+=Query(lson,L,R);
		if(m<R) res+=Query(rson,L,R);
		return res;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int w,int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, dis[v]=dis[x]+len[i], DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	top[x]=tp, ref[dfn[x]=++Index]=x, sump[x]=sump[fa[x]]+dis[P[x]];//son!
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x])
			{
				if(v!=son[x]) DFS2(v,v);
				w[dfn[v]]=len[i];//son!
			}
	}
}
void Modify(int x)
{
	int p=P[x]; root[x]=root[fa[x]];
	while(p>1) T.Modify(root[x],root[x],1,n,dfn[top[p]],dfn[p]), p=fa[top[p]];
}
LL Query(int k,int rt)
{
	if(!rt) return 0;
	LL ans=0;
	while(k>1) ans+=T.Query(rt,1,n,dfn[top[k]],dfn[k]), k=fa[top[k]];
	return ans;
}

int main()
{
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);

	const int type=read(),n=read(),q=read(); ::n=n;
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	for(int i=1; i<=n; ++i) P[i]=read();
	dep[1]=1, DFS1(1), DFS2(1,1);
	for(int i=1; i<=n; ++i) w[i]+=w[i-1];
	for(int i=1; i<=n; ++i) Modify(ref[i]);
	LL ans=0;
	for(int i=1; i<=q; ++i)
	{
		int u=read(),v=read(),k=read();
		if(type) u^=ans, v^=ans, k^=ans;
		int w=LCA(u,v),tot=dep[u]+dep[v]-(dep[w]<<1)+1;
		ans=tot*dis[k]+sump[u]+sump[v]-sump[w]-sump[fa[w]];
		LL tmp=Query(k,root[u])+Query(k,root[v])-Query(k,root[w])-Query(k,root[fa[w]]);
		printf("%lld\n",ans-=tmp<<1);
	}

	return 0;
}
