/*
31ms	0KB
$Description$
����һ��$n$���ڵ������$k$������ǡ��$k$����ɫ��ÿ����Ⱦɫ�������ڵ㲻ͬɫ�ķ�������
$Solution$
��$f(k)$��ʾ�����$k$����ɫȾɫ�ķ�������������̬������ν�ģ�ֻ��Ҫÿ������ɫ��ͬ�븸�ڵ㣬������$f(k)$���ڵ���$k$��ѡ�񣬷Ǹ��ڵ㶼��$k-1$��ѡ�񣬼�$f(k)=k*(k-1)^{n-1}$��
��$g(k)$��ʾǡ����$k$����ɫȾɫ�ķ�������
��**�ݳ�**�У�$g(k)=f(k)-C_k^{k-1}f(k-1)+C_k^{k-2}f(k-2)-...$��$g(k)=\sum_{i=1}^k(-1)^{k-i}f(i)$��
��**����ʽ����**����$f(k)=\sum_{i=0}^kC_k^ig(i)$������ʽ���ݵ�$g(k)=\sum_{i=0}^k(-1)^{k-i}f(i)$��
��$g(k)=\sum_{i=1}^k(-1)^{k-i}i*(i-1)^{n-1}$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define gc() getchar()
typedef long long LL;
const int N=2505;

int inv[N],C[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int FP(LL x,int k)
{
	LL res=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) res=res*x%mod;
	return res;
}

int main()
{
	const int n=read(),K=read();
	C[0]=inv[1]=1;
	for(int i=2; i<=K; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1; i<=K; ++i) C[i]=1ll*(K-i+1)*inv[i]%mod*C[i-1]%mod;

	LL res=0;
	for(int i=K,sgn=1; i; --i,sgn*=-1)
		res+=1ll*sgn*C[i]*i%mod*FP(i-1,n-1)%mod;
	printf("%lld\n",(res%mod+mod)%mod);

	return 0;
}
