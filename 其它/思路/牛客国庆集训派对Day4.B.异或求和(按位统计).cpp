/*
97ms	1892KB
$Description$
求给定$n$及序列$A_i$，求$$\sum_{i<j<k}(A_i\oplus A_j)(A_j\oplus A_k)(A_i\oplus A_k)$$
$n\leq10^5,\ A_i\leq10^9$。

$Solution$
当然还是想拆开乘法按位统计。
考虑枚举每一个异或结果$2^x$的贡献：$$Ans=\sum_{i=0}^{29}\sum_{j=0}^{29}\sum_{k=0}^{29}2^{i+j+k}\times ?$$
乘上多少呢？现在我们需要统计$A_i\oplus A_j$在第$i$为$1$，且$A_j\oplus A_k$在第$j$位为$1$，且$A_k\oplus A_i$在第$k$位为$1$的方案数（不要弄混...$A_i$中的$i$就是下标，外面的$i$是枚举的$2^i$）。
考虑枚举$A_i$第$i$位是$0$还是$1$，设为$a$，那么$A_j$的第$i$位是$a\oplus1$；同理枚举$A_j$的第$j$位是$b$，那么$A_k$的第$j$位是$b\oplus1$；同理枚举$A_k$的第$k$位的$c$，那么$A_i$的第$k$位是$c\oplus1$。（这么打累死我了...）
那么合法的$A_i$就是，第$i$位为$a$且第$k$位为$c\oplus1$的数字，$A_j,A_k$同理...
所以记$cnt[i][j][a][b]$表示第$i$位为$a$，第$j$位为$b$的$A_x$有多少个，乘起来就OK了。
预处理$cnt$的复杂度是$O(n\log^2n)$，常数很小。最后求和的复杂度是$O(2^3\log^3n)$。
答案最后除个$6$。
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
