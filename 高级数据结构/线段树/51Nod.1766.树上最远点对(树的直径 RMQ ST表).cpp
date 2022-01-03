/*
500ms	44,948KB
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
#define BIT 17//2^{17}=131072
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
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
namespace SOL
{
	struct Node
	{
		int x,y;
	}A[N>>1][BIT];
	using PRE::Log2;
	Node Merge(const Node &a,const Node &b)
	{
		int x=a.x,y=a.y,X=b.x,Y=b.y,tx=x,ty=y,tmx=PRE::Dis(x,y),tmp;
		if((tmp=PRE::Dis(X,Y))>tmx) tmx=tmp,tx=X,ty=Y;
		if((tmp=PRE::Dis(x,X))>tmx) tmx=tmp,tx=x,ty=X;
		if((tmp=PRE::Dis(x,Y))>tmx) tmx=tmp,tx=x,ty=Y;
		if((tmp=PRE::Dis(y,X))>tmx) tmx=tmp,tx=y,ty=X;
		if((tmp=PRE::Dis(y,Y))>tmx) tmx=tmp,tx=y,ty=Y;
		return (Node){tx,ty};
	}
	inline Node Query(int l,int r)
	{
		int k=Log2[r-l+1];
		return Merge(A[l][k],A[r-(1<<k)+1][k]);
	}
	void Init_ST(const int n)
	{
		for(int i=1; i<=n; ++i) A[i][0]=(Node){i,i};
		for(int j=1; j<=Log2[n]; ++j)
			for(int t=1<<j-1,i=n-t; i; --i)
				A[i][j]=Merge(A[i][j-1],A[i+t][j-1]);
	}
	void Solve(const int n)
	{
		Init_ST(n);
		for(int Q=read(); Q--; )
		{
			int a=read(),b=read(),c=read(),d=read();
			Node X=Query(a,b),Y=Query(c,d);
			printf("%d\n",std::max(PRE::Dis(X.x,Y.x),std::max(PRE::Dis(X.x,Y.y),std::max(PRE::Dis(X.y,Y.x),PRE::Dis(X.y,Y.y)))));
		}
	}
}

int main()
{
	int n=read();
	for(int i=1; i<n; ++i) PRE::AE(read(),read(),read());
	PRE::DFS(1,1), PRE::Init_RMQ(2*n-1), SOL::Solve(n);

	return 0;
}
