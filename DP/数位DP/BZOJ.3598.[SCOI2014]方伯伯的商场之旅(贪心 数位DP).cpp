/*
49592kb	404ms
先考虑，对于确定的一个数，怎样移动代价最少（或者移到哪个位置最优）？
假设我们都移到下标1位置（设集合点为1），那么移动到下标2与1相比代价差为：下标<1的石子数和-下标>1的石子数和。
如果它为负，那么把移到1的代价加上它，令集合点变为2...这样一直改变集合点，直到 下标<p的石子数和 >= 下标>p的石子数和。那么移到p就是最优的。
这样感觉很对。怎么证明？
我们发现式子左边其实就是前缀和，右边是后缀和。因为石子数非负，所以随着p移动，前缀和是递增的，后缀和递减。
即如果出现 前缀和 >= 后缀和 的情况，前缀和就永远大于等于后缀和了。
那么我们对[l,r]的所有数都进行这个贪心。
首先我们要算出所有数集合到1的代价和。这个可以用数位DP算出（递推数的个数，用个数求和）。
然后枚举p=2~n位，我们可以求 以p为分界，前缀数位和 小于 后缀数位和 且 在[0,r] 的数的个数。其中每个数会减少的代价就是前缀和-后缀和。
因为数位和最多差不多是230，可以直接枚举这两个状态。同样数位DP。
f[i][j][k][0/1]表示当前到第i位，总数位和为j，p位之前的数位和为k，是否到上界，的数的个数。
另外还可以直接减掉k那一维。。
记忆化就好写的多了（还快）。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=52,M=245;

int A[N];
LL g[N][2],sum[N][2],f[N][M][M][2];

LL Calc(LL x,int base)
{
	int n=0;
	for(; x; x/=base) A[++n]=x%base;
	std::reverse(A+1,A+1+n);//
	printf("%d %d\n",base,n*(base-1));

	memset(g,0,sizeof g), memset(sum,0,sizeof sum);
	g[0][1]=1;
	for(int i=0; i<n; ++i)//好像还是从0方便。。
	{
		LL v=g[i][1]; int ai=A[i+1];
		g[i+1][1]+=v, sum[i+1][1]=sum[i][1]+v*i*ai;
		for(int j=0; j<ai; ++j) g[i+1][0]+=v, sum[i+1][0]+=sum[i][1]+v*i*j;
		v=g[i][0];
		for(int j=0; j<base; ++j) g[i+1][0]+=v, sum[i+1][0]+=sum[i][0]+v*i*j;
	}

	LL ans=sum[n][0]+sum[n][1];
	for(int p=1; p<n; ++p)
	{
		f[0][0][0][1]=1;
		for(int i=0; i<n; ++i)
		{
			int ai=A[i+1];
			if(i+1<=p)
			{
				LL v;
				for(int j=0,lim=i*(base-1); j<=lim; ++j)
				{
					if(v=f[i][j][j][1])//好不直观。。
					{
						f[i+1][j+ai][j+ai][1]+=v;//+=
						for(int k=0; k<ai; ++k) f[i+1][j+k][j+k][0]+=v;
					}
					if(v=f[i][j][j][0])
						for(int k=0; k<base; ++k) f[i+1][j+k][j+k][0]+=v;
				}
			}
			else
			{
				LL v;
				for(int j=0,lim=i*(base-1); j<=lim; ++j)
					for(int k=0,lim2=p*(base-1); k<=lim2;  ++k)
					{
						if(v=f[i][j][k][1])
						{
							f[i+1][j+ai][k][1]+=v;
							for(int l=0; l<ai; ++l) f[i+1][j+l][k][0]+=v;
						}
						if(v=f[i][j][k][0])
							for(int l=0; l<base; ++l) f[i+1][j+l][k][0]+=v;
					}
			}
		}
		for(int i=0,lim=p*(base-1); i<=lim; ++i)//pre
			for(int j=i+1,lim2=n*(base-1); i+j<=lim2; ++j)//suf
				ans+=(i-j)*(f[n][i+j][i][0]+f[n][i+j][i][1]);
		for(int i=1; i<=n; ++i)
			for(int j=0,lim=i*(base-1); j<=lim; ++j)
				for(int k=0,lim2=p*(base-1); k<=lim2; ++k)
					f[i][j][k][0]=0, f[i][j][k][1]=0;
	}
	return ans;
}

int main()
{
	LL L,R; int K; scanf("%lld%lld%d",&L,&R,&K);
	printf("%lld\n",Calc(R,K)-Calc(L-1,K));
	return 0;
}
