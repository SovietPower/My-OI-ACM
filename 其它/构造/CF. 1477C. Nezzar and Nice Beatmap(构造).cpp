/*
109ms	100KB
$Description$
给定平面上$n$个不同的点，求一个排列$P_i$，使得$\forall i\in[1,n-2]$，$P_i,P_{i+1},P_{i+2}$依次相连构成的角为锐角。无解输出-1。
$n\leq 5000$。
$Solution$
连边和判断锐角，考虑**大角对大边**，只需要让$|P_{i}P_{i+2}|$不是最长边即可。所以直接令$|P_iP_{i+1}|>|P_iP_{i+2}|$，即$i$每次向最远的点连边，一定可以满足$|P_iP_{i+2}|$不是最长边，这样一定有解。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb push_back
#define Dis(i,j) 1ll*(x[i]-x[j])*(x[i]-x[j])+1ll*(y[i]-y[j])*(y[i]-y[j])
typedef long long LL;
const int N=5005;

int x[N],y[N],vis[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) x[i]=read(),y[i]=read();
	printf("%d",1);
	for(int now=1,i=2; i<=n; ++i)
	{
		vis[now]=1;
		LL mx=0; int p=0;
		for(int j=1; j<=n; ++j)
			if(!vis[j] && Dis(now,j)>mx) mx=Dis(now,j), p=j;
		printf(" %d",now=p);
	}

	return 0;
}
