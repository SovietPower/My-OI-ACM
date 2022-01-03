/*
4ms	2304KB
$Description$
��������һ���ˣ���$0$������$E$���ٶ�Ϊ$1$�������ϻ���$n$ֻ�ܣ�ÿֻ�ܻ��ھ������$T$ʱ�̺����һ����ҡ�����$E,T$�Լ�$n$���ܵ�����$p_i$�����ռ������н�Ҳ�����$E$�����ʱ�䡣
$n\leq10^5,\quad E,T\leq10^9$��
$Solution$
��$f_i$��ʾ��ǰ$1\sim i$ֻ�ܵĽ���Ѿ��ռ��꣬��������$p_i$�������ʱ�䡣
ÿ��һ����·��һ�ε��ܣ�Ȼ���ȥ�������ٻص�$i$��
��ô�У�$$f_i=\min\{f_j+p_i-p_j+\max\{T,\ 2(p_i-p_{j+1})\}\}$$
��ʵ$p_i-p_j$��һ�����Ǳ��ߵģ����Ǵ�$0$��$E$��������Ҫ���ǣ��������ֱ�ӼӸ�$E$������$$f_i=\min\{f_j+\max\{T,\ 2(p_i-p_{j+1})\}\}$$
���Զ����$\max$��������һ�¡�
��������ά����ӽ�ԭ��������$T>2(p_i-p_{j+1})$��λ��$j$����ô���̾���$f_i=\min\{f_j+T\}$��
�����ڲ�Ҫ����Щ����$T\leq2(p_i-p_{j+1})$��$j$��$f_i=\min\{f_j+2p_i-2p_{j+1}\}$��ֻҪ��¼��Щ$j$��$f_j-2p_{j+1}$����Сֵ�Ϳ����ˡ�
���Ӷ�$O(n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int p[N];
LL f[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),E=read(),T=read();
	for(int i=1; i<=n; ++i) p[i]=read();
	LL mn=1e16;
	for(int i=1,j=0; i<=n; ++i)
	{
		while(T<=2*(p[i]-p[j+1])) mn=std::min(mn,f[j]-2*p[j+1]), ++j;
		if(j!=i) f[i]=std::min(f[j]+T,mn+2*p[i]);
		else f[i]=mn+2*p[i];
	}
	printf("%lld\n",f[n]+E);

	return 0;
}
