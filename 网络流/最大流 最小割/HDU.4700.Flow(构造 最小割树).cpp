/*
93MS	1316K
$Description$
给定$n$以及$n$个点任意两点之间的最大流，求一张无向图满足给定条件。
$n\leq100$。
$Solution$
有些类似[最小割树]。
我们可以构造一棵树，只要让树上的边成为割边，非树边容量为$0$就可以了。
每次找到当前点集中流量最小的边，设其流量为$c$，然后根据$c$将点集分成两个集合，满足两个集合之间的点对的最大流是$c$，集合内部的点的最大流$>c$。对于集合内部继续递归做即可。
划分集合的时候也是可以先随便找一个点$x$划分到左集合，将$flow[x][i]>c$的点$i$分到左集合，其余的点分到右集合，再判断一下左右集合是否满足之间的最大流$=c$即可。注意右集合为空时也无解（$x\dfrac{>c}{}u\dfrac{\ c\ }{}v\dfrac{>c}{}x$，这样显然不行）。
复杂度$O(n^3)$？
注意$A[i]$别写成$i$。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=105;

int A[N],tmp[2][N],f[N][N],W[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool DFS(int l,int r)
{
	if(l==r) return 1;
	int mn=1<<30,cnt[2]={0,1}; tmp[1][1]=A[l];
	for(int i=l; i<=r; ++i)
		for(int j=i+1; j<=r; ++j) mn=std::min(mn,f[A[i]][A[j]]);
	for(int s=A[l],i=l+1,t; i<=r; ++i) t=f[s][A[i]]>mn, tmp[t][++cnt[t]]=A[i];
	if(!cnt[0]) return 0;
	for(int i=1; i<=cnt[0]; ++i)
		for(int j=1; j<=cnt[1]; ++j)
			if(f[tmp[0][i]][tmp[1][j]]!=mn) return 0;
	for(int i=l,t=1; t<=cnt[0]; ++i) A[i]=tmp[0][t++];
	for(int i=l+cnt[0],t=1; i<=r; ++i) A[i]=tmp[1][t++];
	W[A[l]][A[r]]=mn, W[A[r]][A[l]]=mn;
	return DFS(l,l+cnt[0]-1)&&DFS(l+cnt[0],r);
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		memset(W,0,sizeof W);
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j) f[i][j]=read();
		for(int i=1; i<=n; ++i) A[i]=i;
		if(!DFS(1,n)) puts("NO");
		else
		{
			puts("YES");
			for(int i=1; i<=n; ++i)
				for(int j=(W[i][i]=-1,1); j<=n; ++j) printf("%d%c",W[i][j]," \n"[j==n]);
		}
	}

	return 0;
}
