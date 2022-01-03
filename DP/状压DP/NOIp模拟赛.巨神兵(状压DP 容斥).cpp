/*
$Description$
给定$n$个点$m$条边的有向图，求有多少个边集的子集，构成的图没有环。
$n\leq17$。
$Solution$
问题也等价于，用不同的边集构造DAG，有多少种合法方案。我们考虑怎么构造DAG使得方案不重不漏。
我们知道一个DAG的拓扑序是唯一确定的。所以我们按照拓扑序每次转移一个点集。
$f[s][s']$表示 构造 已经选择的点集为s，当前最后一层点集为s'的DAG 的方案数。
转移时枚举不在s中的子集k，k合法首先要满足s'与k中所有点有边。
然后设s^s'与k中某点的连边有$cnt1_i$条，s'与k中该点的连边有$cnt2_i$条，则该点的合法方案数为$2^{cnt1_i}*(2^{cnt2_i}-1)$。
$f[s|k][k]=Σf[s][s']*∏2^{cnt1_i}*(2^{cnt2_i}-1)$。
复杂度$O(4^n*m)$。
考虑减掉第二维。直接枚举当前点集i，然后枚举补集的子集j。只要还是按层加入节点就能保证是DAG。
i,j之间可以不存在边，设i连向j的边有cnt条，则$f[i|j]+=f[i]*2^j$？
当然没这么简单。容易发现i|j可以由很多组i,j构成。所以加个容斥，容斥系数是(-1)^{sz[j]+1}。
不是很懂这个容斥系数。。是加1个点的然后减去还可以由两个点的...？
复杂度$O(3^nm)$，可以优化到$O(3^n+2^nm)$（不管了）。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define In(x,s) (s>>x&1)
#define gc() getchar()
#define mod 1000000007
const int N=20,S=(1<<17)+3;

int n,m,pw[N*N],mp[N][N],num[N][S],f[S];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Calc(int s)
{
	int res=0;
	for(; s; s>>=1) res+=s&1;
	return res;
}

int main()
{
	n=read(),m=read();
	pw[0]=1;
	for(int i=1; i<=m; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);
	for(int i=1; i<=m; ++i) mp[read()-1][read()-1]=1;
	int all=(1<<n)-1;
	for(int s=0; s<=all; ++s)
		for(int v=0; v<n; ++v)
			if(In(v,s))
				for(int x=0; x<n; ++x) num[x][s]+=mp[x][v];
	f[0]=1;
	for(int i=0; i<=all; ++i)
	{
		if(!f[i]) continue;
		int rest=all^i;
		for(int j=rest; j; j=(j-1)&rest)
		{
			int sz=Calc(j), cnt=0;
			for(int k=0; k<n; ++k)
				if(In(k,i)) cnt+=num[k][j];
			if(sz&1) f[i|j]+=1ll*f[i]*pw[cnt]%mod, f[i|j]>=mod&&(f[i|j]-=mod);
			else f[i|j]-=1ll*f[i]*pw[cnt]%mod-mod, f[i|j]>=mod&&(f[i|j]-=mod);
		}
	}
	printf("%d\n",f[all]);

	return 0;
}
