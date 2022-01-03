/*
18720kb	3244ms
$Description$
给你一张有向图及一条$1$到$n$的最短路。对这条最短路上的每条边，求删掉这条边后$1$到$n$的最短路是多少。
$Solution$
枚举删每条边然后求最短路显然不行。考虑怎么保留之前求最短路的一些信息。
考虑删掉一条边后的最短路，$1$沿最短路到了某个点$x$，然后如果$x$到了最短路上的某点$y$，之后一定是沿$y$到$n$的最短路走到$n$。
$n$也是最短路上的点，即$x$一定会到达某个$y$并沿最短路到达$n$。这时就可以在$y$处直接更新$Ans$。
我们发现在$y$处的值可以更新所有$y$之前最短路的边的$Ans$。
我们用堆把这个值及$y$前面那条最短路的边的标号$id$存下来。如果当前删的边$i$大于等于堆顶的$id$，就可以直接用堆顶的答案了。否则直接$pop$掉堆顶。
所以我们把所有最短路边删掉，每求完一条边$(u,v)$的值时更新$dis[v]$，然后把$v$再加入队列SPFA就行了。
每次SPFA不需要清空$dis$，$dis$是递减的。
当然本题复杂度玄学。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=2e5+5;

int Enum,H[N],nxt[M],fr[M],to[M],len[M],dis[N],dt[N],A[N],pre[N];
bool ban[M];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int pos,val;
	bool operator <(const Node &x)const
	{
		return val>x.val;
	}
};
std::priority_queue<Node> hp;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int w,int v,int u)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
}
void SPFA(int s)
{
	static bool inq[N];
	static std::queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(!ban[i]&&dis[v=to[i]]>dis[x]+len[i])
			{
				dis[v]=dis[x]+len[i];
				if(pre[v]) hp.push((Node){pre[v],dis[v]+dt[pre[v]]});
				else if(!inq[v]) inq[v]=1, q.push(v);
			}
	}
}

int main()
{
	int n=read(),m=read(),l=read();
	for(int i=1; i<=m; ++i) AE(read(),read(),read());
	for(int i=1,id; i<=l; ++i)
	{
		A[i]=id=read();
		ban[id]=1, pre[to[id]]=i;
	}
	for(int i=l-1; i; --i) dt[i]=dt[i+1]+len[A[i+1]];

	memset(dis,0x3f,sizeof dis);
	dis[1]=0, SPFA(1);
	for(int i=1,id; i<=l; ++i)
	{
		while(!hp.empty()&&hp.top().pos<i) hp.pop();
		if(hp.empty()) puts("-1");
		else printf("%d\n",hp.top().val);
		id=A[i], dis[to[id]]=dis[fr[id]]+len[id];
		SPFA(to[id]);
	}

	return 0;
}
