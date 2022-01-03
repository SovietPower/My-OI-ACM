/*
30268kb	2620ms
要求如果$a_{p_j}=p_k$，$k\lt j$，可以理解为$k$要在$j$之前选。
那么对于给定的$a_j=k$，我们可以连边$k\to j$建一张图。如果图有环，那么无解；否则这是一棵以$0$为根的树。
限制就变成了，选一个点前必须要选其父亲；如果第$k$个选点$i$，$i$的贡献是$k\cdot w_i$。

然后怎么做呢...
假设当前最小的数是$x$，那么如果$fa[x]$选过，现在一定选$x$；否则如果有一次选了$fa[x]$，下一次一定选$x$。
考虑到按顺序选点实际是构成一个序列，且上面的$x$一定和$fa[x]$在序列中挨在一起。所以考虑把$x,fa[x]$合并成一个序列，再考虑其它的。
之前是比点权，现在我们要比较序列与序列之间谁放在后面更优。
考虑两个序列$a,b$，设$a$中有$t_1$个点，$b$中有$t_2$个点，假设现在已经选了$k$个点，那么$ab,ba$的贡献分别为$$W_{ab}=\sum_{i=1}^{t_1}(k+i)w_{a_i}+\sum_{i=1}^{t_2}(k+i+t_1)w_{b_i}\\W_{ba}=\sum_{i=1}^{t_2}(k+i)w_{b_i}+\sum_{i=1}^{t_1}(k+i+t_2)w_{a_i}\\W_{ab}-W_{ba}=t_1\sum w_{b_i}-t_2\sum w_{a_i}$$

那么$W_{ab}>W_{ba}\Rightarrow \frac{\sum w_{b_i}}{t_2}>\frac{\sum w_{a_i}}{t_1}$，即平均数更小的放到前面更优。
所以我们就可以拿堆维护了，每次取出最小的，把它与父节点所在序列合并。这里可以用带修改堆修改父节点的状态，也可以打个标记删掉父节点的状态（其实判一下$sz$是否等于当前状态下的$sz$就可以了）。
答案就在一个序列被放到后面的时候统计就可以了。

另外堆也可以用[$STL$里的$heap$]。只需要`#include <algorithm>`。
常数应该是比`priority_queue`小一些的？可能是我写的丑...
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int Cnt,fa[N],Enum,H[N],nxt[N],to[N],F[N],sz[N];
LL w[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int x,sz; LL val;
	bool operator <(const Node &x)const
	{
		return val*x.sz>x.val*sz;
	}
};

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
}
void DFS(int x)
{
	static bool vis[N];
	++Cnt, vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) DFS(to[i]);
		else {puts("-1"); exit(0);}
}
int Find(int x)
{
	return x==F[x]?x:F[x]=Find(F[x]);
}

int main()
{
//	freopen("perm.in","r",stdin);
//	freopen("perm.out","w",stdout);

	const int n=read();
	for(int i=1; i<=n; ++i) AE(fa[i]=read(),i);
	DFS(0);
	if(Cnt<=n) return puts("-1"),0;
	std::priority_queue<Node> q;
	for(int i=0; i<=n; ++i) F[i]=i, sz[i]=1;//from 0
	for(int i=1; i<=n; ++i) q.push((Node){i,1,w[i]=read()});
	LL ans=0;
	while(!q.empty())
	{
		Node tmp=q.top(); q.pop();
		int x=Find(tmp.x);
		if(tmp.sz!=sz[x]) continue;
		int r=Find(fa[x]);
		F[x]=r, ans+=tmp.val*sz[r], sz[r]+=sz[x], w[r]+=w[x];
		if(r) q.push((Node){r,sz[r],w[r]});
	}
	printf("%lld\n",ans);

	return 0;
}
