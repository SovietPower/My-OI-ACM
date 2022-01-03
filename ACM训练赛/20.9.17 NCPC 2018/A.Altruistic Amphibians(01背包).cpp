/*
218ms	392400KB
$Description$
��$n$ֻ����Ҫ�����Ϊ$d$�ĺӣ�ÿֻ����������$w$���߶�$h$����Ծ����$l$��
����ֻ���ܿ��Ե��޺�����Ҫ��֤ÿֻ����$i$�������������������С��$w_i$����ʱ������$i$�������ܸ߶Ⱥ�$\sum h+l_i>d$��$i$���������ӡ�
ֻҪ��������ÿֻ���ܿ�������ζѵ���������ж���ֻ�����ܹ��ӡ�
$Solution$
Ӣ�������©�����ͺ�����...Ҫע�����������ϸ�С��$w_i$������������Ҫ$\leq 1e8$��
��Ϊ���ܿ�������ε��޺������Ե�����һֻ����$i$����Ϊ����$< w_i$�������ṩ$h_i$�Ĺ��ף���ֻ���ص�ȥ������ģ�
ÿֻ���ܿ���ѡ���׻򲻹��ף����Ծ���һ��01�����ˡ�����
���ܴ��ص�������$f[i]$��ʾ�ɳ���Ϊ$i$ʱ�����߶ȣ�����$k$��Ӱ��Ϊ��$f[i]=max(f[i], f[i+w_k]+h_k)$��
ע��$k$�ܸ��µ�$i$��Χֻ��$1~w_k-1$�������ܸ��Ӷ�ֻ��$O(n+\sum w_i)$��
����ͳ�ƴ𰸣�ֻҪ$f[w_k]+l_k>d$����$k$��һ���а취���ˡ���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,M=1e8+3;

int f[M];
struct Frog
{
	int l,w,h;
	bool operator <(const Frog &x)const
	{
		return w>x.w;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(),D=read(),s=0;
	for(int i=1; i<=n; ++i) A[i]=(Frog){read(),read(),read()}, s+=A[i].w;
	std::sort(A+1,A+1+n);
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		int w=A[i].w, h=A[i].h;
		if(A[i].l+f[w]>D) ++ans;
		for(int j=1; j<w && j+w<=s; ++j) f[j]=std::max(f[j],f[j+w]+h);
	}
	printf("%d\n",ans);

	return 0;
}
