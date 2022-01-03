/*
656ms	84.03MB
$Description$
������ͨ����ͼ��$q$��ѯ�ʣ�ÿ��ѯ�ʸ���$S,T,L,R$������Ҫ��$S$�ߵ�$T$�����ڹ��������������ǡ���л�һ����̬������$S,T$����
�л���̬ǰ���㲻����$[1,L-1]$�ŵ㣻�л���̬���㲻����$[R+1,n]$�ŵ㡣���Ƿ��кϷ�$S\to T$��·����
$n,q\leq 2\times 10^5,\ m\leq 4\times 10^5$��
$Solution$
$Kruskal$�ع��������������е㰴��С����/�Ӵ�С��˳�����μ�����Щ��ıߣ������ǿ��Եõ����������������ⲻһ�����������Ȩֵ�ڵ��ϣ�����Ҫ�½��ڵ㣩��
����ѯ��$(S,T,L,R)$�����Ա����ҳ�$S,T$�������Ŀ�����������ߡ�
��ôֻ��Ҫ�ж����������Ƿ��н��Ϳ����ǡ�
ע�⵽������DFS���������ģ����ǿ����ڵ�һ��������ĳ�����ݽṹ�ϣ���ڶ���������DFS�����䡣����ϯ���Ϳ����ˣ���ϯ�����±���ÿ�����ڵڶ������ϵ�DFS���жϵ�һ�������ڵڶ���������DFS���������Ƿ���ֵ���ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BIT 17
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,M=8e5+5;

int n,root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Graph
{
	int Enum,H[N],nxt[M],to[M];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
}G;
struct Tree
{
	int fg,fa[N][BIT+1],F[N],H[N],nxt[N],L[N],R[N],Index;
	int Find(int x)
	{
		return x==F[x]?x:F[x]=Find(F[x]);
	}
	inline void AE(int u,int v)
	{
		nxt[v]=H[u], H[u]=v;
	}
	inline int Jump(int x,int k)
	{
		if(fg)
		{
			for(int i=BIT; ~i; --i)
				if(fa[x][i]&&fa[x][i]<=k) x=fa[x][i];
		}
		else
		{
			for(int i=BIT; ~i; --i)
				if(fa[x][i]>=k) x=fa[x][i];
		}
		return x;
	}
	void DFS(int x,int dep)
	{
		L[x]=++Index;
		for(int i=1; 1<<i<=dep; ++i) fa[x][i]=fa[fa[x][i-1]][i-1];
		for(int v=H[x]; v; v=nxt[v]) fa[v][0]=x, DFS(v,dep+1);
		R[x]=Index;
	}
	void Build(const int n)
	{
		for(int i=1; i<=n; ++i) F[i]=i;
		if(fg)
		{
			for(int x=1,k=1; x<=n; ++x)
				for(int i=G.H[x],v; i; i=G.nxt[i])
					if((v=G.to[i])<x)
					{
						int r1=Find(x),r2=Find(v);//r1==x
						if(r1!=r2)
						{
							F[r2]=r1, AE(r1,r2);
							if(++k==n) break;
						}
					}
		}
		else
		{
			for(int x=n,k=1; x; --x)
				for(int i=G.H[x],v; i; i=G.nxt[i])
					if((v=G.to[i])>x)
					{
						int r1=Find(x),r2=Find(v);
						if(r1!=r2)
						{
							F[r2]=r1, AE(r1,r2);
							if(++k==n) break;
						}
					}
		}
		DFS(fg?n:1,0);
	}
}T1,T2;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,son[y][0],l,m
	#define rson rs,son[y][1],m+1,r
	#define S N*19
	int tot,sz[S],son[S][2];
	#undef S
	void Modify(int &x,int y,int l,int r,int p)
	{
		sz[x=++tot]=sz[y]+1;
		if(l==r) return;
		int m=l+r>>1;
		p<=m?(rs=son[y][1],Modify(lson,p)):(ls=son[y][0],Modify(rson,p));
	}
	int Query(int x,int y,int l,int r,int L,int R)//y-x
	{
		if(sz[y]-sz[x]<=0) return 0;
		if(L<=l && r<=R) return 1;
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)||Query(rson,L,R);
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
void DFS(int x)
{
	static int Index=0;
	++Index, T.Modify(root[Index],root[Index-1],1,n,T2.L[x]);
	for(int v=T1.H[x]; v; v=T1.nxt[v]) DFS(v);
}

int main()
{
	int n=read(),m=read(),Q=read(); ::n=n;
	for(int i=1; i<=m; ++i) G.AE(read()+1,read()+1);
	T1.Build(n), T2.fg=1, T2.Build(n), DFS(1);
	for(int s,t; Q--; )
		s=read()+1,t=read()+1,s=T1.Jump(s,read()+1),t=T2.Jump(t,read()+1),
		putchar(T.Query(root[T1.L[s]-1],root[T1.R[s]],1,n,T2.L[t],T2.R[t])?'1':'0'), putchar('\n');

	return 0;
}
