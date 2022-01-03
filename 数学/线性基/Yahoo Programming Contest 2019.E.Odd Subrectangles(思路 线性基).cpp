/*
7ms	896KB
$Description$
����һ��$n\times m$��$01$����������ѡ��$r$�С�$c$�У���$2^{n+m}$�ַ�������ʹ����$r$��$c$�еĽ���λ�õ�$r\times c$�����ĺ�Ϊ�������ķ������ж��١�
$n,m\leq300$��

$Solution$
�����Ѿ�ȷ����ѡ��ĳЩ�У�Ȼ���ÿһ��$m$��������һ��$m$λ����������
�����Щ������Ϊ$0$������ôѡ��Ҳ���С�
����ÿһ�������Щ����$0$����$1$��ȷ���ġ�������$a$������Ϊ$1$��$b$������Ϊ$0$��$a+b=m$������Ҫ��$a$��ѡ������������$b$�����ѡ����ô��������$2^{a-1}\cdot2^b=2^{m-1}$����$n$��ѡ�����������ķ���������$C_n^1+C_n^3+C_n^5+...=\frac{2^n}{2}=2^{n-1}$����
Ҳ���ǲ�������ôѡ��ֻҪ���Ͳ�Ϊ$0$���о���$2^{m-1}$�ַ�����
���Ͳ�Ϊ$0$�ķ�����=$2^n-$����Ϊ$0$�ķ�����������Ϊ$0$�ķ��������������Ի�����$2^{n-r}$��$n$��Ԫ��������$r$�Ǿ�����ȣ�Ҳ�������Ի��е�Ԫ�ظ����������Դ𰸾���$(2^n-2^{n-r})\cdot2^{m-1}$��
�������Ի����뻹��һ���ģ���һ�п���$m$λ���ͺ��ˡ�
���Ӷ�$O(n^3)$��$O(\frac{n^3}{w})$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 998244353
typedef long long LL;
const int N=305;

int A[N][N],B[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) A[i][j]=read();
	int r=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(A[i][j])//x>>j&1
			{
				if(B[j][j]) for(int k=j; k<=m; ++k) A[i][k]^=B[j][k];
				else
				{
					for(int k=j; k<=m; ++k) B[j][k]=A[i][k];
					++r; break;
				}
			}
	printf("%d\n",(FP(2,n+m-1)+mod-FP(2,n-r+m-1))%mod);

	return 0;
}
