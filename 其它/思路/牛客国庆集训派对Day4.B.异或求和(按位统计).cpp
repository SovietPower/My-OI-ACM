/*
97ms	1892KB
$Description$
�����$n$������$A_i$����$$\sum_{i<j<k}(A_i\oplus A_j)(A_j\oplus A_k)(A_i\oplus A_k)$$
$n\leq10^5,\ A_i\leq10^9$��

$Solution$
��Ȼ������𿪳˷���λͳ�ơ�
����ö��ÿһ�������$2^x$�Ĺ��ף�$$Ans=\sum_{i=0}^{29}\sum_{j=0}^{29}\sum_{k=0}^{29}2^{i+j+k}\times ?$$
���϶����أ�����������Ҫͳ��$A_i\oplus A_j$�ڵ�$i$Ϊ$1$����$A_j\oplus A_k$�ڵ�$j$λΪ$1$����$A_k\oplus A_i$�ڵ�$k$λΪ$1$�ķ���������ҪŪ��...$A_i$�е�$i$�����±꣬�����$i$��ö�ٵ�$2^i$����
����ö��$A_i$��$i$λ��$0$����$1$����Ϊ$a$����ô$A_j$�ĵ�$i$λ��$a\oplus1$��ͬ��ö��$A_j$�ĵ�$j$λ��$b$����ô$A_k$�ĵ�$j$λ��$b\oplus1$��ͬ��ö��$A_k$�ĵ�$k$λ��$c$����ô$A_i$�ĵ�$k$λ��$c\oplus1$������ô����������...��
��ô�Ϸ���$A_i$���ǣ���$i$λΪ$a$�ҵ�$k$λΪ$c\oplus1$�����֣�$A_j,A_k$ͬ��...
���Լ�$cnt[i][j][a][b]$��ʾ��$i$λΪ$a$����$j$λΪ$b$��$A_x$�ж��ٸ�����������OK�ˡ�
Ԥ����$cnt$�ĸ��Ӷ���$O(n\log^2n)$��������С�������͵ĸ��Ӷ���$O(2^3\log^3n)$��
��������$6$��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define mod 998244353
#define inv6 166374059
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=31;

int cnt[N][N][2][2],pw[N<<2];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Calc(int i,int j,int x,int y)
{
	if(i>j) std::swap(i,j), std::swap(x,y);
	return cnt[i][j][x][y];
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i)
	{
		int x=read();
		for(int a=0; a<N; ++a)
			for(int b=a; b<N; ++b) ++cnt[a][b][x>>a&1][x>>b&1];
	}
	pw[0]=1;
	for(int i=1; i<90; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);
	LL ans=0;
	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			for(int k=0; k<N; ++k)
				for(int a=0; a<2; ++a)
					for(int b=0; b<2; ++b)
						for(int c=0; c<2; ++c)
							ans+=1ll*pw[i+j+k]*Calc(i,k,a,c^1)%mod*Calc(i,j,a^1,b)%mod*Calc(j,k,b^1,c)%mod;
	printf("%lld\n",ans%mod*inv6%mod);

	return 0;
}
