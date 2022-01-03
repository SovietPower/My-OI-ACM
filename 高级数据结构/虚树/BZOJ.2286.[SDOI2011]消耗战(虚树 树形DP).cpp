/*
17428kb	3264ms(fread很有用啊)
树形DP，对于每棵子树要么逐个删除其中要删除的边，要么直接断连向父节点的边。
如果当前点需要删除，那么直接断不需要再管子树。
复杂度O(m*n)。
对于两个要删除的点 u,v 之间的链，若链上没有其它需要删的点，则只需保留链上的最小边权即可。
把有用的点按DFS序排序，依次构建出一棵虚树，可以在上面进行同样的DP。
卡常技巧：
本题建虚树时，对于某要删除点的子树中的点，都可以忽略，即Insert时若LCA(sk[top],now)=sk[top]，可直接忽略now的入栈。（因为刚开始栈顶一定是个要删的点）
这样就可以用表头是否为空来判断是否要删除该点了，不需要标记。
本题建虚树时不需要边权，直接用点权即可，权值为到根路径的最小边权。
还因为是棵树，那么连边时用链表即可，不需要用边表。(然并软。。还是用链表吧)
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=250005,M=N<<1;

int n,m,K,A[N],Enum,H[N],nxt[M],to[M],len[M],val[N],dfn[N],Index,fa[N],tp[N],sz[N],son[N],dep[N],top,sk[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], len[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], len[Enum]=w, H[v]=Enum;
}
inline void Add_direct(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
inline bool cmp_dfn(const int &a,const int &b){
	return dfn[a]<dfn[b];
}
void DFS1(int x,int mn)
{
	int mx=0; sz[x]=1, val[x]=mn;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v,std::min(mn,len[i])), sz[x]+=sz[v];
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
	return dep[u]<dep[v]?u:v;
}
void Insert(int p)
{
	if(top==1) {sk[++top]=p; return;}//if(sk[top]==1)
	int lca=LCA(sk[top],p);
	if(lca==sk[top]) return;
//	int las=sk[top];
//	while(lca!=las)
//	{
//		if(dfn[sk[--top]]<dfn[lca])
//		{
//			Add_direct(lca,las), sk[++top]=lca;
//			break;
//		}
//		Add_direct(sk[top],las), las=sk[top];
//	}
	while(dfn[sk[top-1]]>=dfn[lca]) Add_direct(sk[top],sk[top--]);//参数调用顺序...
	if(lca!=sk[top] && dfn[sk[top-1]]<dfn[lca]) Add_direct(lca,sk[top]), sk[top]=lca;//++top, --top
	sk[++top]=p;
}
LL DP(int x)
{
	if(!H[x]) return val[x];
	LL sum=0;
	for(int i=H[x]; i; i=nxt[i]) sum+=DP(to[i]);
	H[x]=0;
	return std::min((LL)val[x],sum);
}

int main()
{
	n=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v,read());
	DFS1(1,0x7fffffff), DFS2(1,1), Enum=0, memset(H,0,sizeof H);
	m=read();
	while(m--)
	{
		K=read();
		for(int i=1; i<=K; ++i) A[i]=read();
		std::sort(A+1,A+1+K,cmp_dfn);
		sk[top=1]=1;
		for(int i=1; i<=K; ++i) Insert(A[i]);
		while(--top) Add_direct(sk[top],sk[top+1]);

		LL res=0;
		for(int i=H[1]; i; i=nxt[i]) res+=DP(to[i]);//对1要单独处理，要不应把val[1]设为很大的longlong 
		H[1]=0;
		printf("%lld\n",res);
		Enum=0; //for(int i=1; i<=K; ++i) H[A[i]]=0;
	}
	return 0;
}
