/*
93ms	7700KB
$Description$
Leha从0出发前往n。给定数组$a[]$。路上可能会有一些休息点，Leha会在这些地方停下休息。如果当前所在休息点$i$，而上一个休息点是$j$，那他会得到$a_{i-j}$的困难值（包括在n点停下也要计算，路程上所有累加）。休息点一共有$2^{n-1}$种可能分布，求所有可能中整段路程所得到的困难值的期望$e\times 2^{n-1}\mod\ 998244353$。
$Solution$
要求一个线性做法，我们尝试递推求它。
对每一个位置$i$，我们可以写出它作为休息点时得到困难值的期望：$e_i=\frac{a_1}{2}+\frac{a_2}{2^2}+\ldots+\frac{a_{i-1}}{2^{i-1}}+\frac{a_i}{2^{i-1}}$。最后一项的概率是$2^{i-1}$，因为是从0号点出发。
那么就可以得到$e_1=a_1，e_{i+1}=e_i-\frac{a_i}{2^i}+\frac{a_{i+1}}{2^i}$。
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
#define mod (998244353)
const int N=1e6+5;

int n,A[N],pw[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);

	long long now=1ll*A[1]*pw[n-1]%mod, ans=now;
	for(int i=1; i<n; ++i)
	{
		now=(now-1ll*A[i]*pw[n-1-i]%mod+1ll*A[i+1]*pw[n-1-i]%mod+mod)%mod,
		ans+=now;
	}
	printf("%I64d\n",ans%mod);

	return 0;
}
