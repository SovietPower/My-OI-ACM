/*
17604kb	5528ms
$Description$
����һ������$n$����ÿ�����е�Ȩ��ÿ��ѯ��һ��·������·�������ɵ�ʹ�������$n\leq2\times10^4,q\leq2\times10^5$��
$Solution$
���Ի�����$O(\log^2)$�����ϲ���Ȼ����������·�����⣬���ǵ���Ρ�
����ÿ����$i$��� $LCA(u,v)=i$ʱ��ѯ��$(u,v)$��ֻ���������㵽����������Ի��󣬱����ϲ���
��LCA����ֱ���󡣡���Ϊ�����ʱ����̬�ڱ䡣
����Getһ���µ���η�����$q[x]$��·����$x$��������е�ѯ�ʡ�����ѯ��ʱ���ҵ���ǰ������$root$������$LCA=root$��ѯ�ʣ�����$root$��ʼDFS����һ��ÿ���������Ŀ�����������ö�����������ѯ��$q[x]$�����LCA��$root$���ѯ��������ͬһ���������Ļ��Ͱ�ѯ�ʷָ��ǿ���������
ע�������Ļ��������$root$�����ǵ�ǰ�ڵ�$x$��$x$���ܻ����ٷ��ʣ�so�ǵ����$x$��ѯ�ʡ�btw����$x$�������ǰҪ����ѯ�ʺ�����գ���Ϊ�����и�x��ѯ�ʡ�������ֱ�����ˣ� 
ע��û��ѯ��ʱ����֦��
���Ӷ�$O(60n\log n+60^2q)$��
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 60
typedef long long LL;
const int N=2e4+5,Qs=2e5+5;

int n,Q,Enum,tmp[Qs],H[N],nxt[N<<1],to[N<<1],sz[N],bel[N],X[Qs],Y[Qs],Min,root;
bool vis[N];
LL A[N],Ans[Qs];
std::vector<int> q[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Base
{
	LL b[61];
	inline void Clear() {memset(b,0,sizeof b);}
	inline void Insert(LL x)
	{
		for(int i=Bit; ~i; --i)
			if(x>>i & 1)
				if(b[i]) x^=b[i];
				else {b[i]=x; break;}
	}
	inline void Merge(const Base &x)
	{
		for(int i=Bit; ~i; --i)
			if(x.b[i]) Insert(x.b[i]);
	}
	inline LL Query()
	{
		LL ans=0;
		for(int i=Bit; ~i; --i) ans=std::max(ans,ans^b[i]);
		return ans;
	}
}base[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Get_root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=f)
		{
			Get_root(v,x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int f,int Bel)
{
	bel[x]=Bel, base[x]=base[f], base[x].Insert(A[x]);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f&&!vis[to[i]]) DFS(to[i],x,Bel);
}
void Solve(int x)
{
	if(!q[x].size()) return;//!
	Min=N, Get_root(x,x,sz[x]);
	vis[root]=1, bel[root]=root,/*!*/ base[root].Clear(), base[root].Insert(A[root]);
	for(int i=H[root]; i; i=nxt[i]) if(!vis[to[i]]) DFS(to[i],root,to[i]);
	int cnt=q[x].size();
	for(int i=0; i<=cnt; ++i) tmp[i]=q[x][i];//!
	q[x].clear();//! 
	Base b;
	for(int i=0,id; i<cnt; ++i)
		if(bel[X[id=tmp[i]]]==bel[Y[id]]) q[bel[X[id]]].push_back(id);
		else b=base[X[id]], b.Merge(base[Y[id]]), Ans[id]=b.Query();
	for(int i=H[root]; i; i=nxt[i]) if(!vis[to[i]]) Solve(to[i]);
}

int main()
{
	n=read(), Q=read();
	for(int i=1; i<=n; ++i) A[i]=readll();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	for(int i=1; i<=Q; ++i)
	{
		X[i]=read(), Y[i]=read();
		if(X[i]!=Y[i]) q[1].push_back(i);
		else Ans[i]=A[X[i]];
	}
	sz[1]=n, Solve(1);
	for(int i=1; i<=Q; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
