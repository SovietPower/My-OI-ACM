/*
129ms	14336KB
$Description$
����һ��$n$�����������ÿ����$i$����Բ���$g_i$������������һ������Ҫ���ѱ߳��������������ѡ�������һ���������������������ֱ�������ľ������ߣ������ظ�����ͬһ���㣩��������ܾ������ٸ��㡣
$n\leq10^5$��
$Solution$
����Ρ���ÿ����������$rt$�������$rt$��������ĳ����������Ҫ���ٳ�ʼ��������������ĳ���㵽$rt$����ʣ�¶���������Ȼ��`sort`һ�ºϲ����ɡ�ע�ⲻҪ�ϲ�����ͬһ�������ڵ�·�������������Բ�ͬ���������ֵ�����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 400000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,INF=1<<30;

int Ans,Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],A[N],Min,root,sz[N],cnt1,cnt2;
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int s,dep,bel;
	bool operator <(const Node &x)const
	{
		return s<x.s;//��s���򰡣�����ô��dep��mdzz��
	}
}f[N],g[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void FindRoot(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa) FindRoot(v,x,tot), sz[x]+=sz[v], mx=std::max(mx,sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int fa,int need,int need2,int sum,int dep,int anc)
{//need:v->x��ǰ��������ҪҪ�ж������� rest:v->x��ʣ�¶������� need2:x->v������Ҫ������ʼ���� sum:x->vһ���������� rest=A[root]+sum
	g[++cnt2]=(Node){need2,dep,anc}, sum+=A[x];
	if(A[x]>=need) f[++cnt1]=(Node){sum,dep+1,anc};
	for(int i=H[x],v,w; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa)
			w=len[i], DFS(v,x,w+std::max(0,need-A[x]),std::max(need2,w-sum),sum-w,dep+1,anc);
}
void Solve(int x)
{
	vis[x]=1, cnt1=cnt2=1, f[1]=(Node){0,1,0}, g[1]=(Node){0,0,0};
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) DFS(v,x,len[i],len[i],-len[i],1,v);
	for(int i=1,a=A[x]; i<=cnt1; ++i) f[i].s+=a;
	std::sort(f+1,f+1+cnt1), std::sort(g+1,g+1+cnt2);
	Node a=(Node){0,0,0},b=a;
	int res=0; g[cnt2+1].s=INF;
	for(int i=1,j=1; i<=cnt1; ++i)
	{
		while(g[j].s<=f[i].s)
		{
			if(g[j].dep>a.dep)
				if(g[j].bel!=a.bel) b=a, a=g[j];
				else a=g[j];
			else if(g[j].dep>b.dep && g[j].bel!=a.bel) b=g[j];
			++j;
		}
		if(f[i].bel!=a.bel) res=std::max(res,f[i].dep+a.dep);
		else res=std::max(res,f[i].dep+b.dep);
	}
	Ans=std::max(Ans,res);
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) Min=N, FindRoot(v,x,sz[v]), Solve(root);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	Ans=1, Min=N, FindRoot(1,1,n), Solve(root), printf("%d\n",Ans);

	return 0;
}
