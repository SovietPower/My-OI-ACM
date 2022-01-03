/*
836kb	20ms
发现这题和[BZOJ1202](https://lydsy.com/JudgeOnline/problem.php?id=1202)是一模一样的= =。因为全是相等关系，其实是十分特殊的差分约束，可以用带权并查集做。
记$fa[x]$表示$x$所在集合的根节点，$dis[x]$表示$x$到$fa[x]$的实际距离。
所谓距离是指：对于$r+c=k$，变成$r-(-c)=k$，即$r$比$-c$大$k$，就在$r\to -c$之间连距离为$k$的边，同时令$fa[r]=-c$。
这样对于一个限制$r,c,k$，如果$r,c$不在同一集合就合并（令较大的数的祖先是较小的数）。在并查集$Find$过程中顺便维护一下$dis$（具体见代码好惹，注意变量赋值顺序）。
如果$r,c$在同一集合，就根据$dis$差判一下它俩的距离是否等于$k$。
就算$k$可能是负的这么做也没什么问题。（废话=v=）
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2005;

int fa[N],dis[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int x)
{
	if(x==fa[x]) return x;
	int t=fa[x];
	fa[x]=Find(t), dis[x]+=dis[t];//!!!
	return fa[x];
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		const int n=read(),m=read(),tot=n+m;
		for(int i=1; i<=tot; ++i) fa[i]=i, dis[i]=0;
		bool fg=1;
		for(int u,v,w,K=read(); K--; )
		{
			u=read(),v=read()+n,w=read();
			if(!fg) continue;
			int r1=Find(u),r2=Find(v);
			if(r1!=r2) fa[r1]=r2, dis[r1]=dis[v]+w-dis[u];
			else if(dis[u]-dis[v]!=w) fg=0;
		}
		puts(fg?"Yes":"No");
	}

	return 0;
}
