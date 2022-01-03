/*
$Description$
飞机上有n个位置。有m个乘客入座，每个人会从前门(1)或后门(n)先走到其票上写的位置。若该位置没人，则在这坐下；若该位置有人，则按原方向向前走直到找到空座坐下。
如果有人最后仍无座，he will be angry.求有多少种安排票上位置的方案使得没有人会angry(不同票写的位置可相同，从前门/后门进是不同的)。
$Solution$
如果我们添加一个位置到0或n+1，那么不合法情况就是有人坐在了这个位置。
那么加入n+1后，可以把序列看成环，这种情况下总的方案数是[2(n+1)]^m，合法情况还是n+1没有人坐。
考虑这m个位置，因为是在环上，所以选择哪个位置的概率都是相同的！($\frac{1}{n+1}$)(因为对于选择一个位置的方案可以直接平移到另一个位置)
那么不坐在n+1位置(or任意一个)的方案数是$[2(n+1)]^m\times\frac{n+1-m}{n+1}$。
*/
#include <cstdio>
#define mod (1000000007)
typedef long long LL;

inline LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	printf("%I64d\n",1ll*FP(2,m)*FP(n+1,m-1)%mod*(n+1-m)%mod);
	return 0;
}
