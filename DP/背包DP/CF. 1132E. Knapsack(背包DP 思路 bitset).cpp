/*
31ms	0KB
$Description$
������ֱ�Ϊ$1,2,...,8$����Ʒ���������Ե�����$cnt_1,cnt_2,...,cnt_8$��$W$������Щ��Ʒ����ɵ�����Ҳ�����$W$������͡�
$cnt_i\leq 10^{16},\ W\leq 10^{18}$��
$Solution$
**����1��**
����$1,2,...,8$���Լ���ɵ���С����ͬ��Ϊ$\mathbb{lcm}(1,2,...,8)=840$�����Զ�ÿ����$i$����������ɾ����ܶ��$A_i$��$840$��ʣ�µ�$i$���Ժ�����ʣ�µ������������ж������$0\sim 839$�е���Щ���Լ�������ɶ��ٸ�$840$��ö��$0\sim 839$����Ȼ�����������һ�����ˡ�
��$f[i][j]$��ʾ��ǰ������$i$���������Ϊ$j$�������ɵ�$840$������
������ÿ������ʵ������Ϊ$\frac{840}{i}$�����������$840$�����Ӷ�$O(840\times\sum\frac{840}{i})$��

**����2��**
ͬ���ȿ���$1,2,...,8$�ܵ�����ɵ���С��ͬ��Ϊ$840$��
���������ĺ�Ϊ$sum$��ֻ�迼��$sum\gt W$��
����ÿ��$i$��$\frac{840}{i}$��$i$��������������������$0\sim 839$�е���Щ��$x$��ʣ�µ������������������$t$��$840$��ֻҪ����$x+840t\leq sum$����$t\leq\lfloor\frac{sum-x}{840}\rfloor$��
ͬ������$sum$���ǿ���ɾ��������е�$x$������$t$��$840$��ֻ������$sum-x-840t\leq W$���ɵ�$t\geq\lceil\frac{sum-x-W}{840}\rceil$������С��$t$�����Ա�����ö������ɵ�$x$���ɡ�
����������`bitset`�Ż������Ӷ�$O(\frac{8\times 840}{64})$��

ע��checkһ�±߽磺$sum-x<W$ʱ����Ϊ$sum>W$������$sum-x-W>-840$��$t_{min}=0$���Ϸ���
����$t\leq\lfloor\frac{sum-x}{840}\rfloor$���������ʵ�����С�����ֻ��������$\lfloor\frac{sum-x}{840}\rfloor<\lceil\frac{sum-x-W}{840}\rceil$������Ҫ$ans\geq 0$������$ans=sum-x-840t\geq 0$��������$t\leq\lfloor\frac{sum-x}{840}\rfloor$��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=10,M=840;

LL cnt[N];
std::bitset<M> f;

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

	f.reset(), f[0]=1;
	for(int i=1; i<=8; ++i)
		for(int t=std::min(cnt[i],1ll*M/i); t--; )
			f|=(f<<i);
	LL ans=0;
	for(int x=0; x<M; ++x)
		if(f[x])
		{
			LL t=(sum-x-W+M-1)/M;
//			if(t<=(sum-x)/M) ans=std::max(ans,sum-x-M*t);
			ans=std::max(ans,sum-x-M*t);
		}
	printf("%lld\n",ans);

	return 0;
}
