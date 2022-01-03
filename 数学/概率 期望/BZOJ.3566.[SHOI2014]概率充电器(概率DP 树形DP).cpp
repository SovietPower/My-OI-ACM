/*
38344kb	3684ms
$Description$
给定一棵树，每个点是一个可导电元件。每条边有$p\%$的概率导电，每个元件本身有$q\%$的概率被充电，求期望有多少个元件有电。
$n\leq 5\times10^5$。
$Solution$
每个点的贡献都是$1$，所以直接求每个点通电的概率$F_i$，答案就是$\sum F_i$。
把$F_x$分成：父节点通电给$x$带来的概率$g_x$，和$x$及其子树通电给$x$带来的概率$f_x$。
对于两个独立的事件$A,B$，由概率加法公式，$P(A+B)=P(A)+P(B)-P(A)P(B)$，$F_x=f_x+g_x-f_xg_x$。
令$p_x$表示$x$本身通电的概率，$p_{(x,v)}$表示边$(x,v)$通电的概率，那么$f_x=p_x+\sum_{v\in son[x]}f_vp_{(x,v)}$。注意这里的加法是概率的加法（相加再减去同时发生的概率）。
$g_x$的转移，就是$F_{fa}$减去$x$转移到$fa$的概率。因为$P(A)=\frac{P(A+B)-P(B)}{1-P(B)}$，所以除去$x$的贡献外$fa$通电的概率$q=\frac{F_{fa}-f_xp_{(fa,x)}}{1-f_xp_{(fa,x)}}$，所以$g_x=q\times p_{(fa,x)}$。
然后就做完啦。
**ps：**其实不是很懂第二次DFS，$P(B)=1$的时候（除$0$）$P(A)$应该等于多少...
然而数据水？并不会出现$P(B)=1$的情况。

还可以令$F_x$表示$x$不通电的概率，$F_x=f_xg_x$。那么只考虑子树的贡献，记$h_v$表示$v$给父节点贡献的概率，即$h_v=f_v+(1-f_v)(1-p_{(x,v)})$，有$f_x=(1-p_x)\prod h_v$。
再考虑父节点的贡献$g_x$，同样考虑直接减掉$x$对$fa$的贡献，即$g_x=\frac{F_{fa}}{h_x}$（注意特判$h_x=0$的情况）。
同样两次DP就OK啦。

调了半年原来是边权没开`double`...
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define eps 1e-10
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1];
double f[N],F[N],pe[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int w,int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, pe[Enum]=1.0*w/100;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, pe[Enum]=pe[Enum-1];
}
void DFS1(int x,int fa)
{
	double b;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
			DFS1(v,x), b=f[v]*pe[i], f[x]=f[x]+b-f[x]*b;
}
void DFS2(int x,int fa)
{
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			double b=f[v]*pe[i];
			if(fabs(1-b)<eps) F[v]=1;//=1怎么考虑的啊...网上都这么写的=-=
			else
			{
				double q=(F[x]-b)/(1-b)*pe[i];
				F[v]=f[v]+q-f[v]*q;
			}
			DFS2(v,x);
		}
}

int main()
{
	const int n=read();
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	for(int i=1; i<=n; ++i) f[i]=1.0*read()/100;
	DFS1(1,1), F[1]=f[1], DFS2(1,1);
	double ans=0;
	for(int i=1; i<=n; ++i) ans+=F[i];
	printf("%.6f\n",ans);

	return 0;
}
