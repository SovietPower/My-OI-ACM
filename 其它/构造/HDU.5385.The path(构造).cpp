/*
187MS	3328K
$Description$
给定一张$n$个点$m$条边的有向图，每条边的边权在$[1,n]$之间。
记$d[i]$为$1$到$i$的最短路。你需要对每条边确定一个边权，使得存在一个$i\in[2,n]$，满足$d[1]\lt d[2]\lt...d[i]\gt d[i+1]\gt...d[n]$。
输出方案（每条边的边权）。输入保证有解。
$n,m\leq10^5$。
$Solution$
$d[1]=0$，考虑$d[i]=1$的点有哪些。那要么是$2$，要么是$n$，但一定存在边$1\to i$。
$d[i]=2,3...$的点同理。
所以标记$1$能到的所有点，然后维护两个指针$l=2,r=n$。从$l,r$中选一个标记过的，令其$d[i]=++now$，然后标记能到的点，往中间移动这个指针即可。
因为保证有解，所以每次至少有一个指针会移动。
输出答案时对于边$(i,j)$，输出$|d[i]-d[j]|$即可。
会有重边，不要输出$0$就好了。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int Enum,H[N],nxt[N],fr[N],to[N],dis[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int v,int u)//opposite
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum;
}

int main()
{
	for(int T=read(); T--; )
	{
		int n=read(),m=read();
		Enum=0, memset(H,0,n+1<<2), memset(vis,0,n+1);
		for(int i=1; i<=m; ++i) AE(read(),read());
		for(int i=H[1]; i; i=nxt[i]) vis[to[i]]=1;
		for(int l=2,r=n,now=1; l<=r; )
		{
			int x=vis[l]?l++:r--; dis[x]=now++;
			for(int i=H[x]; i; i=nxt[i]) vis[to[i]]=1;
		}
		for(int i=1; i<=m; ++i) printf("%d\n",fr[i]==to[i]?1:std::abs(dis[fr[i]]-dis[to[i]]));
	}

	return 0;
}
