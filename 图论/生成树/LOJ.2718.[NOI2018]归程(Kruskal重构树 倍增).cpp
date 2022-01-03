/*
4860ms	50.49MB + 4392ms	50.33MB(��4������)
$Description$
����һ������ͼ��ÿ�����г���$l$�ͺ���$h$��
$q$��ѯ�ʣ�ÿ��ѯ�ʸ������$u$��ˮλ��$p$��Ҫ�ߵ�$1$����ʼʱ���Դ�$u$���������к��δ���$p$�ıߣ�Ȼ���������ʱ���³��������ߵ�$1$������·�����߳�����Сֵ��ǿ�����ߡ�
$n\leq 2\times10^5,\ m,q\leq 4\times 10^5$��
$Solution$
�����뵽���߶�Kruskal�ع���+Ԥ������1�ľ���dis��
��һ������������������㽨�Ļ���������������ߣ������������ߴ𰸵�Ȼ��0...�������Щ���߲����ߣ���ô���߷�Χ����������ĳ����ͨ�顣
Ȼ����������ĳ����ͨ���ͼ(��Ҫ�������ѵ����ֿ�?)ûʲô�����������ǿ������������ߵĸ߶���Ҷ�����ϵݼ�������ÿ��ѯ�� �ҵ������С�Ŀ��е�󣬴𰸾���������dis��Сֵ(����̬��Ȼ����Ӱ��ʲô)��
������Kruskal�ϲ���������ʱ���½�һ���ڵ���Ϊ�����ϵĲ��Ĵ���ڵ㣬��͸߶�mnΪ������Ȩ(��Ȼ������������еĴ�)��disΪ������dis��min������Ҷ�ӽڵ㼴Ϊԭ���нڵ㡣
**Update on 2019.1.5**
[UOJ](http://uoj.ac/problem/393)�ϱ�hack��....�����Ǵ�һ���������ݹ����ˣ�������....���ڲ���ġ�
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 400000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=2e5+5,M=8e5+5,INF=0x7fffffff;

int n,m,tot,Enum,H[N],nxt[M],to[M],len[M],dis[N],fa[N<<1][19],mn[N<<1],anc[N<<1],Ans[N<<1];
std::priority_queue<pr> q;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int fr,to,h;
	Edge() {}
	Edge(int fr,int to,int h):fr(fr),to(to),h(h) {}
	bool operator <(const Edge &x)const{
		return h>x.h;
	}
}e[M>>1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int _h,int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
	e[Enum>>1]=Edge(u,v,_h);
}
void Dijkstra()
{
	static bool vis[N];
	memset(dis,0x3f,sizeof dis), memset(vis,0,sizeof vis);
	dis[1]=0, q.push(mp(0,1));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int v,i=H[x]; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i])
				dis[v]=dis[x]+len[i], q.push(mp(-dis[v],v));
	}
}
int Get_fa(int x){
	return x==anc[x]?x:anc[x]=Get_fa(anc[x]);
}
void Kruskal()
{
	for(int i=1; i<=n; ++i) anc[i]=i, Ans[i]=dis[i];
	int m=Enum>>1; std::sort(e+1,e+1+m);
	for(int r1,r2,k=1,i=1; i<=m; ++i)
	{
		if((r1=Get_fa(e[i].fr))==(r2=Get_fa(e[i].to))) continue;
		anc[r1]=anc[r2]=fa[r1][0]=fa[r2][0]=++tot, anc[tot]=fa[tot][0]=tot/*!*/;//����½���fa[tot]��(������Ϊ���ڵ�)
		mn[tot]=e[i].h, Ans[tot]=std::min(Ans[r1],Ans[r2]);
		if(++k==n) break;
	}
}
void Init_ST()
{
	for(int i=1; i<=18; ++i)
		for(int x=1; x<=tot; ++x) fa[x][i]=fa[fa[x][i-1]][i-1];
}
inline int Solve(int p,int ht)
{
	for(int i=18; ~i; --i)
		if(mn[fa[p][i]]>ht) p=fa[p][i];
	return Ans[p];
}

int main()
{
//	freopen("return.in","r",stdin);
//	freopen("return.out","w",stdout);

	int Case=read();
	while(Case--)
	{
		Enum=0, memset(H,0,sizeof H);
		tot=n=read(), m=read();
		while(m--) AddEdge(read(),read(),read(),read());
		Dijkstra(), Kruskal(), Init_ST();

		int Q=read(),K=read(),S=read(),ans=0,pos,ht;
		if(K) while(Q--)
			pos=(read()+ans-1)%n+1,ht=(read()+ans)%(S+1),printf("%d\n",ans=Solve(pos,ht));
		else while(Q--)
			pos=read(),ht=read(),printf("%d\n",Solve(pos,ht));
	}
	return 0;
}
