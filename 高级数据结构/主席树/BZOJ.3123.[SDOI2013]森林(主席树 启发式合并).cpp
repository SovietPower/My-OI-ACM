/*
481804kb	8920ms
查树上第k小可以用主席树，但是合并。。~~(LCT再维护一个值的Splay行不行。。更改fa,son就Delete,Insert...作死的节奏)~~
合并两棵树我们可以用启发式合并，logn是可以的。
合并时还需要动态维护并上去的子树的LCA，所以用ST表求LCA，每次DFS一个点更新ST表即可。
合并时建主席树和之前DFS建树时是一样的，直接由父节点的root再加上A[x]。但这样每次合并一个点需要新开一个节点。。
合并一棵子树，这棵子树某些点的dep[x]可能会变小，于是fa[x][..]应变为0，但如果在循环里写 `&&(1<<i)<=dep[x]` 这个dep[x]是更新后的，fa[x][..]不会被更新成0，还是以前的fa[x][..]，于是就挂了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=8e4+5,B=16;

int n,m,Fa[N],root[N],cnt,ref[N],A[N],dep[N],fa[N][17],sz[N],Enum,H[N],to[N<<1],nxt[N<<1];
struct Seg_Tree
{
	#define lson son[x][0]
	#define rson son[x][1]

	int tot,sum[N*500],son[N*500][2];//sum[N*18],son[N*18][2];
	void Insert(int x,int &y,int l,int r,int p)
	{
		sum[y=++tot]=sum[x]+1;
		if(l<r){
			int m=l+r>>1;
			if(p<=m) son[y][1]=rson,Insert(lson,son[y][0],l,m,p);
			else son[y][0]=lson,Insert(rson,son[y][1],m+1,r,p);
		}
	}
	int Query(int x,int y,int lca,int falca,int l,int r,int k)
	{
		if(l==r) return l;
		int delta=sum[lson]+sum[son[y][0]]-sum[son[lca][0]]-sum[son[falca][0]];
		if(delta>=k) return Query(lson,son[y][0],son[lca][0],son[falca][0],l,l+r>>1,k);
		return Query(rson,son[y][1],son[lca][1],son[falca][1],(l+r>>1)+1,r,k-delta);
	}
}t;

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
int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
void Discrete()
{
	std::sort(ref+1,ref+1+n);
	cnt=1;
	for(int i=2; i<=n; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i]);
}
void pre_DFS(int x,int anc)
{
	t.Insert(root[fa[x][0]],root[x],1,cnt,A[x]), Fa[x]=anc, ++sz[anc];
	for(int i=1; i<=B&&(1<<i)<=dep[x]; ++i)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x][0])
			dep[v]=dep[x]+1, fa[v][0]=x, pre_DFS(v,anc);//, sz[x]+=sz[v];
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y]) std::swap(x,y);
	int t=dep[x]-dep[y];
	for(int i=B; i>=0; --i)
//		if(dep[fa[x][i]]>=dep[x]) x=fa[x][i];
		if(t&(1<<i)) x=fa[x][i];
	if(x==y) return x;
	for(int i=B; i>=0; --i)
		if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
void DFS(int x)
{
	t.Insert(root[fa[x][0]],root[x],1,cnt,A[x]);
	for(int i=1; i<=B/*&&(1<<i)<=dep[x]*/; ++i)//这个不能写! 
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x][0])
			dep[v]=dep[x]+1, fa[v][0]=x, DFS(v);
}
int Get_fa(int x){
	return x==Fa[x]?x:Fa[x]=Get_fa(Fa[x]);
}
void Union(int x,int y)
{
	int r1=Get_fa(x),r2=Get_fa(y);
	if(sz[r1]>sz[r2]) std::swap(x,y),std::swap(r1,r2);
	Fa[r1]=r2, sz[r2]+=sz[r1];
	fa[x][0]=y, dep[x]=dep[y]+1, DFS(x);
}

int main()
{
//	freopen("forest.in","r",stdin);
//	freopen("forest.out","w",stdout);

//	int size = 256 << 20; // 256MB  
//	char *p = (char*)malloc(size) + size;  
//	__asm__("movl %0, %%esp\n" :: "r"(p));

	int test=read(),T;
	n=read(),m=read(),T=read();
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	Discrete();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);
	for(int i=1; i<=n; ++i) if(!dep[i]) pre_DFS(i,i);
	int ans=0,x,y,w,k; char opt[3];
	while(T--)
	{
		scanf("%s",opt), x=read()^ans, y=read()^ans;
		if(opt[0]=='Q') k=read()^ans, w=LCA(x,y),printf("%d\n",ans=ref[t.Query(root[x],root[y],root[w],root[fa[w][0]],1,cnt,k)]);
		else AddEdge(x,y), Union(x,y);
	}
	return 0;
}
