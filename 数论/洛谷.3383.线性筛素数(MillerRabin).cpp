//注：1.=1,=2,非2偶数,=p[i],整除p[i]不要忘特判 
//2.n做模数时不-1，费马小定理是%p
//3.分解后为(a^(2^t))*(a^u),不是now^u。先计算a^u方便 
#include<cstdio>
#include<cctype>
#define gc() getchar()
const int p[]={2,3,5,7,11,13,17,19};
typedef long long LL;

inline LL read()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
LL Fast_Pow(LL n,LL k,LL mod)
{
	LL t=1;
	for(;k;k>>=1,n=n*n%mod)
		if(k&1) t=t*n%mod;
	return t;
}
bool Miller_Rabin(LL n)
{
	if(n==2) return 1;
	if(!(n&1)||n==1) return 0;
	int t=0; LL u=n-1;
	while(!(u&1)) u>>=1,++t;
	LL now,las;
	for(int i=0;i<8;++i)
	{
		if(n==p[i]) return 1;
		if(!(n%p[i])) return 0;
		now=Fast_Pow(p[i],u,n);
//		now=p[i];
		for(int j=1;j<=t;++j)
		{
			las=now, now=now*now%n;
			if(now==1&&las!=1&&las!=n-1) return 0;//a^2 = 1(mod p) -> a = ±1(mod p) 
		}
		if(now!=1) return 0;
//		if(now*Fast_Pow(p[i],u,n)%n!=1) return 0;
	}
	return 1;
}

int main()
{
	int w=read(),t=read();LL n;
	while(t--)
		n=read(),puts(Miller_Rabin(n)?"Yes":"No");

	return 0;
}//1 1 5444489
