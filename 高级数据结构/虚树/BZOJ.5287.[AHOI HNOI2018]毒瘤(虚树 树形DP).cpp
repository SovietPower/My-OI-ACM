/*
12540kb	1096ms
��$f[i][0/1]$��ʾ����$i$���㣬��ѡ/ѡ�����ķ�����������һ�������У�$$f[x][0]=\prod_{v\in son[x]}(f[v][0]+f[v][1])\\f[x][1]=\prod_{v\in son[x]}f[v][0]$$

���ڷ����ߵ����ƣ������ټ�һά�����߶˵��״̬��ѡûѡ�����ܵ�$55$�֡�
����һ��������$(u,v)$��Ҫô��$u$ѡ$v$��ѡ��Ҫô��$u$��ѡ$v$ѡ��Ҫô��$u$��ѡ$v$��ѡ�����ֺ�����������Ժϲ���������ǿ��$u$ѡ$v$��ѡDPһ�飬��ǿ��$u$��ѡ$v$û������DPһ�飬���������ǶԵ��ˡ����ڶ��������ߣ�$2^{m-n+1}$ö�ٷ��������˵��״̬���ɡ��ܵ�$70\sim85$�֣�ȡ���������...������Ҳ�����ݳ⣬ǿ��ö�ټ��������ߵ����˵�ͬʱѡ������û�����ƣ�

�����뵽���ڷ�����$(u,v)$�����$u,v$֮��ĵ㼰֮��������ж�û�з����߶˵㣬��ô$f[v][0/1]$��$f[u][0/1]$�Ĺ���ϵ����һ���ġ�
Ҳ����˵����$z$�ĸ�����$y$��$y$�ĸ�����$x$������$$f[y][0]=k_0[z][0]\cdot f[z][0]+k_0[z][1]\cdot f[z][1]\\f[y][1]=k_1[z][0]\cdot f[z][0]+k_1[z][1]\cdot f[z][1]$$

��$x$ֻ����$y$����֮�����������Ĺ���ʱ��DPֵ�ֱ���$g[x][0/1]$����ô���������$f[y][0/1]$����ȥ�У�$$f[x][0]=g[x][0]\cdot(k_0[y][0]+k_1[y][0])\cdot f[y][0]+g[x][0]\cdot(k_0[y][1]+k_1[y][1])\cdot f[y][1]\\f[x][1]=g[x][1]\cdot(k_0[z][0]\cdot f[z][0]+k_0[z][1]\cdot f[z][1])$$

ͬ������$fa[x],fa[fa[x]]...$��$f[z][0/1]$�����Ĺ���ϵ��Ҳ������ô����DP�õ���
��Ȼ���������$(u,v)$֮��û�з����߶˵㣬������$u,v$ѡ��ѡ����ϵ���ǲ���ġ������з����߶˵�Ĺ���ϵ������$O(n)$ͨ������DPһ��õ���
����...���ڷ�����$(u,v)$����$(u,v)$�����ϵ�·���������$v$������������ͬʱͳ�����������Ĺ��ס��������һ�����������������ϵĵ�$w$��������$w\to v$�ߵ�ת��ϵ����$v$��ϵ����Ȼ��$v$��ϵ�����㣬��$w$��ϵ���������ϸ���...���$w$���������ϵĵ㣬��ת��$v$��ϵ�������о���̫��˵...̫����~~ʽ�Ӹ�����~~���˺þã�

���ԾͿ��԰ѷ����ߵ�$k=2(m-n+1)$���˵��ó�����������ö�ٷ����߶˵��״̬��ֻ�����������������DP��Ȼ��˶�Ӧ�Ĺ���ϵ����
��$k=m-n+1$�����Ӷ�$O(n+k2^k)$��

��Ϊ�����ϵĵ��ǿ���ȷ���ģ����Կ��Ե�һ��DFS��ʱ��ֱ�ӽ�����������������ϵĵ㡣��orz Kelin�������е���ϧ...��
ע�������$n+10$��������$n$�͹���_����
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mod 998244353
#define Mod(x,v) x>=mod&&(x-=mod)
#define Add(x,v) x+v>=mod?x+v-mod:x+v
#define Mul(x,v) 1ll*(x)*(v)%mod
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=1e5+15;

int cnt,Enum,H[N],nxt[N<<1],to[N<<1],f[N][2],g[N][2],sz[N],sta[N];
pr e[23];
bool vis[N],mark[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Coef//ficient
{
	int c0,c1;
	Coef(int c0=0,int c1=0):c0(c0),c1(c1) {}
	inline Coef operator +(const Coef &x)
	{
		return Coef(Add(c0,x.c0),Add(c1,x.c1));
	}
	inline Coef operator *(const int x)
	{
		return Coef(Mul(c0,x),Mul(c1,x));
	}
}k[N][2];
struct VirtualTree
{
	#define M 105
	int Enum,H[N],to[M],nxt[M];
	Coef k0[M],k1[M];
	inline void AE(int u,int v,Coef c1,Coef c2)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, k0[Enum]=c1, k1[Enum]=c2;
	}
}VT;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x,int fa)
{
	static bool vis[N];
	vis[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
			if(!vis[v]) DFS1(v,x), sz[x]+=sz[v];
			else mark[x]=1, x>v&&(e[cnt++]=mp(x,v),1);
	mark[x]|=sz[x]>=2, sz[x]=sz[x]||mark[x];
}
int DFS2(int x)//Build Tree
{
	static bool vis[N];
	int pos=0;
	vis[x]=1, g[x][0]=g[x][1]=1;
	for(int i=H[x],v,w; i; i=nxt[i])
		if(!vis[v=to[i]])
		{
			if(!(w=DFS2(v))) g[x][0]=Mul(g[x][0],g[v][0]+g[v][1]), g[x][1]=Mul(g[x][1],g[v][0]);
			else if(!mark[x]) k[x][0]=k[v][0]+k[v][1], k[x][1]=k[v][0], pos=w;
			else VT.AE(x,w,k[v][0]+k[v][1],k[v][0]);
		}
	if(!mark[x]) k[x][0]=k[x][0]*g[x][0], k[x][1]=k[x][1]*g[x][1];
	else k[x][0]=Coef(1,0), k[x][1]=Coef(0,1), pos=x;
	return pos;
}
void DP(int x)
{
	f[x][0]=g[x][0], f[x][1]=g[x][1];
	if(~sta[x]) f[x][sta[x]^1]=0;
	for(int i=VT.H[x],v; i; i=VT.nxt[i])
	{
		DP(v=VT.to[i]);
		f[x][0]=Mul(f[x][0],Mul(f[v][0],VT.k0[i].c0)+Mul(f[v][1],VT.k0[i].c1));
		f[x][1]=Mul(f[x][1],Mul(f[v][0],VT.k1[i].c0)+Mul(f[v][1],VT.k1[i].c1));
	}
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<=m; ++i) AE(read(),read());
	DFS1(1,1), mark[1]=1, DFS2(1);
	memset(sta,0xff,sizeof sta);
	LL ans=0;
	for(int s=0,lim=1<<cnt; s<lim; ++s)
	{
		bool fg=1;
		for(int i=0; i<cnt&&fg; ++i)
		{
			int x=e[i].first,y=e[i].second;
			if(s>>i&1) (!sta[x]||sta[y]==1)&&(fg=0), sta[x]=1, sta[y]=0;
			else sta[x]==1&&(fg=0), sta[x]=0;
		}
		if(fg) DP(1), ans+=f[1][0]+f[1][1];
		for(int i=0; i<cnt; ++i) sta[e[i].first]=-1, sta[e[i].second]=-1;
	}
	printf("%lld\n",ans%mod);

	return 0;
}
