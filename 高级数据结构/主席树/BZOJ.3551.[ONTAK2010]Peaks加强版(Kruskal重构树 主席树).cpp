/*
81128kb	9952ms
$Description$
有n个座山，其高度为hi。有m条带权双向边连接某些山。多次询问，每次询问从v出发 只经过边权<=x的边 所能到达的山中，第K高的是多少。
强制在线。
$Solution$
首先要求最小生成树。然后每个<=x的限制会把范围限制在一个连通块中，但这样还是没法做。
参照[NOI2018]归程的思路，把所有叶节点作为原节点，令它们的父节点或是某个祖先节点代表每条边（边权），重构一棵树。
具体就是从小到大加入树边，然后在两个点原先集合的代表节点之间建父节点。
那么对于<=x的限制，我们只需跳到对应的节点上，满足限制的范围就是它的子树了。
强制在线查第K大，用DFS序+主席树维护。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 17//1N
const int N=2e5+5,M=5e5+5;

int cnt,H[N>>1],ref[N>>1],root[N],anc[N],fa[N][18],val[N],lson[N],rson[N],sz[N],lecnt[N],Index,dfn[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int fr,to,val;
	bool operator <(const Edge &x)const{
		return val<x.val;
	}
}e[M];
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define S N*20//2n!
	int tot,son[S][2],sz[S];
	#undef S
	void Insert(int x,int &y,int l,int r,int p)
	{
		sz[y=++tot]=sz[x]+1;
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) son[y][1]=rs, Insert(ls,son[y][0],l,m,p);
		else son[y][0]=ls, Insert(rs,son[y][1],m+1,r,p);
	}
	int Query(int x,int y,int l,int r,int k)
	{
		if(l==r) return l;//ref[l]
		int delta=sz[son[y][0]]-sz[ls];
		if(k<=delta) return Query(ls,son[y][0],l,l+r>>1,k);
		else return Query(rs,son[y][1],(l+r>>1)+1,r,k-delta);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
int Find(int x)
{
	return x==anc[x]?x:anc[x]=Find(anc[x]);
}
int Kruskal(int n,int m)
{
	for(int i=1; i<=n; ++i) anc[i]=i;
	for(int i=1; i<=m; ++i) e[i]=(Edge){read(),read(),read()};
	std::sort(e+1,e+1+m);
	int tot=n;
	for(int i=1,k=1,r1,r2; i<=m; ++i)
	{
		if((r1=Find(e[i].fr))==(r2=Find(e[i].to))) continue;
		fa[r1][0]=fa[r2][0]=anc[r1]=anc[r2]=++tot, fa[tot][0]=anc[tot]=tot;//初始化!
		lson[tot]=r1, rson[tot]=r2, val[tot]=e[i].val;
		if(++k==n) break;
	}
	return tot;
}
void Init_ST(int n)
{
	for(int i=1; i<=Bit; ++i)
		for(int x=1; x<=n; ++x)
			fa[x][i]=fa[fa[x][i-1]][i-1];
}
void DFS(int x)
{
	dfn[x]=++Index, root[Index]=root[Index-1], sz[x]=1;
	if(!lson[x]) lecnt[x]=1, T.Insert(root[Index-1],root[Index],1,cnt,H[x]);
	else DFS(lson[x]), DFS(rson[x]), sz[x]+=sz[lson[x]]+sz[rson[x]], lecnt[x]=lecnt[lson[x]]+lecnt[rson[x]];
}
inline int Jump(int x,int v)
{
	for(int i=Bit; ~i; --i)
		if(val[fa[x][i]]<=v) x=fa[x][i];
	return x;
}

int main()
{
	int n=read(),m=read(),Q=read();
	for(int i=1; i<=n; ++i) ref[i]=H[i]=read();
	std::sort(ref+1,ref+1+n); cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) H[i]=Find(H[i],cnt);
	n=Kruskal(n,m), Init_ST(n), DFS(n);
//	val[0]=2e9;
	for(int x,lim,k,p,ans=-1; Q--; )
	{
		if(~ans) x=read()^ans,lim=read()^ans,k=read()^ans;
		else x=read(),lim=read(),k=read();
		p=Jump(x,lim);
		if(lecnt[p]<k) printf("%d\n",ans=-1);
		else printf("%d\n",ans=ref[T.Query(root[dfn[p]],root[dfn[p]+sz[p]-1],1,cnt,lecnt[p]-k+1)]);
	}
	return 0;
}
