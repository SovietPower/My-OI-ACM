/*
134ms	33496KB
首先变换的周期是$26$，而所有字符是同时变的，所以一共就只有$26$种树，我们对$26$棵树分别处理。
求某节点到根路径上的字符串，可以从根往下哈希，$O(n)$预处理出。
然后我们就可以求出任意时刻的树上，从下往上某条路径的字符串的哈希值了。
对于询问，倍增往上跳找到第一个字符不相同的位置即可（注意不要跳过头）。
复杂度$O(26n+q\log n)$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define S 26
#define seed 31
#define Add(x,v) (x+=v)>=S&&(x-=S)
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
typedef unsigned long long ull;
const int N=1e5+5;

int dep[N],fa[17][N],H[N],nxt[N],ch[N],tm[N];
ull pw[N],hs[S][N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline char Get()
{
	register char c=gc(); while(!isalpha(c)) c=gc();
	return c;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
void DFS(int x)
{
	for(int v=H[x]; v; v=nxt[v])
	{
		for(int i=0,now=ch[v]; i<S; ++i,Add(now,tm[v])) hs[i][v]=hs[i][x]*seed+now;
		dep[v]=dep[x]+1, DFS(v);
	}
}
void Solve()
{
	int n=read();
	for(int i=2; i<=n; ++i)
		AE(fa[0][i]=read(),i), ch[i]=Get()-'a', tm[i]=read()%26;
	DFS(1);
	int mx=0,lim=0;
	for(int i=1; i<=n; ++i) mx=std::max(mx,dep[i]);
	while(1<<lim<=mx) ++lim;
	for(int j=1; j<=lim; ++j)
		for(int i=1; i<=n; ++i)
			fa[j][i]=fa[j-1][fa[j-1][i]];
	for(int Q=read(); Q--; )
	{
		int x=read(),y=read(),t=read()%26;
		for(int i=lim; ~i; --i)
			if(std::min(dep[x],dep[y])>=1<<i)
				hs[t][x]-hs[t][fa[i][x]]*pw[1<<i]==hs[t][y]-hs[t][fa[i][y]]*pw[1<<i]&&(x=fa[i][x],y=fa[i][y]);
		int c1=(ch[x]+t*tm[x])%S,c2=(ch[y]+t*tm[y])%S;
		puts(c1>c2?">":c1<c2?"<":"=");
	}
	memset(H,0,n+1<<2);
}

int main()
{
	pw[0]=1;
	for(int i=1; i<N; ++i) pw[i]=pw[i-1]*seed;
	for(int T=read(); T--; Solve());
	return 0;
}
