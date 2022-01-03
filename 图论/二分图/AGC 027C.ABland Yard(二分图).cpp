/*
30ms	10496KB
$Description$
给定一张图（可能存在自环），每个点上有A或B。求是否存在一条路径，使得在上面不断走，能够得到所有AB串组合（可以重复经过点）。
$n\leq2\times10^5,m\leq2\times10^5$。
$Solution$
对于一个点，如果它的后继只有A或B，显然它不能在这条路径上。
$Sol 1$
我们把这样的点删掉。然后再判断连向它的点是否要被删掉...这样一直删，判断最后是否存在未被删掉的点。和拓扑排序差不多。
$Sol 2$
由上面的结论也可以看出，路径只能是AABB这样的环（或者AABBAABB...）（这样每个点就存在两种转移）。
AA,AB,BB,BA，这样的环我们可以通过二分图找，即对于相同字符连一条S->T的边，不同字符连一条T->S的边，最后判环。
*/
#include <cstdio>
#include <cctype>
#include <cstdlib>
#define gc() getchar()
const int N=4e5+5;

int Enum,H[N],nxt[N],to[N],vis[N];
char s[N>>1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS(int x)
{
	vis[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) DFS(v);
		else if(vis[v]==1) {puts("Yes"); exit(0);}
	vis[x]=-1;
}

int main()
{
	int n=read(),m=read(); scanf("%s",s+1);
	for(int u,v; m--; )
	{
		u=read(),v=read();
		s[u]==s[v]?(AE(u,v+n),AE(v,u+n)):(AE(u+n,v),AE(v+n,u));
	}
	for(int i=1; i<=n; ++i) if(!vis[i]) DFS(i);
	puts("No");

	return 0;
}
