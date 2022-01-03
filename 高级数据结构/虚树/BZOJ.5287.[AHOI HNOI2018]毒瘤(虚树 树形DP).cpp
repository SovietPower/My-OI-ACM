/*
12540kb	1096ms
设$f[i][0/1]$表示到第$i$个点，不选/选这个点的方案数。对于一棵树，有：$$f[x][0]=\prod_{v\in son[x]}(f[v][0]+f[v][1])\\f[x][1]=\prod_{v\in son[x]}f[v][0]$$

对于非树边的限制，可以再加一维非树边端点的状态（选没选），能得$55$分。
对于一条非树边$(u,v)$，要么是$u$选$v$不选，要么是$u$不选$v$选，要么是$u$不选$v$不选。发现后两种情况可以合并，即可以强制$u$选$v$不选DP一遍，再强制$u$不选$v$没有限制DP一遍，加起来就是对的了。对于多条非树边，$2^{m-n+1}$枚举非树边两端点的状态即可。能得$70\sim85$分（取决于评测机...）。（也可以容斥，强制枚举几条非树边的两端点同时选，其它没有限制）

可以想到对于非树边$(u,v)$，如果$u,v$之间的点及之间的子树中都没有非树边端点，那么$f[v][0/1]$对$f[u][0/1]$的贡献系数是一样的。
也就是说，设$z$的父亲是$y$，$y$的父亲是$x$，且有$$f[y][0]=k_0[z][0]\cdot f[z][0]+k_0[z][1]\cdot f[z][1]\\f[y][1]=k_1[z][0]\cdot f[z][0]+k_1[z][1]\cdot f[z][1]$$

设$x$只考虑$y$子树之外所有子树的贡献时，DP值分别是$g[x][0/1]$，那么把上面这个$f[y][0/1]$代进去有：$$f[x][0]=g[x][0]\cdot(k_0[y][0]+k_1[y][0])\cdot f[y][0]+g[x][0]\cdot(k_0[y][1]+k_1[y][1])\cdot f[y][1]\\f[x][1]=g[x][1]\cdot(k_0[z][0]\cdot f[z][0]+k_0[z][1]\cdot f[z][1])$$

同样对于$fa[x],fa[fa[x]]...$，$f[z][0/1]$对它的贡献系数也可以这么类似DP得到。
显然如果非树边$(u,v)$之间没有非树边端点，那无论$u,v$选不选贡献系数是不变的。而所有非树边端点的贡献系数可以$O(n)$通过上述DP一遍得到。
具体...对于非树边$(u,v)$，把$(u,v)$在树上的路径提出来，$v$暴力往上跳，同时统计其它子树的贡献。如果在这一过程中遇到了虚树上的点$w$，就连边$w\to v$边的转移系数是$v$的系数，然后将$v$的系数清零，用$w$的系数继续向上更新...如果$w$不是虚树上的点，就转移$v$的系数。（感觉不太好说...太菜了~~式子给代错~~想了好久）

所以就可以把非树边的$k=2(m-n+1)$个端点拿出来建虚树，枚举非树边端点的状态后，只在虚树上面做最初的DP，然后乘对应的贡献系数。
设$k=m-n+1$，复杂度$O(n+k2^k)$。

因为虚树上的点是可以确定的，所以可以第一次DFS的时候直接建出虚树并标记虚树上的点。（orz Kelin，替他感到可惜...）
注意边数是$n+10$！（不是$n$就够→_→）
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
