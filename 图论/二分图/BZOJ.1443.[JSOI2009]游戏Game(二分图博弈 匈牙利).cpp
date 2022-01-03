/*
1680kb	256ms
二分图匹配总结一下就[这样](https://www.cnblogs.com/SovietPower/p/14433906.html)。
$Description$
一个$N*M$的有障碍的棋盘，先手放置棋子后，从后手开始轮流移动棋子，不能走重复的位置，不能移动的输。求在哪些位置放棋子是先手必胜的。
$Solution$
依旧先黑白染色，移动棋子对应一个匹配。
那么原图有两种情况：
一是存在完美匹配：那么无论先手选哪个点开始，假设是S集合某点，那么后手沿匹配边走，先手要么沿匹配边再走到S集合某点，要么没法走。即先手必败；
二是不存在完美匹配：
1.先手从最大匹配点开始，好像胜负情况都有，先不考虑；
2.先手从非最大匹配点（在某种最大匹配方案中未被匹配）开始，后手只能走到一个最大匹配点（若能走到非匹配点则又是一个匹配，与最大匹配矛盾），然后先手再走匹配边，发现后手只能走匹配边。
因为当前点如果存在非匹配边，则与起点那个非匹配点又形成了一条增广路，与最大匹配矛盾。
那这又成了情况一了，即后手必败。
即如果起点是非最大匹配点则必胜。起点只要在某种最大匹配下不是最大匹配点就满足。
再看情况二的1，如果起点可以不是最大匹配点，则先手必胜。否则先手必败，和情况二的2的结论一样。

现在问题是判断有哪些点不一定在最大匹配中。首先跑一遍最大匹配，未匹配的点肯定是。
然后这些未匹配点$x$可以替换掉邻接点$v$的一条匹配边，即$match[v]$也可以不在最大匹配中（原先的匹配边$v\rightarrow match[v]$替换为$v\rightarrow x$）。
对未匹配点DFS一遍就可以了。
复杂度在于匹配，$O(nm)$？

刚想起来最大匹配要拆点。。或者黑白染色？也不用拆点或者染色，每个点向四周都连边即可。
不拆点要注意`match[]/lk[]`这个数组对两边的集合都要给它赋值，匹配（`bool OK()`）的时候保证它之前没有匹配。。
做题前已经忘了最大匹配长什么样了...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 350000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define ID(i,j) ((i-1)*m+j)
#define Ck(i,j) (mp[i][j]&&1<=(i)&&(i)<=n&&1<=(j)&&(j)<=m)
const int N=10005,M=N<<2;

int n,m,vis[N],Time,Enum,H[N],nxt[M],to[M],lk[N],q[N];
bool mp[105][105],ok[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define AE(u,v) to[++Enum]=v,nxt[Enum]=H[u],H[u]=Enum,to[++Enum]=u,nxt[Enum]=H[v],H[v]=Enum
bool OK(int x)
{
	vis[x]=Time;
	for(int i=H[x],v; i; i=nxt[i])
		if(vis[v=to[i]]!=Time)
		{
			vis[v]=Time;
			if(!lk[v]||OK(lk[v])) return lk[v]=x,lk[x]=v;//两个都有啊 
		}
	return 0;
}
void DFS(int x)
{
	ok[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(lk[to[i]] && !ok[lk[to[i]]]/*vis[lk[to[i]]]!=Time*/) DFS(lk[to[i]]);
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i)
	{
		register char c=gc();
		for(; c!='.'&&c!='#'; c=gc());
		for(int j=1; j<=m; ++j,c=gc()) mp[i][j]=c=='.';		
	}
	int t=0;
	for(int i=1,tot=0; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(++tot,mp[i][j])
			{
				if(mp[i+1][j]/*i+1<=n*/) AE(tot,tot+m);
				if(mp[i][j+1]) AE(tot,tot+1);
			}
	for(int i=1,tot=0; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if((++tot,mp[i][j]) && !lk[tot]/*!*/ && (++Time,!OK(tot)))
				q[++t]=tot;
	if(!t) return puts("LOSE"),0;
	puts("WIN");
	for(int i=1; i<=t; ++i) DFS(q[i]);
	for(int i=1,tot=0; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(ok[++tot]) printf("%d %d\n",i,j);

	return 0;
}
