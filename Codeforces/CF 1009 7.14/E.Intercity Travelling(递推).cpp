/*
93ms	7700KB
$Description$
Leha��0����ǰ��n����������$a[]$��·�Ͽ��ܻ���һЩ��Ϣ�㣬Leha������Щ�ط�ͣ����Ϣ�������ǰ������Ϣ��$i$������һ����Ϣ����$j$��������õ�$a_{i-j}$������ֵ��������n��ͣ��ҲҪ���㣬·���������ۼӣ�����Ϣ��һ����$2^{n-1}$�ֿ��ֲܷ��������п���������·�����õ�������ֵ������$e\times 2^{n-1}\mod\ 998244353$��
$Solution$
Ҫ��һ���������������ǳ��Ե���������
��ÿһ��λ��$i$�����ǿ���д������Ϊ��Ϣ��ʱ�õ�����ֵ��������$e_i=\frac{a_1}{2}+\frac{a_2}{2^2}+\ldots+\frac{a_{i-1}}{2^{i-1}}+\frac{a_i}{2^{i-1}}$�����һ��ĸ�����$2^{i-1}$����Ϊ�Ǵ�0�ŵ������
��ô�Ϳ��Եõ�$e_1=a_1��e_{i+1}=e_i-\frac{a_i}{2^i}+\frac{a_{i+1}}{2^i}$��
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
