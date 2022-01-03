/*
671ms	45,244KB
$Description$
给定一棵树。每次询问给定$a\sim b,c\sim d$两个下标区间，从这两个区间中各取一个点，使得这两个点距离最远。输出最远距离。
$n,q\leq10^5$。
$Solution$
一个集合直径的两端点，在被划分为两个集合后一定是两个集合直径的四个端点中的两个。
即假设将$S$分为两个集合后，另外两个集合的直径的两端点分别为a,b和c,d，那么$S$集合的直径的两端点一定是a,b,c,d中的两个。
证明类似树的直径。
所以信息可以合并，所以就可以线段树啦。而且没有修改，ST表就够啦。
原来是两个区间各选一点。。=-=
写namespace不想改了...有点丑不要介意。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BIT 17
#define gc() getchar()
#define MAXIN 100000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;//2n

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace PRE
{
	int Enum,H[N>>1],nxt[N],to[N],len[N],dis[N>>1],pos[N>>1],Log2[N],st[N][BIT+1];
	inline void AE(int w,int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
	}
	inline int LCA_dis(int l,int r)
	{
		if(l>r) std::swap(l,r);
		int k=Log2[r-l+1];
		return std::min(st[l][k],st[r-(1<<k)+1][k])<<1;
//		return dis[ref[std::min(st[l][k],st[r-(1<<k)+1][k])]]<<1;
	}
	inline int Dis(int x,int y)
	{
		return dis[x]+dis[y]-LCA_dis(pos[x],pos[y]);
	}
	void DFS(int x,int fa)
	{
		static int tot=0;
		st[pos[x]=++tot][0]=dis[x];//边权为正的话可以直接用dis[x]
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa) dis[v]=dis[x]+len[i], DFS(v,x), st[++tot][0]=dis[x];
	}
	void Init_RMQ(const int n)
	{
		for(int i=2; i<=n; ++i) Log2[i]=Log2[i>>1]+1;
		for(int j=1; j<=Log2[n]; ++j)
			for(int t=1<<j-1,i=n-t; i; --i)
				st[i][j]=std::min(st[i][j-1],st[i+t][j-1]);
	}
}
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,rt<<1
	#define rson m+1,r,rt<<1|1
	#define S N<<1//2n
	int n,ansx,ansy,ansmx,X[S],Y[S],mxds[S];
	#undef S
	void Merge(int &x,int &y,int &mx,int X,int Y,int Mx)
	{
		int tmp,tx=x,ty=y,tmx=mx;
		if(Mx>tmx) tmx=Mx,tx=X,ty=Y;
		if((tmp=PRE::Dis(x,X))>tmx) tmx=tmp,tx=x,ty=X;
		if((tmp=PRE::Dis(x,Y))>tmx) tmx=tmp,tx=x,ty=Y;
		if((tmp=PRE::Dis(y,X))>tmx) tmx=tmp,tx=y,ty=X;
		if((tmp=PRE::Dis(y,Y))>tmx) tmx=tmp,tx=y,ty=Y;
		x=tx, y=ty, mx=tmx;
	}
	inline void Update(int rt)
	{
		int l=ls,r=rs;
		Merge(X[rt]=X[l],Y[rt]=Y[l],mxds[rt]=mxds[l],X[r],Y[r],mxds[r]);
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {X[rt]=Y[rt]=l; return;}
		int m=l+r>>1; Build(lson), Build(rson), Update(rt);
	}
	void Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Merge(ansx,ansy,ansmx,X[rt],Y[rt],mxds[rt]); return;}
		int m=l+r>>1;
		if(L<=m) Query(lson,L,R);
		if(m<R) Query(rson,L,R);
	}
	void Solve()
	{
		int a=read(),b=read(),c=read(),d=read();
		ansx=a, ansy=a, ansmx=0;
		Query(1,n,1,a,b);
		int x1=ansx,y1=ansy; ansx=c, ansy=c, ansmx=0;
		Query(1,n,1,c,d);
		int x2=ansx,y2=ansy;
		printf("%d\n",std::max(PRE::Dis(x1,x2),std::max(PRE::Dis(x1,y2),std::max(PRE::Dis(y1,x2),PRE::Dis(y1,y2)))));
	}
}T;

int main()
{
	int n=read();
	for(int i=1; i<n; ++i) PRE::AE(read(),read(),read());
	PRE::DFS(1,1), PRE::Init_RMQ(2*n-1);
	T.n=n, T.Build(1,n,1);
	for(int Q=read(); Q--; T.Solve());

	return 0;
}
