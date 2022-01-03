/*
308ms	1.0Mb
$Description$
给定$x,T$，$T$次询问，每次给定$k$求$x^k\% 998244352$。
$x,k\lt 998244352,\ T\leq 5\times10^6$。
$Solution$
**做法1：**
直接快速幂就行了。没过的是$5e6$还不用快读的（所以时限应该改0.5s）。

**做法2：**
常规以$2$为底的快速幂：$x^n=x^{\lfloor\frac{n}{2}\rfloor\times2}\times x^{n\%2}$。
同理可以改成以$3$为底：$x^n=x^{\lfloor\frac{n}{3}\rfloor\times3}\times x^{n\%3}$。（但是不能位运算优化，不如常规写法）
```cpp
int FP(LL x,int k)
{
	LL t=1;
	for(; k; k/=3,x=x*x%mod*x%mod)
		if(k%3==1) t=t*x%mod;
		else if(k%3==2) t=t*x%mod*x%mod;
	return t;
}
```
同理可以改成以任意数$k$为底：$x^n=x^{\lfloor\frac{n}{k}\rfloor\times k}\times x^{n\%k}$。
取$k=\sqrt{mod}$，则只需预处理$x^0,x^k,x^{2k},...,x^{\lfloor\frac{mod}{k}\rfloor\times k}$，以及$x^0,x^1,...,x^{k-1}$，复杂度$O(k)$。
询问就是$O(1)$的了。

细节：最好取$k=\sqrt{mod}+1$？应该问题不大但是基本都加了$1$。。
*/
#include <bits/stdc++.h>
#define pc putchar
#define MAXIN 300000
#define gc() getchar()
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define pb emplace_back
#define mod 998244352
typedef long long LL;
const int N=1e5+5,K=(int)(sqrt(mod))+1;

int A[N],B[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
//	LL t=1;
//	for(; k; k/=3,x=x*x%mod*x%mod)
//		if(k%3==1) t=t*x%mod;
//		else if(k%3==2) t=t*x%mod*x%mod;
//	return t;
}

int main()
{
	LL x=read(),xk=FP(x,K);
	A[0]=B[0]=1;
	for(int i=1,cnt=mod/K; i<=cnt; ++i) A[i]=A[i-1]*xk%mod;
	for(int i=1; i<K; ++i) B[i]=B[i-1]*x%mod;

	for(int T=read(),n; T--; )
		n=read(), printf("%d ",int(1ll*A[n/K]*B[n%K]%mod));

	return 0;
}
