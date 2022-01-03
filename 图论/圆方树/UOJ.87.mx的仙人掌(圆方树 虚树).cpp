/*
本代码10分(感觉速度还行。。)。
建圆方树，预处理一些东西。对询问建虚树。
对于虚树上的圆点直接做；对于方点特判，枚举其所有儿子，如果子节点不在该方点代表的环中，跳到那个点并更新其val，加入B数组；对于环中的点直接加入B数组。
然后像BZOJ2125一样更新环上的。懒得写拆环的单调队列了，直接用min(abs,len-abs)。
UOJ特么的数据有毒啊。调不出来了，AC的代码一个比一个码风奇特，还有的贼长。。先不调了。
一上午+半下午了。。从注释的代码可以看出调的过程多么鬼畜。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=(3e5+5)*2,INF=1e9;

int n,m,Q,K,A[N],B[N],tot,D[N],fat[N][20],dfn[N],low[N],Index,tp[N],dep[N],fa[N],son[N],sz[N],sk[N],top,q[N];
LL dis[N],cdis[N],length[N],f[N],Ans,val[N],len[N][20];
bool tag[N],vis[N];
struct Graph
{
	int Enum,H[N],nxt[N<<1],to[N<<1];//边数：仙人掌：2*2n 圆方树：1*2n 虚树：1*2K 
	LL len[N<<1];
	inline void Init(){
		Enum=0, memset(H,0,sizeof H);
	}
	inline void Add_direct(int u,int v,LL w)
	{
//		printf("Add_direct:%d->%d:",u,v);
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		if(~w) len[Enum]=w;//,printf("%I64d\n",w);
		else len[Enum]=dis[v]-dis[u];//,printf("%I64d\n",len[Enum]);
	}
	inline void AddEdge(int u,int v,int w)
	{
		to[++Enum]=v, nxt[Enum]=H[u], len[Enum]=w, H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], len[Enum]=w, H[v]=Enum;
	}
}T,G;

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
void Build(int u,int v,int w)
{
//	printf("Build:%d->...->%d\n",v,u);
	LL len=w;
	for(int x=v; x!=u; x=fa[x]) cdis[x]=len, len+=D[x];
	length[++tot]=len, T.Add_direct(u,tot,0);
	for(int x=v; x!=u; x=fa[x]) T.Add_direct(tot,x,std::min(cdis[x],len-cdis[x]));
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++Index;
	for(int v,i=G.H[x]; i; i=G.nxt[i])
		if(!dfn[v=G.to[i]]) D[v]=std::min((LL)D[v],G.len[i]);
	for(int v,i=G.H[x]; i; i=G.nxt[i])
		if((v=G.to[i])!=fa[x])
		{
			if(!dfn[v]) fa[v]=x, Tarjan(v), low[x]=std::min(low[x],low[v]);
			else low[x]=std::min(low[x],dfn[v]);
			if(low[v]>dfn[x]&&!vis[v]) T.Add_direct(x,v,D[v]), vis[v]=1;
		}
	for(int v,i=G.H[x]; i; i=G.nxt[i])
		if(fa[v=G.to[i]]!=x&&dfn[v]>dfn[x]) Build(x,v,G.len[i]);
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=T.H[x]; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x])//
		{
			v=T.to[i];
			fa[v]=fat[v][0]=x, len[v][0]=T.len[i], dep[v]=dep[x]+1, dis[v]=dis[x]+T.len[i], DFS1(v), sz[x]+=sz[v];
			if(mx<sz[v]) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int _tp)
{
	dfn[x]=++Index, tp[x]=_tp;
	if(son[x]){
		DFS2(son[x],_tp);
		for(int i=T.H[x]; i; i=T.nxt[i])
//			if(T.to[i]!=son[x]) DFS2(T.to[i],T.to[i]);
			if(T.to[i]!=fa[x]&&T.to[i]!=son[x]) DFS2(T.to[i],T.to[i]);
	}
}
void Init_ST()
{
	for(int x=1; x<=tot; ++x)
		for(int j=1; j<20; ++j)
			fat[x][j]=fat[fat[x][j-1]][j-1], len[x][j]=len[x][j-1]+len[fat[x][j-1]][j-1];
}
int LCA(int u,int v)//既然要用倍增了也许可以改成倍增 
{
	while(tp[u]!=tp[v]) dep[tp[u]]>dep[tp[v]]?u=fa[tp[u]]:v=fa[tp[v]];
	return dep[u]>dep[v]?v:u;
}
void Insert(int p)
{
	if(top==1) {sk[++top]=p; return;}
	int lca=LCA(sk[top],p);
	while(dfn[sk[top-1]]>=dfn[lca]) G.Add_direct(sk[top],sk[top--],-1);
	if(lca!=sk[top] && dfn[sk[top-1]]<dfn[lca]) G.Add_direct(lca,sk[top],-1), sk[top]=lca;
	sk[++top]=p;
}
inline LL Cir_dis(int u,int v,int cir){
	return std::min(std::abs(cdis[u]-cdis[v]),length[cir]-std::abs(cdis[u]-cdis[v]));
}
inline LL Dis(int u,int v,int cir){
	return val[u]+Cir_dis(u,v,cir);
}
int Jump(int x,LL d)
{
	LL res=0;
//	printf("Jump:%d %I64d:",x,d);
	for(int i=19; ~i; --i)
		if(dis[fat[x][i]]>=d) res+=len[x][i], x=fat[x][i];
//	printf("%d %I64d\n",x,res);
	return val[x]=std::max(val[x],res), x;
}
void Solve(int x)//Square Point
{
//	printf("\nSolve:%d\n",x);
	int cnt=0;
//	if(tag[fa[x]]) B[cnt=1]=fa[x];//
	for(int v,i=G.H[x]; i; i=G.nxt[i])
		if(fa[v=G.to[i]]==x||fa[x]==v) val[B[++cnt]=v]=f[v];
		else B[++cnt]=Jump(v,dis[x]+1);
	int h=1,t=0;
	for(int v,i=1; i<=cnt; ++i)
	{
		if(h>t) {q[++t]=B[i]; continue;}
		v=B[i];
		while(h<t && Dis(q[h],v,x)<Dis(q[h+1],v,x)) ++h;
//		printf("q[h]:%d v:%d Dis:%I64d\n",q[h],v,Dis(q[h],v,x));
		Ans=std::max(Ans,Dis(q[h],v,x)+val[v]);
		while(h<t && Dis(q[t],v,x)<val[v]) --t;
		q[++t]=v;
	}
	for(int v,i=1; i<=cnt; ++i)
		f[x]=std::max(f[x],val[B[i]]+Cir_dis(fa[x],B[i],x));
	for(int i=1; i<=cnt; ++i) val[B[i]]=0;
//	putchar('\n');
}
void DP(int x)//G:Virtual Tree
{
	f[x]=tag[x]?0:-INF;
//	printf("Now:%d\n",x);
	if(x<=n){//Round Point
		for(int v,i=G.H[x]; i; i=G.nxt[i])
			DP(v=G.to[i]), Ans=std::max(Ans,f[x]+f[v]+G.len[i]), f[x]=std::max(f[x],f[v]+G.len[i]);
//			printf("%d->%d:end Ans:%I64d f[x]:%I64d\n",x,v,Ans,f[x]);
	}
	else{
		for(int i=G.H[x]; i; i=G.nxt[i]) DP(G.to[i]);
		Solve(x);
	}
//	printf("%d:tag:%d f:%I64d Ans:%I64d\n",x,tag[x],f[x],Ans);
	G.H[x]=tag[x]=0;
}

int main()
{
//	freopen("1.in","r",stdin);
	tot=n=read(),m=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),G.AddEdge(u,v,read());
//	memset(D,0x7f,sizeof D);//0x7fffffff
	for(int i=1; i<=n; ++i) D[i]=0x7fffffff;
	Tarjan(1), fa[1]=Index=0, DFS1(1), DFS2(1,1), Init_ST(), G.Init();
	Q=read();//puts("\ndis:");
//	for(int i=1; i<=tot; ++i) printf("%d:%I64d\n",i,dis[i]);putchar('\n');
	while(Q--)
	{
		K=read(); for(int i=1; i<=K; ++i) tag[A[i]=read()]=1;
		std::sort(A+1,A+1+K);
		int k=K; K=1;//unique //有重这有毒啊 
		for(int i=2; i<=k; ++i) if(A[i]!=A[i-1]) A[++K]=A[i];

		std::sort(A+1,A+1+K,cmp_dfn);
		sk[top=1]=1;
		if(A[1]==1) for(int i=2; i<=K; ++i) Insert(A[i]);
		else for(int i=1; i<=K; ++i) Insert(A[i]);
		while(--top) G.Add_direct(sk[top],sk[top+1],-1);

		Ans=0, DP(1), G.Enum=0;
		printf("%lld\n",Ans);
	}
	return 0;
}
