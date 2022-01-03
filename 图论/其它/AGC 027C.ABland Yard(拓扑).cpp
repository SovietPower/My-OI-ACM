/*
35ms	6656KB
$Description$
给定一张图（可能存在自环），每个点上有A或B。求是否存在一条路径，使得在上面不断走，能够得到所有AB串组合（可以重复经过点）。
$n\leq2\times10^5,m\leq2\times10^5$。
$Solution$
对于一个点，如果它的后继只有A或B（或者没有后继），显然它不能在这条路径上。
$Sol 1$
我们把这样的点删掉。然后再判断连向它的点是否要被删掉...这样一直删，判断最后是否存在未被删掉的点。和拓扑排序差不多。
$Sol 2$
由上面的结论也可以看出，路径只能是AABB这样的环（或者AABBAABB...）（这样每个点就存在两种转移）。
AA,AB,BB,BA，这样的环我们可以通过二分图找，即对于相同字符连一条S->T的边，不同字符连一条T->S的边，最后判环。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],t,q[N],cnt[N][2];
char s[N];
bool del[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	++cnt[u][s[v]-'A'], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++cnt[v][s[u]-'A'], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Del(int x)
{
	if(del[x]||(cnt[x][0]&&cnt[x][1])) return;
	q[++t]=x, del[x]=1;
}

int main()
{
	int n=read(),m=read(); scanf("%s",s+1);
	while(m--) AE(read(),read());
	for(int i=1; i<=n; ++i) Del(i);
	for(int h=1; h<=t; ++h)
	{
		int x=q[h];
		for(int i=H[x]; i; i=nxt[i]) --cnt[to[i]][s[x]-'A'],Del(to[i]);
	}
	puts(t==n?"No":"Yes");

	return 0;
}
