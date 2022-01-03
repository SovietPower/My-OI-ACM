/*
12540kb	536ms
����$a_i>a_{i/2}$���������뵽С���ѡ�������ǣ���һ�����й��ɴ�СΪn��С�����ж����ַ�����
����DP��f[i]��ʾ���ɴ�СΪi��С���ѵķ���������ô�������ȷ����������size�������������ֱַ���һ�������⡣
��ô���Եõ�ת�Ʒ��̣�$f[i]=C_{i-1}^l*f[l]*f[r]$��
��Ϊ�ǰ�˳��������������ÿһ�㣬������������С��ȷ���İ���
P����������<=n������Ҫ��Lucas�������������
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
