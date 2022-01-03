/*
308ms	1.0Mb
$Description$
����$x,T$��$T$��ѯ�ʣ�ÿ�θ���$k$��$x^k\% 998244352$��
$x,k\lt 998244352,\ T\leq 5\times10^6$��
$Solution$
**����1��**
ֱ�ӿ����ݾ����ˡ�û������$5e6$�����ÿ���ģ�����ʱ��Ӧ�ø�0.5s����

**����2��**
������$2$Ϊ�׵Ŀ����ݣ�$x^n=x^{\lfloor\frac{n}{2}\rfloor\times2}\times x^{n\%2}$��
ͬ����Ըĳ���$3$Ϊ�ף�$x^n=x^{\lfloor\frac{n}{3}\rfloor\times3}\times x^{n\%3}$�������ǲ���λ�����Ż������糣��д����
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
ͬ����Ըĳ���������$k$Ϊ�ף�$x^n=x^{\lfloor\frac{n}{k}\rfloor\times k}\times x^{n\%k}$��
ȡ$k=\sqrt{mod}$����ֻ��Ԥ����$x^0,x^k,x^{2k},...,x^{\lfloor\frac{mod}{k}\rfloor\times k}$���Լ�$x^0,x^1,...,x^{k-1}$�����Ӷ�$O(k)$��
ѯ�ʾ���$O(1)$���ˡ�

ϸ�ڣ����ȡ$k=\sqrt{mod}+1$��Ӧ�����ⲻ���ǻ���������$1$����
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
