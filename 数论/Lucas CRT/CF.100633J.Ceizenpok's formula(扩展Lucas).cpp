//求C_n^k%m 
#include <cstdio>
typedef long long LL;

LL FP(LL x,LL k,LL p)
{
	LL t=1ll;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
void Exgcd(LL a,LL b,LL &x,LL &y)
{
	if(!b) x=1ll, y=0ll;
	else Exgcd(b,a%b,y,x),y-=a/b*x;
}
LL Inv(LL a,LL mod)
{
	// if(!a) return 0ll;//?
	LL x,y; Exgcd(a,mod,x,y);
	x=(x%mod+mod)%mod;//!
//	if(!x) x=mod;
	return x;
}
LL Fact(LL n,LL pi,LL pk)//factorial Calc n!%(pi^ki) (不计算pi因子 计算C()时提出)
{
	if(!n) return 1ll;
	LL ans=1ll;
	if(n/pk)
	{
		for(LL i=2; i<=pk; ++i)//每pi^ki一循环的部分 
			if(i%pi) (ans*=i)%=pk;
		ans=FP(ans,n/pk,pk);//一共n/pk个循环 
	}
	for(LL i=2; i<=n%pk; ++i)//pi^ki循环之外的部分 mod pk意义下所以i=2 to n%pk即可 
		if(i%pi) (ans*=i)%=pk;
	return ans*Fact(n/pi,pi,pk)%pk;//[n/pi]!部分 
}
LL C(LL n,LL m,LL mod,LL pi,LL pk)//Calc C_n^m%(pi^ki)
{
	if(n<m) return 0ll;
	LL a=Fact(n,pi,pk),b=Fact(m,pi,pk),c=Fact(n-m,pi,pk),k=0ll;//k:质因子pi的个数 
	for(LL i=n; i; i/=pi) k+=i/pi;//计算x!中pi因子个数:k=f(x)=f(x/pi)+x/pi 
	for(LL i=m; i; i/=pi) k-=i/pi;
	for(LL i=n-m; i; i/=pi) k-=i/pi;
	LL ans=a*Inv(b,pk)%pk*Inv(c,pk)%pk*FP(pi,k,pk)%pk;
	return ans*(mod/pk)%mod*Inv(mod/pk,pk)%mod;//这步不是很懂 大概是转到模mod意义下？
}

int main()
{
	LL n,k,mod,ans=0ll;
	scanf("%I64d%I64d%I64d",&n,&k,&mod);
	for(LL now=mod,i=2; i<=mod; ++i)
		if(!(now%i))
		{
			LL pk=1ll;
			while(!(now%i)) pk*=i, now/=i;
			(ans+=C(n,k,mod,i,pk))%=mod;
		}
	printf("%I64d",ans);

	return 0;
}
