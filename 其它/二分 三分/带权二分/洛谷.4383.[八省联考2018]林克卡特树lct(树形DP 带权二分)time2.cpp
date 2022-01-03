/*
$Description$
给定一棵边带权的树。求删掉K条边、再连上K条权为0的边后，新树的最大直径。
$n,K\leq3\times10^5$。
$Solution$
题目可以转化为，求树上不相交的$k+1$条链，使得它们的边权和最大(已不想再说什么了。。)。
选择链数越多，答案增长得越慢，减少的时候还会减少得越快，即形成了一个$K-Ans_K$的上凸包；而如果没有链数的限制，DP是很容易的(有链数得加一维$k$)。
带权二分。DP用$f[x][0/1/2]$表示点$x$度数为$0/1/2$时的最优解，记一下最优情况下的链数。

**DP细节：**
$f[x][1]$即度数为$1$时不加作为链的花费，而是合并时加上，更方便吧。
最后用$f[x][0]$ 与 以$f[x][1]$结束链或是$f[x][2]$取个$\max$，表示最终状态（不再向上更新的最优状态，即从这断开）。
结构体写虽然可能慢点但是太好写了。但常数竟然这么大的么...
注意是$K+1$→_→ 

**[Update] 19.2.11**
二分边界是，使得边界足够大能保证每一个物品都不会选，也就是每个物品的最大可能值就可以了。（比如[CF739E](https://www.cnblogs.com/SovietPower/p/9163792.html)，权值0~1就够）
然后...二分的时候只要保证恰好取到$k$个就可以了，斜率具体是多少无所谓...吧。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;
const LL INF=1ll<<60;

int Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1];
LL C;
struct Node
{
	LL val; int cnt;
	inline Node operator +(int v)
	{
		return (Node){val+v,cnt};
	}
	inline Node operator +(const Node &x)
	{
		return (Node){val+x.val,cnt+x.cnt};
	}
	inline bool operator <(const Node &x)const
	{
		return val==x.val?cnt>x.cnt:val<x.val;
	}
}f[N][3];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline Node Upd(const Node &x)
{
	return (Node){x.val-C,x.cnt+1};
}
void DFS(int x,int fa)
{
	f[x][0]=f[x][1]=(Node){0,0}, f[x][2]=(Node){-INF,0};
	//f[x][1]=0，直接合并。
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			f[x][2]=std::max(f[x][2]+f[v][0],Upd(f[x][1]+f[v][1]+len[i]));
			f[x][1]=std::max(f[x][1]+f[v][0],f[x][0]+f[v][1]+len[i]);
			f[x][0]=f[x][0]+f[v][0];
		}
	f[x][0]=std::max(f[x][0],std::max(Upd(f[x][1]),f[x][2]));//为方便直接把f[x][0]作为在x处断开的最优值即可。
}

int main()
{
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);

	const int n=read(),K=read()+1;
	LL s1=0,s2=0;
	for(int i=1,u,v,w; i<n; ++i) u=read(),v=read(),w=read(),w>0?s1+=w:s2-=w,AE(u,v,w);
	LL r=std::max(s1,s2),l=-r,mid;
	while(l<r)
	{
		if(C=mid=l+r>>1,DFS(1,1),f[1][0].cnt>K) l=mid+1;
		else r=mid;
	}
	C=l, DFS(1,1);
	printf("%lld\n",f[1][0].val+C*K);

	return 0;
}
