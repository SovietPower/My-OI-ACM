/*
108172kb	2564ms(又是Rank4...)
要求的和、最大值、最小值好像都可以通过O(n)的树形DP做，总询问点数<=2n。
于是建虚树就可以了。具体DP见DP()函数，维护三个值sum[],mx[],mn[]。
sum[]要开longlong！。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5,M=N<<1,INF=5e8;

int n,Q,K,A[N],Enum,H[N],nxt[M],to[M],val[M],dep[N],tp[N],top,sk[N],dfn[N],Index,fa[N],son[N],sz[N],mn[N],mx[N],Min,Max;
LL Sum,sum[N];
bool tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool cmp_dfn(const int &a,const int &b){
	return dfn[a]<dfn[b];
}
inline void Add_direct(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=dep[v]-dep[u], H[u]=Enum;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
			if(mx<sz[v]) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int _tp)
{
	dfn[x]=++Index, tp[x]=_tp;
	if(son[x])
	{
		DFS2(son[x],_tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x]&&to[i]!=son[x]) DFS2(to[i],to[i]);
	}
}
int LCA(int u,int v)
{
	while(tp[u]!=tp[v]) dep[tp[u]]>dep[tp[v]]?u=fa[tp[u]]:v=fa[tp[v]];
	return dep[u]>dep[v]?v:u;
}
void Insert(int p)
{
	if(top==1) {sk[++top]=p; return;}
	int lca=LCA(sk[top],p);
//	if(lca==sk[top]) {sk[++top]=p; return;}
	while(dfn[sk[top-1]]>=dfn[lca]) Add_direct(sk[top],sk[top--]);
	if(lca!=sk[top] && dfn[sk[top-1]]<dfn[lca]) Add_direct(lca,sk[top]), sk[top]=lca;
	sk[++top]=p;
}
void DP(int x)
{
	sum[x]=0;
	if(tag[x]) mn[x]=0, mx[x]=0/*可以以此为一端点*/, sz[x]=1;
	else mn[x]=INF, mx[x]=-INF, sz[x]=0;
	for(int v,i=H[x]; i; i=nxt[i])
	{
		DP(v=to[i]);
		Min=std::min(Min, mn[x]+mn[v]+val[i]), mn[x]=std::min(mn[x], mn[v]+val[i]);
		Max=std::max(Max, mx[x]+mx[v]+val[i]), mx[x]=std::max(mx[x], mx[v]+val[i]);
		Sum+=1ll*sz[x]*(sum[v]+val[i]*sz[v])+1ll*sz[v]*sum[x];//之前的此时会被统计sz[v]次，v子树被统计sz[x]次  //long long!
		sum[x]+=sum[v]+val[i]*sz[v], sz[x]+=sz[v];
	}
	tag[x]=H[x]=0;
}

int main()
{
	n=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	DFS1(1), DFS2(1,1), Enum=0, memset(H,0,sizeof H);// memset(sz,0,sizeof sz);
	Q=read();
	while(Q--)
	{
		K=read();
		for(int i=1; i<=K; ++i) tag[A[i]=read()]=1;
		std::sort(A+1,A+1+K,cmp_dfn);
		sk[top=1]=1;
		if(A[1]==1) for(int i=2; i<=K; ++i) Insert(A[i]);//以1为根，注意不要加1两次。。
		else for(int i=1; i<=K; ++i) Insert(A[i]);
		while(--top) Add_direct(sk[top],sk[top+1]);//!

		Sum=0, Min=INF, Max=-INF, DP(1);
		printf("%lld %d %d\n",Sum,Min,Max);
		Enum=0;// for(int i=1; i<=K; ++i) H[A[i]]=0;
	}
	return 0;
}
