/*
对于$n=3$，$p=[1,2,3,1,3,2,2,1,3,2,3,1,3,1,2,3,2,1]$，（结合样例解释）我们猜，把排列分成$n$段，也就是以不同数开头的排列为一段，这些段的答案是一样的。（对于$n=3$就是分成$[1,2,3,1,3,2]，[2,1,3,2,3,1]，[3,1,2,3,2,1]$三段）
事实上也确实是这样，对于相邻两段比如：$2,n,...1,3,1,...,n$，它们之间也形不成合法子段。
所以我们现在只考虑怎么算以某个数开头的排列的答案（比如$[1,2,3,1,3,2]$），再乘$n$就是答案了。
我们猜是可以递推的。也就是假设我们知道$n-1$时的答案$f_{n-1}$，怎么求$f_n$？
拿$n=4$来说，考虑此时以$4$开头的排列，就是在每个$3$的排列前面加上一个$4$再拼在一起。
显然我们可以得到$3!$种合法子段。而$f_3$中的每种方案，在$n=4$时也都能和一个$4$组成合法的子段（写一写看）。但唯独最后面的$4,3,2,1$算了两次。所以有：$f_n=\left[f_{n-1}+(n-1)!-1\right]*n$。
*/
#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define mod 998244353
typedef long long LL;
typedef unsigned long long ull;
const int N=1e6+5;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
//bool Check(int *p,int n)
//{
//	for(int i=1; i<=n; ++i) if(p[i]!=i) return 0;
//	return 1;
//}
//void Work(int n)
//{
//	static int A[10000004],p[15];
//	for(int i=1; i<=n; ++i) p[i]=i;
//	int t=0;
//	do
//	{
//		for(int i=1; i<=n; ++i) A[++t]=p[i];
//		std::next_permutation(p+1,p+1+n);
//	}while(!Check(p,n));
//	int ans=0;
//	for(int i=1; i<=t; ++i)
//	{
//		int s=0;// n<=4 && printf("%d ",A[i]);
//		for(int j=i; j-i+1<=n && j<=t; ++j)
//			s+=A[j], j-i+1==n && s==n*(n+1)/2 && (++ans);
//		if(n<=5 && i+n-1<=t) printf("%lld ",s);
//	}
//	puts("");
//	printf("%d:%d t:%d\n",n,ans,t);
//}

int fac[N],A[N];

int main()
{
//	for(int i=1; i<=9; ++i) Work(i);
	int n=read();
	fac[0]=1, A[0]=1;
	for(int i=1; i<=n; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1; i<=n; ++i) A[i]=1ll*i*A[i-1]%mod+1;
	A[n]=(A[n]+mod-fac[n]-1)%mod;
	LL ans=1ll*n*fac[n]%mod-A[n];
	printf("%d\n",(int)(ans%mod+mod)%mod);

	return 0;
}
