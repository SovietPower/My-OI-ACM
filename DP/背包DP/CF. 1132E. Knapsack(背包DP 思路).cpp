/*
46ms	100KB
$Description$
有体积分别为$1,2,...,8$的物品，给定各自的数量$cnt_1,cnt_2,...,cnt_8$和$W$，求这些物品能组成的最大且不超过$W$的体积和。
$cnt_i\leq 10^{16},\ W\leq 10^{18}$。
$Solution$
**做法1：**
考虑$1,2,...,8$能自己组成的最小的相同数为$\mathbb{lcm}(1,2,...,8)=840$，所以对每个数$i$，可以先组成尽可能多的$A_i$个$840$，剩下的$i$可以和其它剩下的数做背包，判断能组成$0\sim 839$中的那些数以及还能组成多少个$840$。枚举$0\sim 839$，显然就能组成任意一个数了。
令$f[i][j]$表示当前考虑了$i$个数，体积为$j$最多能组成的$840$个数。
这样做每个数的实际数量为$\frac{840}{i}$，背包总体积$840$，复杂度$O(840\times\sum\frac{840}{i})$。

**做法2：**
同样先考虑$1,2,...,8$能单独组成的最小相同数为$840$。
记所有数的和为$sum$，只需考虑$sum\gt W$。
对于每个$i$用$\frac{840}{i}$个$i$做背包，可以求出能组成$0\sim 839$中的哪些数$x$，剩下的数可以用来组成任意$t$个$840$，只要满足$x+840t\leq sum$，即$t\leq\lfloor\frac{sum-x}{840}\rfloor$。
同样对于$sum$我们可以删掉任意可行的$x$和任意$t$个$840$，只需满足$sum-x-840t\leq W$，可得$t\geq\lceil\frac{sum-x-W}{840}\rceil$，即最小的$t$。所以背包后枚举能组成的$x$即可。
背包可以用`bitset`优化，复杂度$O(\frac{8\times 840}{64})$。

注意check一下边界：$sum-x<W$时，因为$sum>W$，所以$sum-x-W>-840$，$t_{min}=0$，合法。
还有$t\leq\lfloor\frac{sum-x}{840}\rfloor$这个条件其实不用判。问题只可能在于$\lfloor\frac{sum-x}{840}\rfloor<\lceil\frac{sum-x-W}{840}\rceil$，但若要$ans\geq 0$，则有$ans=sum-x-840t\geq 0$，即已有$t\leq\lfloor\frac{sum-x}{840}\rfloor$。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=10,M=840;

LL cnt[N],f[N][M+5];

inline LL read()
{
	LL now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	LL W=read(),sum=0;
	for(int i=1; i<=8; ++i) cnt[i]=read(),sum+=cnt[i]*i;
	if(sum<=W) return printf("%lld\n",sum),0;

	memset(f,0xff,sizeof f);
	f[0][0]=0;
	for(int i=1; i<=8; ++i)
		for(int j=0; j<M; ++j)
		{
			LL val=f[i-1][j];
			if(val==-1) continue;
			for(int k=std::min(cnt[i],1ll*M/i); ~k; --k)
			{
				int t=(j+k*i)/M,v=(j+k*i)%M;
				f[i][v]=std::max(f[i][v],val+t+(cnt[i]-k)/(M/i));
			}
		}
	LL ans=0,val;
	for(int i=0; i<M; ++i)
		if(~(val=f[8][i]) && i<=W)
			ans=std::max(ans,i+std::min(val,(W-i)/M)*M);
	printf("%lld\n",ans);

	return 0;
}
