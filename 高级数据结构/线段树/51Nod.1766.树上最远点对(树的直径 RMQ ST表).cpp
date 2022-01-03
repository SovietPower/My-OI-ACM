/*
500ms	44,948KB
$Description$
����һ������ÿ��ѯ�ʸ���$a\sim b,c\sim d$�����±����䣬�������������и�ȡһ���㣬ʹ���������������Զ�������Զ���롣
$n,q\leq10^5$��
$Solution$
һ������ֱ�������˵㣬�ڱ�����Ϊ�������Ϻ�һ������������ֱ�����ĸ��˵��е�������
�����轫$S$��Ϊ�������Ϻ������������ϵ�ֱ�������˵�ֱ�Ϊa,b��c,d����ô$S$���ϵ�ֱ�������˵�һ����a,b,c,d�е�������
֤����������ֱ����
������Ϣ���Ժϲ������ԾͿ����߶�����������û���޸ģ�ST��͹�����
ԭ�������������ѡһ�㡣��=-=
дnamespace�������...�е��Ҫ���⡣
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
		st[pos[x]=++tot][0]=dis[x];//��ȨΪ���Ļ�����ֱ����dis[x]
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
