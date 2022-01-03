/*
72992kb	784ms
$Description$
给定$n$个节点的完全二叉树，每个点为白色，权值$a_i$。每条边权值$b_i$。第一次染黑某个点无花费，然后每次染黑点$v$的花费，为上一个染黑点$u$到$v$的距离$d_{u,v}$，乘这个点的权值$a_v$。过程中要保证任意时刻黑色点连通，且染黑$v$后必须再染黑$v$子树的所有点，才能染其它点。求染黑所有点最小花费。
$n\leq 2\times10^5$。

$Solution$
（下面点亮一个灯泡就说成染色了，感觉染色比较顺口...
注意完全二叉树$\neq$满二叉树，点亮第一个灯泡$\neq$第一次点亮一号灯泡，根节点应该就是$1$...

代价取决于下一次跳到哪个点，考虑记下这个状态，令$f[i][j]$表示染完$i$这棵子树后下一次染$j$的最小花费，但是状态数是$O(n^2)$的。
因为染色顺序很特殊，染完整棵$i$子树后下一步要么是染$i$的某个祖先，要么是染$i$的某个祖先的另一个儿子（除去$i$这棵子树外的另一棵子树）。同时树深是$O(\log n)$的，也就是一个点最多有$\log n$个祖先。
所以我们记$f[i][j]$表示染完$i$子树后，走到$i$的$j$级祖先的最小花费；$g[i][j]$表示染完$i$子树后，走到$i$的$j$级祖先的另一个儿子处（即$i$的$j$级祖先的兄弟节点）的最小花费。状态数是$O(n\log n)$的。

考虑$f[i][j]/g[i][j]$的转移。
如果$i$是叶子节点，那直接算一下走到对应节点的花费即可。
如果$i$只有左儿子，那走到左儿子再从左儿子走到对应节点即可。
否则$i$有两个儿子$l,r$，要么是$i\to l\to r\to i的对应祖先$，要么是$i\to r\to l\to i的对应祖先$，取个$\min$即可。
DP的复杂度也是$O(n\log n)$的。

然后怎么统计以$x$作为起点的答案？
注意到一定是染完$x$子树，然后跳到$fa[x]$，染$fa[x]$的另一棵子树（如果有）；然后跳到$fa[fa[x]]$，染$fa[fa[x]]$的另一棵子树...重复这个过程。
每次跳$fa$，用DP数组统计一下花费就好了。总复杂度也是$O(n\log n)$。

注意是用`dep[1]`等于$1$来得到`dep`的（因为要算$g[i][j]$，表示$j$级祖先的**另一个儿子**！）。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define fa(x) (x>>1)
#define lson(x) (x<<1)
#define rson(x) (x<<1|1)
#define Anc(x,j) (x>>j)//x的j级祖先 
#define Bro(x,j) ((x>>j-1)^1)//x的j级祖先的另一个儿子 
typedef long long LL;
const int N=2e5+5,BIT=18;

int A[N],dep[N],dis[N][BIT];
LL f[N][BIT],g[N][BIT];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	dep[1]=1;
	for(int x=2; x<=n; ++x)
	{
		dep[x]=dep[fa(x)]+1, dis[x][1]=read();
		for(int j=2; j<=dep[x]; ++j)
			dis[x][j]=dis[fa(x)][j-1]+dis[x][1];
	}
	for(int x=n; x; --x)
	{
		int l=lson(x),r=rson(x);
		for(int j=1; j<=dep[x]; ++j)
			if(r<=n)
			{
				f[x][j]=std::min(1ll*A[l]*dis[l][1]+g[l][1]+f[r][j+1],1ll*A[r]*dis[r][1]+g[r][1]+f[l][j+1]);
				g[x][j]=std::min(1ll*A[l]*dis[l][1]+g[l][1]+g[r][j+1],1ll*A[r]*dis[r][1]+g[r][1]+g[l][j+1]);
			}
			else if(l<=n)
			{
				f[x][j]=1ll*A[l]*dis[l][1]+f[l][j+1];
				g[x][j]=1ll*A[l]*dis[l][1]+g[l][j+1];
			}
			else f[x][j]=1ll*dis[x][j]*A[Anc(x,j)], g[x][j]=1ll*(dis[x][j]+dis[Bro(x,j)][1])*A[Bro(x,j)];
	}
	LL ans=1ll<<61;
	for(int i=1; i<=n; ++i)
	{
		LL now=f[i][1];
		for(int x=fa(i),las=i; x; las=x,x=fa(x))
		{
			int y=las^1;
			if(y<=n) now+=1ll*dis[y][1]*A[y]+f[y][2];
			else now+=1ll*dis[x][1]*A[fa(x)];
		}
		ans=std::min(ans,now);
	}
	printf("%lld\n",ans);

	return 0;
}
