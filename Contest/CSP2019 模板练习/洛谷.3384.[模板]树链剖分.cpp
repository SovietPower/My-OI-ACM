//411ms	10.14MB
#include <cstdio>
#include <cctype>
#include <algorithm>
#define MOD(x) x>=mod&&(x-=mod)
#define ADD(x,v) (x+=v)>=mod&&(x-=mod)
#define gc() getchar()
#define MAXIN 200000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int n,mod,val[N],Enum,H[N],nxt[N<<1],to[N<<1],sz[N],son[N],top[N],fa[N],dep[N],dfn[N],ref[N];
//char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int t[S],tag[S];
	#undef S

	#define Add(rt,v,l) t[rt]+=1ll*(l)*v%mod, MOD(t[rt]), ADD(tag[rt],v)
	#define Update(rt) t[rt]=t[ls]+t[rs], MOD(t[rt])
	inline void PushDown(int rt,int m)
	{
		Add(ls,tag[rt],m-(m>>1)), Add(rs,tag[rt],(m>>1)), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {t[rt]=val[ref[l]]; return;}
		int m=l+r>>1; Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Add(rt,v,r-l+1); return;}
		if(tag[rt]) PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return t[rt];
		if(tag[rt]) PushDown(rt,r-l+1);
		int m=l+r>>1,res=0;
		if(L<=m) res+=Query(lson,L,R);
		if(m<R) res+=Query(rson,L,R);
		return res>=mod?res-mod:res;
	}
}T;

#define S 1,n,1
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[v]>mx&&(mx=sz[v],son[x]=v), sz[x]+=sz[v];
}
void DFS2(int x,int tp)
{
	static int Index=0;
	top[x]=tp, ref[dfn[x]=++Index]=x;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x] && v!=son[x]) DFS2(v,v);
	}
}
void ChainAdd(int w,int u,int v)
{
	while(top[u]!=top[v])
	{
		dep[top[u]]<dep[top[v]]&&(std::swap(u,v),0);
		T.Modify(S,dfn[top[u]],dfn[u],w), u=fa[top[u]];
	}
	dep[u]>dep[v]&&(std::swap(u,v),0), T.Modify(S,dfn[u],dfn[v],w);
}
int Query(int u,int v)
{
	LL res=0;
	while(top[u]!=top[v])
	{
		dep[top[u]]<dep[top[v]]&&(std::swap(u,v),0);
		res+=T.Query(S,dfn[top[u]],dfn[u]), u=fa[top[u]];
	}
	dep[u]>dep[v]&&(std::swap(u,v),0);
	return (res+T.Query(S,dfn[u],dfn[v]))%mod;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);//树剖模板需要调数据的菜鸡 
#endif
	int n=read(),m=read(),root=read(); ::n=n, mod=read();
	for(int i=1; i<=n; ++i) val[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(root), DFS2(root,root), T.Build(S);
	for(int x; m--; )
	{
		switch(read())
		{
			case 1: ChainAdd(read(),read(),read()); break;
			case 2: printf("%d\n",Query(read(),read())); break;
			case 3: x=read(), T.Modify(S,dfn[x],dfn[x]+sz[x]-1,read()); break;
			case 4: x=read(), printf("%d\n",T.Query(S,dfn[x],dfn[x]+sz[x]-1)); break;
		}
	}

	return 0;
}
