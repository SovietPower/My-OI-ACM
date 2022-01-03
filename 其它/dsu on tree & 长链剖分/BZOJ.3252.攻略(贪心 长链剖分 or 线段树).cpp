/*
10236kb	364ms
贪心，每次选价值最大的一条到根的链。比较显然（不选白不选）。
考虑如何维护这个过程。一个点的价值选了就没有了，而它只会影响它子树里的点，可以用DFS序+线段树修改。而求最大值也可以用线段树。
每个点只会被取一次，即价值也只会被清空一次。所以每选一条链就暴力往上跳，直到到一个清空过的点，顺便在线段树上修改经过点的子树权值就可以了。
复杂度$O((n+k)\log n)$。
实际上，每个点只被统计一次，就是选$k$条最长的不相交的链（链形态是从上到下的）。
所以可以想到长链剖分。以路径权值和作为深度，选最长的$k$条长链就行了。
用`nth_element`就可以把排序的复杂度也省了233.
所以复杂度$O(n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int Enum,H[N],nxt[N],to[N],A[N],son[N],cnt;
LL mxd[N],val[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS1(int x)
{
	LL mx=0;
	for(int i=H[x],v; i; i=nxt[i])
		DFS1(v=to[i]), mxd[v]>mx&&(mx=mxd[v],son[x]=v);
	mxd[x]=mx+A[x];
}
void DFS2(int x,int top)
{
	if(x==top) val[++cnt]=mxd[x];
	if(!son[x]) return;
	DFS2(son[x],top);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=son[x]) DFS2(to[i],to[i]);
}

int main()
{
	int n=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1), DFS2(1,1);
	K=std::min(K,cnt), std::nth_element(val+1,val+cnt-K+1,val+1+cnt);
	LL ans=0;
	for(int i=cnt-K+1; i<=cnt; ++i) ans+=val[i];
	printf("%lld\n",ans);

	return 0;
}
