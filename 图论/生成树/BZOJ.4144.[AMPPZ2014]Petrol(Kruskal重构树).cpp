/*
20216kb	2600ms
$Description$
������Ȩ����ͼ����$s$�����Ǽ���վ��ÿ��������������$b$����ʾ���߾��벻�ܳ���$b$�����ڼ���վ�ɲ�����
$q$��ѯ�ʣ�ÿ�θ���$S,T,b$��$S,T$Ϊ����վ��������������Ϊ$b$�ĳ��ܷ��$S$�ߵ�$T$��
$n,m,q\leq 2\times10^5,\ b\leq 2\times 10^9$��
$Solution$
���ȷǼ���վ�ĵ���û���õġ��������ɾ����Щ��Ȼ���ڼ���վ֮������Ӧ�ıߡ�
��[����](https://blog.csdn.net/pbihao/article/details/54882546)��һ��ͼ��![](https://img2018.cnblogs.com/blog/1143196/201904/1143196-20190422212654603-959092877.png)
��Ϊ$b<a\ \&\&\ b<c$��������$b+c<a+c\ \&\&\ b+a<a+c$��Ҳ���ǵ�һ����ʱ����ȥһ����������ĵ������ȥ�����ĵ�һ����������$bel[p]$Ϊ��$p$������ļ���վ��$dis[p]$Ϊ$bel[p]$��$p$�ľ��룬����һ����$(u,v,w)$����$bel[u]\neq bel[v]$����ô����$bel[u],bel[v]$֮���һ��$dis[u]+dis[v]+w$�ı߼��ɡ�����Ϊ���κ�һ�����������$u$����ȥһ��$bel[u]$��ȥ��ĵ㲻��������ֱ�Ӻ�$bel[u]$���߾����ˣ�
������������м��͵�Ϊ��㣬$Dijkstra$��һ���Դ���·��
Ȼ����һ����С��������ѯ�ʾ��ж������·���ϵ����ֵ���ɡ�
ע������������ʱ�����ֱ�Ӱ��Ⱥϲ������߱�����$O(\log n)$�ĸ߶ȡ�����ѯ�ʱ�����$fa$���ɡ�

Ҫע��ͼ���ܲ���ͨ����
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],dis[N],bel[N],F[N],fa[N],w[N],rk[N],dep[N];
char IN[MAXIN],*SS=IN,*TT=IN;
std::priority_queue<pr> q;
struct Edge
{
	int u,v,w;
	bool operator <(const Edge &x)const
	{
		return w<x.w;
	}
}e[N<<1];//˫��߰� 

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int w,int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
int Dijkstra()
{
	static bool vis[N];
	int cnt=0;
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i])
				dis[v]=dis[x]+len[i], bel[v]=bel[x], q.push(mp(-dis[v],v));
			else if(bel[x]!=bel[v])
				e[++cnt]=(Edge){bel[x],bel[v],dis[x]+dis[v]+len[i]};
	}
	return cnt;
}
int Find(int x)
{
	return x==F[x]?x:F[x]=Find(F[x]);
}
void GetDep(int x)
{
	if(fa[x]&&!dep[fa[x]]) GetDep(fa[x]);
	dep[x]=dep[fa[x]]+1;
}
void Kruskal(const int n,const int m)
{
	std::sort(e+1,e+1+m);
	for(int i=1; i<=n; ++i) F[i]=i;
	for(int i=1,r1,r2,k=1; i<=m; ++i)
	{
		if((r1=Find(e[i].u))==(r2=Find(e[i].v))) continue;
		if(rk[r1]<rk[r2]) std::swap(r1,r2);//r2->r1
		else if(rk[r1]==rk[r2]) ++rk[r1];
		F[r2]=r1, fa[r2]=r1, w[r2]=e[i].w;
	}
	for(int i=1; i<=n; ++i) if(!dep[i]) GetDep(i);
}
inline bool Query()
{
	int u=read(),v=read(),val=read();
	if(Find(u)!=Find(v)) return 0;//!
	if(dep[u]<dep[v]) std::swap(u,v);
	for(int tmp=dep[v]; dep[u]>tmp; u=fa[u])
		if(w[u]>val) return 0;
	for(; u!=v; u=fa[u],v=fa[v])
		if(w[u]>val||w[v]>val) return 0;
	return 1;
}

int main()
{
	const int n=read(),s=read(),m=read();
	memset(dis,0x7f,sizeof dis);
	for(int i=1,x; i<=s; ++i) dis[x=read()]=0, bel[x]=x, q.push(mp(0,x));
	for(int i=1; i<=m; ++i) AE(read(),read(),read());
	int cnt=Dijkstra(); Kruskal(n,cnt);
	for(int Q=read(); Q--; puts(Query()?"TAK":"NIE"));

	return 0;
}
