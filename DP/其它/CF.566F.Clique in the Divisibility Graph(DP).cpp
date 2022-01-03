/*
$Description$
��������$S=\{a_1,a_2,\ldots,a_n\}$������������֮���бߵ��ҽ���$a_i|a_j$��$a_j|a_i$��
��$S$����һ���Ӽ�$S'$��������$S'$����������䶼�����ߣ�$S'$��ֻ��1����Ҳ�ǺϷ��ģ���
$n,a_i\leq 10^6$��$a_i$������ͬ��
$Solution$
��С����ѡ���Ѿ��ź��򣩣����ѡ��$a_i$������һ����һ����$a_i$�ı��������¸���һ�����¸�����������ı�������
�����뵽DP��ÿ�θ����䱶�����ɡ����Ӷ�$O(n\ln n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e6+5;

int n,A[N],f[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(); int mx=0, ans=1;
	for(int i=1; i<=n; ++i) mx=std::max(mx,A[i]=read());
	for(int i=1; i<=n; ++i)
	{
		int a=A[i], v=++f[a];
		ans=std::max(ans,v);
		for(int j=a<<1; j<=mx; j+=a) f[j]=std::max(f[j],v);
	}
	printf("%d\n",ans);

	return 0;
}
