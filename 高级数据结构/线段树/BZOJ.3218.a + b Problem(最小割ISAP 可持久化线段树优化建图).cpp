/*
15336kb	500ms
首先不考虑奇怪方格的限制，就是类似最大权闭合子图一样建图。
对于奇怪方格的影响，显然可以建一条边$(i\to x,p_i)$，然后由$x$向$1\sim i-1$中权值在$[l_i,r_i]$中的点所有点连$INF$边。
但是$O(n^2)$条边显然要GG。容易想到用线段树优化。
每次都是向前缀所有的点连边，所以可以离散化后用可持久化线段树连边。
另外其实也不需要拆点，直接连即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5005*18,M=(5*5005+3*N)*2,INF=1e9;//注意不要卡着开n*15以及双向边。。

int tot,src,des,Enum,H[N],nxt[M],fr[M],to[M],cap[M],pre[N],lev[N],A[N],ref[N],L[N],R[N],P[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
int Discrete(int n)
{
	static std::pair<int,int*> t[N];
	A[++n]=0, A[++n]=1e9;
	for(int i=1; i<=n; ++i) t[i]=std::make_pair(A[i],&A[i]);
	std::sort(t+1,t+1+n), ref[*t[1].second=1]=t[1].first;
	int now=1;
	for(int i=2; i<=n; ++i)
		ref[*t[i].second=t[i].first==t[i-1].first?now:++now]=t[i].first;
	return now;
}
//---Segment Tree---
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N
	int tot,son[S][2];
	#undef S
	void Insert(int &x,int y,int l,int r,int p,int id)
	{
		x=++tot;
		if(l==r)
		{
			AE(x,id,INF);
			if(y) AE(x,y,INF);//叶节点还要连上原来的！
			return;
		}
		int m=l+r>>1;
		if(p/*A[id]*/<=m) rs=son[y][1], Insert(ls,son[y][0],l,m,p,id);
		else ls=son[y][0], Insert(rs,son[y][1],m+1,r,p,id);
		if(ls) AE(x,ls,INF);
		if(rs) AE(x,rs,INF);
	}
	void Link(int l,int r,int x,int L,int R,int p)
	{
		if(!x) return;
		if(L<=l && r<=R) {AE(p,x,INF); return;}
		int m=l+r>>1;
		if(L<=m) Link(lson,L,R,p);
		if(m<R) Link(rson,L,R,p);
	}
}T;
//---ISAP---
bool BFS()
{
	static int q[N];
	for(int i=0; i<=tot; ++i) lev[i]=tot+1;
	int h=0,t=1; q[0]=des, lev[des]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==tot+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[0]<=tot;
}
inline int Augment()
{
	int mn=INF;
	for(int i=des; i; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	static int cur[N],num[N];
	if(!BFS()) return 0;
	for(int i=0; i<=tot; ++i) cur[i]=H[i], ++num[lev[i]];
	int x=0,res=0;
	while(lev[0]<=tot)
	{
		if(x==des) x=0, res+=Augment();
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=tot;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x) x=fr[pre[x]];
		}
	}
	return res;
}
//---Main---
int main()
{
	int n=read(),sum=0; des=n+1; Enum=1;
	for(int i=1,b,w; i<=n; ++i)
	{
		A[i]=read(),sum+=b=read(),sum+=w=read(),L[i]=read(),R[i]=read(),P[i]=read();
		AE(0,i,b), AE(i,des,w);
	}
	int cnt=Discrete(n); T.tot=n+1;
	for(int i=1,root=0; i<=n; ++i)
	{
		AE(i,++T.tot,P[i]);
		int l=std::lower_bound(ref+1,ref+1+cnt,L[i])-ref, r=std::upper_bound(ref+1,ref+1+cnt,R[i])-ref-1;
		if(l<=r) T.Link(1,cnt,root,l,r,T.tot);
		T.Insert(root,root,1,cnt,A[i],i);
	}
	tot=T.tot;
	printf("%d\n",sum-ISAP());

	return 0;
}
