/*
20760kb	320ms
$Description$
给定一个字符串$s$，求一个最短的字符串$t$满足，将$t$拼接多次后，可以得到$s$。拼接是指，可以将$t$放在当前串的任意位置，但要保证对应位置相同。（不太会说，看样例吧...）
$|s|\leq5\times10^5$。
$Solution$
首先$t$既是$s$的前缀也是$s$的后缀，即$s$的$border$、$border$的$border$...
考虑$KMP$建出$fail$树，那么$t$是$n$到根节点路径上的某个节点。考虑路径上怎样的节点是合法的。
$s$中能够放$t$的位置$i$满足，$t$是$s[1...i]$的$border$或者$border$的$border$...即在$fail$树中$i$在$t$的子树内。对于所有$i$，要满足相邻的$i$之间的最大间距不超过$|t|$，这样$t$就是合法的。
注意到从根节点到$n$的路径中，要维护的这个最大间距是递减的（每次删掉若干棵子树中的$i$）。那么删除一个位置时，用链表维护下相邻位置的最大间距就可以了。
还有一个更简单的DP方法，看洛谷题解吧，~~我还不是很理解就不写了~~。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5e5+5;

int fail[N],H[N],nxt[N],way[N],L[N],R[N],Max;
char s[N];

inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
void Delete(int x)
{
	L[R[x]]=L[x], R[L[x]]=R[x], Max=std::max(Max,R[x]-L[x]);
	for(int v=H[x]; v; v=nxt[v]) if(v!=way[x]) Delete(v);
}

int main()
{
	scanf("%s",s+1); int n=strlen(s+1);
	for(int i=2,j=0; i<=n; ++i)
	{
		while(j&&s[i]!=s[j+1]) j=fail[j];
		fail[i]=s[i]==s[j+1]?++j:0;
	}
	for(int i=1; i<=n; ++i) L[i]=i-1, R[i]=i+1, AE(fail[i],i);
	for(int x=n; x; x=fail[x]) way[fail[x]]=x;
	int x=0;
	for(Max=1; Max>x; x=way[x]) Delete(x);
	printf("%d\n",x);

	return 0;
}
