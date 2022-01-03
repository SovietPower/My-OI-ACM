/*
$Description$
给定一棵基环树，每条边有一个颜色$c$。$m$次修改一条边的颜色，每次修改输出当前的边连通块个数。
边连通定义为两条边颜色相同即为连通。
$T\leq 100,\ n,m\leq 2*10^5,\ \sigma n,m\leq 10^6$。
$Solution$
对于树的情况很简单，只需要随便判一下就OK了。
树+一个环的情况，设环为$u->w->v->u$，其中$LCA(u,v)=w$。
若修改边不在环上和树一样；否则要判断几种情况。
可以发现我们只要能维护查询$u->w->v$整条路径的边是否同色就可以了。
因为没有修改不需要树剖（写了但是HDU栈溢出。。扩栈也没用）（可是网上的都有DFS啊/whl/kk），用multiset维护环上的边就ok。
不想写了，用set感觉不难写啊，懒得看网上那么长的代码。。
*/
#pragma comment(linker, "/STACK:1024000000,1024000000")
//#include <bits/stdc++.h>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define gc() getchar()
typedef long long LL;
const int N=2e5+25;

int Ans,Index,Tag,Enum,col[N],H[N],nxt[N<<1],to[N<<1],cole[N<<1],son[N],top[N],dep[N],fa[N],id[N],sz[N];
bool vis[N];
std::unordered_map<int,int> mp[N];
struct Segment_Tree
{
	#define S N<<2
	int cov[S],A[N];
	#undef S
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	inline void Update(int rt)
	{
		if(!cov[ls]||!cov[rs]) cov[rt]=0;
		else cov[rt]=(cov[ls]==cov[rs])*cov[ls];
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {cov[rt]=A[l]; return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int p)
	{
		if(l==r) {cov[rt]=A[p]; return;}
		int m=l+r>>1;
		p<=m ? Modify(lson,p) : Modify(rson,p);
		Update(rt);
	}
	int Query(int l,int r,int rt,int id,int R)
	{
		if(id<=l && r<=R) return cov[rt];
		int m=l+r>>1;
		if(id<=m)
		{
			int lv=Query(lson,id,R);
			if(m<R)
			{
				int rv=Query(rson,id,R);
				return lv&&rv?(lv==rv)*lv:0;
			}
			return lv;
		}
		return Query(rson,id,R);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int c)
{
	++mp[u][c], ++mp[v][c];
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cole[Enum]=c;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cole[Enum]=c;
}
void DFS1(int x)
{
	int mx=0; vis[x]=1, sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			if(vis[v]) Tag=i;
			else
			{
				if(x!=1 && cole[i]==col[x]) --Ans;
				col[v]=cole[i], fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
			}
		}
}
void DFS2(int x,int tp)
{
	vis[x]=1;
	top[x]=tp, T.A[id[x]=++Index]=col[x];
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x] && v!=son[x] && i!=Tag && (i^1)!=Tag && !vis[v])
				DFS2(v,v);
	}
}
int Query(int u,int v,int n)
{
	int ans=-1;
	while(top[u]!=top[v]&&ans)
	{
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		int t=T.Query(2,n,1,id[top[u]],id[u]), u=fa[top[u]];
		if(ans==-1) ans=t;
		else if(ans&&t) ans=(ans==t)*t;
		else ans=0;
	}
	if(u==v) return ans;
	if(dep[u]>dep[v]) std::swap(u,v);
	int t=T.Query(2,n,1,son[id[u]],id[v]);
	if(ans==-1) ans=t;
	else if(ans&&t) ans=(ans==t)*t;
	else ans=0;
	return ans;
}
int Check(int A,int B,int C,int n)
{
	int x=mp[A][C],y=mp[B][C];
	if(!x && !y) return 0;
	int t=Query(A,B,n);
	if(t==C) return 1;
	if(x && y) return 2;
	return 1;
}

int main()
{
	static bool Tmp[N];

//    int size = 256 << 20; // 256MB  
//    char *p = (char*)malloc(size) + size;  
//    __asm__("movl %0, %%esp\n" :: "r"(p));

	for(int Ts=1,TS=read(); Ts<=TS; ++Ts)
	{
		printf("Case #%d:\n",Ts);
		int n=read(),Q=read();
		Enum=1, memset(H,0,n+2<<2), memset(vis,0,n+2), memset(Tmp,0,n+2);
		for(int i=1,u,v; i<=n; ++i) u=read(),v=read(),AE(u,v,read());
		Ans=n, Tag=0, Index=0, dep[1]=1, fa[1]=0, DFS1(1);
		memset(vis,0,n+2);
		DFS2(1,1);
		int A=to[Tag],B=to[Tag^1],C=cole[Tag];
		if(A>B) std::swap(A,B);
		--mp[A][C], --mp[B][C];
		for(int i=H[1],v; i; i=nxt[i])
			if(i!=Tag && (i^1)!=Tag)
				if(Tmp[col[v]]) --Ans;
				else Tmp[col[v]]=1;

		#define S 2,n,1
		T.Build(S);
		int las=Check(A,B,C,n);
		Ans-=las;
//		printf("Init Ans:%d\n",Ans);
		for(int i=1; i<=Q; ++i)
		{
			int x=read(),y=read(),c=read();
			if(x>y) std::swap(x,y);
			if(x==A && y==B)
				Ans+=las, las=Check(A,B,C=c,n), Ans-=las;
			else
			{
				if(dep[x]>dep[y]) std::swap(x,y);
				int t=col[y];
				if(mp[x][t]>1) ++Ans;
				if(mp[y][t]>1) ++Ans;
				--mp[x][t], --mp[y][t];
				col[y]=c, ++mp[x][c], ++mp[y][c];
				if(mp[x][c]>1) --Ans;
				if(mp[y][c]>1) --Ans;
				T.A[id[y]]=c, T.Modify(S,id[y]);
				Ans+=las, las=Check(A,B,C,n), Ans-=las;
			}
			printf("%d\n",Ans);
		}
		for(int i=1; i<=n; ++i) mp[i].clear();
	} 

	return 0;
}
