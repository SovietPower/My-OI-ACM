/*
648ms	31.61MB
构建完MST后，枚举非树边(u,v,w)，在树上u->v的路径中找一条权值最大的边(权为maxn)，替换掉它 
这样在 w=maxn 时显然不能满足严格次小。但是这个w可以替换掉树上严格小于maxn的次大边 
用倍增维护MST上路径的最大值、次大值，每条非树边的查询复杂度就为O(logn) 

ps:1.倍增更新次大值时，未必是从最大值转移，要先赋值较大的次大值，再与较小的那个最大值比较。
2.maxn!=w时，是可以从maxn更新的(不能更新就是上面情况啊) 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=3e5+5,D=18,MAXIN=2e6;

int n,m,F[N],Enum,H[N],to[N<<1],nxt[N<<1],val[N<<1],dep[N],fa[N][D],maxn[N][D],s_maxn[N][D];
bool ist[M];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int fr,to,val;
	bool operator <(const Edge &a)const{
		return val<a.val;
	}
}e[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge_T(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], val[Enum]=w, H[v]=Enum;
}
int Find(int x){
	return x==F[x]?x:F[x]=Find(F[x]);
}
LL Kruskal()
{
	LL res=0ll;
	std::sort(e+1,e+1+m);
	for(int i=1; i<=n; ++i) F[i]=i;
	for(int u,v,k=0,i=1; i<=m; ++i)
	{
		u=Find(e[i].fr), v=Find(e[i].to);
		if(u!=v)
		{
			ist[i]=1, F[u]=v, res+=e[i].val;
			AddEdge_T(e[i].fr,e[i].to,e[i].val);//别拿u,v建边 
			if(++k==n-1) break;
		}
	}
	return res;
}
void pre_DFS(int x)
{
	for(int i=1; i<D && (1<<i)<=dep[x]; ++i)
	{
		fa[x][i]=fa[fa[x][i-1]][i-1];
		maxn[x][i]=std::max(maxn[fa[x][i-1]][i-1],maxn[x][i-1]);
		s_maxn[x][i]=std::max(s_maxn[fa[x][i-1]][i-1],s_maxn[x][i-1]);
		if(maxn[fa[x][i-1]][i-1]>maxn[x][i-1])
			s_maxn[x][i]=std::max(s_maxn[x][i],maxn[x][i-1]);
		else if(maxn[fa[x][i-1]][i-1]<maxn[x][i-1])//不要直接else 
			s_maxn[x][i]=std::max(s_maxn[x][i],maxn[fa[x][i-1]][i-1]);
	}
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x][0])
			fa[v][0]=x, dep[v]=dep[x]+1, maxn[v][0]=val[i], pre_DFS(v);
}
//void Init()//这步先处理i！
//{
//	for(int i=1; i<D; ++i)
//		for(int x=2; x<=n; ++x)
//		{
//			fa[x][i]=fa[fa[x][i-1]][i-1];
//			maxn[x][i]=std::max(maxn[fa[x][i-1]][i-1],maxn[x][i-1]);
//			s_maxn[x][i]=std::max(s_maxn[fa[x][i-1]][i-1],s_maxn[x][i-1]);
//			if(maxn[fa[x][i-1]][i-1]>maxn[x][i-1])
//				s_maxn[x][i]=std::max(s_maxn[x][i],maxn[x][i-1]);
//			else if(maxn[fa[x][i-1]][i-1]<maxn[x][i-1])//不要直接else 
//				s_maxn[x][i]=std::max(s_maxn[x][i],maxn[fa[x][i-1]][i-1]);
//		}
//}
int Query(int u,int lca,int w)
{
	int res=0;
	for(int i=D-1; i>=0; --i)
		if(dep[fa[u][i]]>=dep[lca])
		{
			if(maxn[u][i]!=w) res=std::max(res,maxn[u][i]);
			else res=std::max(res,s_maxn[u][i]);
			u=fa[u][i];
		}
	return res;
}
int LCA(int u,int v)
{
	if(dep[u]<dep[v]) std::swap(u,v);
	int t=dep[u]-dep[v];
	for(int i=D-1; i>=0; --i)
		if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
//		if(t&(1<<i)) u=fa[u][i];
	if(u==v) return u;
	for(int i=D-1; i>=0; --i)
		if(fa[u][i]!=fa[v][i])
			u=fa[u][i], v=fa[v][i];
	return fa[u][0];
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=m; ++i) e[i].fr=read(),e[i].to=read(),e[i].val=read();
	LL tot=Kruskal(),res=e[m].val+tot;
	dep[1]=1, pre_DFS(1);//, Init();
	for(int u,v,w,lmax,rmax,i=1; i<=m; ++i)
		if(!ist[i])
		{
			u=e[i].fr, v=e[i].to, w=LCA(u,v);
			lmax=Query(u,w,e[i].val), rmax=Query(v,w,e[i].val);
			res=std::min(res,tot+e[i].val-std::max(lmax,rmax));
		}
	printf("%lld",res);

	return 0;
}
