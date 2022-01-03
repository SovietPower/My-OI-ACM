/*
$Description$
有一棵高度为$h$的满二叉树，点从$1$到$2^h-1$编号（无序）。每次你可以询问一个点的编号，交互库会返回其所有邻接点的编号。你需要在$16$次询问内确定这棵树根节点的编号。
$h\leq 7$。
$Solution$
考虑随便问一个点，然后任意找个相邻点走。这样如果不往回走，最差情况下是一直走到一个叶子，这样找走两遍，扩展出一条叶子到叶子的链，就可以往上扩展了。这样最多扩展$1+2+\ldots+7=28$个点，但是确定根节点就够了，即$21$个。
还是不行。在深度比较浅时代价会比较高，但是深度浅了我们离根节点就更近。所以在离根足够近（距离为$2$）直接BFS。这样代价为$10+1+2+4=17$，但是最后一个点不需要查知道了，代价为$16$。
思路很好理解，但是代码好难写啊。。弃疗了。参考个吧。orzyanQval.
要对初始点DFS两次，不管路径如何，我们记下两条路径经过点数c1,c2，其深度就是(c1+c2)/2+1。如果有一次是向根节点延伸(c1!=c2)，就可以直接跳到经过路径上最靠近根的点。
之后保证每次向上走，用之前的深度和新路径的点数同样可以跳。最后手动BFS。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=150;

int h,dgr[N],son[N][3],A1[N],A2[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define Check(x) if(dgr[x]==2) return x
inline void Query(int x)
{
	vis[x]=1;
	printf("? %d\n",x), fflush(stdout);
	dgr[x]=read();
	for(int i=0; i<dgr[x]; ++i) son[x][i]=read();
}
inline int Step(int x)
{
	for(int i=0; i<dgr[x]; ++i) if(!vis[son[x][i]]) return son[x][i];
	return son[x][0];
}
int Solve()
{
	memset(vis,0,sizeof vis);
	int h=read(), x=rand()%((1<<h)-1)+1, dep;
	Query(x); Check(x);
	if(dgr[x]==1) dep=1;
	else
	{
		int cnt1=0, cnt2=0;
		for(int v=Step(x); ; v=Step(v))
		{
			Query(v), A1[++cnt1]=v; Check(v);
			if(dgr[v]==1) break;
		}
		for(int v=Step(x); ; v=Step(v))
		{
			Query(v), A2[++cnt2]=v; Check(v);
			if(dgr[v]==1) break;
		}
		dep=(cnt1+cnt2>>1)+1;
		if(cnt1>cnt2) x=A1[cnt1-dep+1];
		else if(cnt1<cnt2) x=A2[cnt2-dep+1];
	}
	for(int cnt=0; dep<4/*not 5*/; cnt=0)
	{
		for(int v=Step(x); ; v=Step(v))
		{
			Query(v), A1[++cnt]=v; Check(v);
			if(dgr[v]==1) break;
		}
		dep=dep+cnt+1>>1, x=A1[cnt-dep+1];
	}
	int a,b,c,d,e;
	if(dep<h)
	{
		x=Step(x), Query(x); Check(x);
	}
	if(dep<h-1)
	{
		a=Step(x), Query(a); Check(a);
		b=Step(x), Query(b); Check(b);
	}
	if(dep<h-2)
	{
		c=Step(a), Query(c); Check(c);
		d=Step(a), Query(d); Check(d);
		e=Step(b), Query(e); Check(e);
		return Step(b);
	}
	return x;
}

int main()
{
	for(int T=read(); T--; printf("! %d\n",Solve()),fflush(stdout));
	return 0;
}
