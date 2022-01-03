/*
13516kb	6784ms
错位排列$D_n=(n-1)*(D_{n-1}+D_{n-2})$，表示$n$个数都不在其下标位置上的排列数。
那么题目要求的就是$C_n^m*D_{n-m}$。
阶乘分母部分的逆元可以线性处理，不需要扩欧。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define MAXIN 1000000
#define p (1000000007)
typedef long long LL;
const int N=1e6+5;

int inv_fac[N],fac[N],D[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Init()
{
	D[1]=0, inv_fac[0]=inv_fac[1]=fac[0]=fac[1]=D[0]=D[2]=1;
	for(int i=2; i<N; ++i){
		inv_fac[i]=1ll*(p-p/i)*inv_fac[p%i]%p,
		fac[i]=1ll*fac[i-1]*i%p;
	}
	for(int i=3; i<N; ++i) inv_fac[i]=1ll*inv_fac[i]*inv_fac[i-1]%p;
	for(int i=3; i<N; ++i) D[i]=1ll*(i-1)*(D[i-1]+D[i-2])%p;
}

int main()
{
	Init();
	int T=read(),n,m;
	while(T--)
		n=read(),m=read(),printf("%lld\n",(1ll*fac[n]*inv_fac[m]%p*inv_fac[n-m]%p*D[n-m]%p));

	return 0;
}
