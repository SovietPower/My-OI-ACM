/*
3652kb	1036ms
$Description$
����������͵����͡�
$n\leq 10^5,\ \sum a_i\leq 10^6$��
$Solution$
�������⻹��Ҫ�ȿ��ǰ�λ����
��$s_i$��ʾǰ׺�ͣ�$s_0$=0�������赱ǰ�ǵ�$k$λ������Ҫͳ��������ڵ�$k$λΪ$1$�������ж��ٸ���������ż�ԣ���
ö�������Ҷ˵�$i$��Ȼ������Ҫͳ���ж��ٸ�$s_i-s_j$�ڵ�$k$λΪ$1$��
��$s_i$��$k$λΪ$1$ʱ��
�������$s_j$��$k$λΪ$0$����$s_j$�ĺ�$k$λ����С�ڵ���$s_i$�ĺ�$k$λ�Ų��ᷢ����λ��$s_i$��$k$λ�ϵ�$1$���ܱ�����
�������$s_j$��$k$λΪ$1$����$s_j$�ĺ�$k$λ�������$s_i$�ĺ�$k$λ��������λʹ��$s_i-s_j$�ĵ�$k$λΪ$1$��
��$s_i$��$k$λΪ$0$ʱ��ͬ������һ�¾Ϳ����ˡ�����ʵҪע��$s_i$�ǲ����ģ�����ǰ$k$λ��Ӱ������ױ��������
�������ĺ���$\leq10^6$�ġ����Զ���ÿһλ������������Ȩֵ��״����ά����$k$λΪ$0/1$��$s_i$�ĺ�$k$λ�Ϳ����ˡ�
���Ӷ�$O(n\log^2A)$��
�ƺ�������ֻ��[һ����״����]����~~����������˼��.jpg��~~���忴���£����Ҳ���������ۣ����ǿ���ֱ��������ʹ��棬����Ҫ����$s_j$��һλ��0����1...
��������[FFT]������Ȼ�����е�����ȥ������������ô��������=-=��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int sum[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct BIT
{
	#define N 1000005
	int n;
	bool t[N];
	#undef N
	#define lb(x) (x&-x)
	inline void Clear()
	{
		memset(t,0,n+1<<1);
	}
	inline void Add(int p)
	{
		for(; p<=n; p+=lb(p)) t[p]^=1;
	}
	inline bool Query(int p)
	{
		bool res=0;
		for(; p; p^=lb(p)) res^=t[p];
		return res;
	}
}T0,T1;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+read();
	int ans=0;
	for(int k=0; 1<<k<=sum[n]; ++k)
	{
		T0.Clear(), T1.Clear();
		T0.n=T1.n=1<<k, T0.Add(1);
		int s=0;
		for(int i=1,t0=1,t1=0,lim=(1<<k)-1; i<=n; ++i)
		{
			int val=sum[i]&lim;
			if(sum[i]>>k&1)
				s^=t1^T1.Query(val+1)^T0.Query(val+1), T1.Add(val+1), t1^=1;//(t1-T1.Query(val+1)+T0.Query(val+1))&1, ++t1;
			else
				s^=t0^T0.Query(val+1)^T1.Query(val+1), T0.Add(val+1), t0^=1;//(t0-T0.Query(val+1)-T1.Query(val+1))&1, ++t0;
		}
		ans+=s<<k;
	}
	printf("%d\n",ans);

	return 0;
}
