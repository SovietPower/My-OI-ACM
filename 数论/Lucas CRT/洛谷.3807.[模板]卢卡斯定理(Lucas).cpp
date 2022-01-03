//想错int范围了...不要被longlong坑 
//这个范围现算阶乘比预处理快得多 
#include <cstdio>
typedef long long LL;
const int N=1e5+5;

LL n,m,p;//,fac[N+3];

LL FP(LL x,LL k,LL p)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
inline LL inv(LL x,LL p)
{
	return FP(x,p-2,p);
}
//LL C(LL n,LL m)
//{
//	if(n<m) return 0ll;
// 	return fac[n]*inv(fac[m],p)%p*inv(fac[n-m],p)%p;
//}
LL C(LL n,LL m)
{
	if(n<m) return 0ll;
	LL up=1ll,down=1ll;
	for(LL i=n-m+1; i<=n; ++i) (up*=i)%=p;
	for(LL i=2; i<=m; ++i) (down*=i)%=p;
	return up*inv(down,p)%p;
}
LL Lucas(LL n,LL m,LL p)
{
	LL ans=1;
	for(; m && ans; n/=p, m/=p)
		(ans*=C(n%p,m%p))%=p;
	return ans;
}

int main()
{
//	fac[0]=fac[1]=1;
	LL t; scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld",&n,&m,&p);
//		for(LL i=2; i<=p; ++i) fac[i]=i*fac[i-1]%p;
		printf("%lld\n",Lucas(n+m,m,p));
	}
	return 0;
}
