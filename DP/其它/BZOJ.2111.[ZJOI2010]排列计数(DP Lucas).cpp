/*
12540kb	536ms
对于$a_i>a_{i/2}$，我们能想到小根堆。题意就是，求一个排列构成大小为n的小根堆有多少种方案。
考虑DP，f[i]表示构成大小为i的小根堆的方案数，那么如果我们确定左右子树size，则左右子树又分别是一个子问题。
那么可以得到转移方程：$f[i]=C_{i-1}^l*f[l]*f[r]$。
因为是按顺序填满二叉树的每一层，所以左子树大小是确定的啊。
P给定，可能<=n，所以要用Lucas定理求组合数。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e6+5;

int f[N],fac[N],inv[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k,int P)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%P)
		if(k&1) t=1ll*t*x%P;
	return t;
}
int Calc(int n,int m,int P)
{
	if(n<m) return 0;
	return 1ll*fac[n]*inv[m]%P*inv[n-m]%P;
}
int C(int n,int m,int P)
{
	int res=1;
	for(; n&&m; n/=P,m/=P)
		res=1ll*res*Calc(n%P,m%P,P)%P;
	return res;
}

int main()
{
	int n=read(), P=read();
	int lim=std::min(n,P-1);
	fac[0]=1;
	for(int i=1; i<=lim; ++i) fac[i]=1ll*fac[i-1]*i%P;
	inv[lim]=FP(fac[lim],P-2,P);
	for(int i=lim-1; ~i; --i) inv[i]=1ll*inv[i+1]*(i+1)%P;//inv[0]!

	f[1]=f[2]=1, f[3]=2;
	for(int i=4,l=1,now=2,mx=3,lim=1; i<=n; ++i)
	{
		if(mx<i) lim+=now, mx+=(now<<=1);
		if(l<lim) ++l;
		f[i]=1ll*C(i-1,l,P)*f[l]%P*f[i-1-l]%P;
	}
	printf("%d\n",f[n]);

	return 0;
}
