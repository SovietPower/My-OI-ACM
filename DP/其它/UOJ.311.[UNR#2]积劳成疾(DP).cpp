/*
1447ms	2052kb
�����е�ÿ��λ���ǵȼ۵ġ�ֱ����$f[i][j]$��ʾ��$i$���������У����ֵ������$j$����������ÿ����Ϊ$k$�����������ֵ�ĳ˻��ĺ͡�
��$j-1$ת�Ƶ�$j$ʱ������ö�ٵ�һ��$j$���������������ߵ�$j$��$p$λ�ã���ô�����˵���$[\max(1,p-k+1),\ \min(p,i-k+1)]$��ÿ��$k$�������$w[j]$�Ĺ��ף�Ҳ����$w[j]^{len}$��$p$���û���ֹ�$j$��������$f[p-1][j-1]$��$p$�ұ߻����ܳ���$j$��������$f[i-p][j]$��
������$f[i][j]=f[i][j-1]+\sum_{p=1}^{i}f[p-1][j-1]*w[j]^{len}*f[i-p][j]$��
ע���ʼ�������⣬$f[i][j]\ (i<k)$�ĳ�ֵ��$j^i$�������и�����������$i\geq k$��ʱ���ǻῼ���������й��ɵģ�
���Ӷ�$O(n^3)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 998244353
#define gc() getchar()
typedef long long LL;
const int N=505;
const LL LIM=1ll<<61;

int pw[N][N],f[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod) k&1&&(t=1ll*x*t%mod);
	return t;
}

int main()
{
	const int n=read(),K=read();
	for(int i=1; i<=n; ++i)
	{
		int w=read(); pw[i][0]=1;
		for(int j=1,wn=w; j<=n; ++j,w=1ll*w*wn%mod) pw[i][j]=w;
	}
	for(int i=0; i<=n; ++i) f[0][i]=1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(i<K) f[i][j]=FP(j,i);
			else
			{
				LL tmp=f[i][j-1];
				for(int p=1; p<=i; ++p)
					tmp+=1ll*f[p-1][j-1]*f[i-p][j]%mod*pw[j][std::min(p,i-K+1)-std::max(1,p-K+1)+1], tmp>=LIM&&(tmp%=mod);
				f[i][j]=tmp%mod;
			}
	printf("%d\n",f[n][n]);

	return 0;
}
