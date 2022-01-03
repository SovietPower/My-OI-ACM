//��C_n^k%m 
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
LL Fact(LL n,LL pi,LL pk)//factorial Calc n!%(pi^ki) (������pi���� ����C()ʱ���)
{
	if(!n) return 1ll;
	LL ans=1ll;
	if(n/pk)
	{
		for(LL i=2; i<=pk; ++i)//ÿpi^kiһѭ���Ĳ��� 
			if(i%pi) (ans*=i)%=pk;
		ans=FP(ans,n/pk,pk);//һ��n/pk��ѭ�� 
	}
	for(LL i=2; i<=n%pk; ++i)//pi^kiѭ��֮��Ĳ��� mod pk����������i=2 to n%pk���� 
		if(i%pi) (ans*=i)%=pk;
	return ans*Fact(n/pi,pi,pk)%pk;//[n/pi]!���� 
}
LL C(LL n,LL m,LL mod,LL pi,LL pk)//Calc C_n^m%(pi^ki)
{
	if(n<m) return 0ll;
	LL a=Fact(n,pi,pk),b=Fact(m,pi,pk),c=Fact(n-m,pi,pk),k=0ll;//k:������pi�ĸ��� 
	for(LL i=n; i; i/=pi) k+=i/pi;//����x!��pi���Ӹ���:k=f(x)=f(x/pi)+x/pi 
	for(LL i=m; i; i/=pi) k-=i/pi;
	for(LL i=n-m; i; i/=pi) k-=i/pi;
	LL ans=a*Inv(b,pk)%pk*Inv(c,pk)%pk*FP(pi,k,pk)%pk;
	return ans*(mod/pk)%mod*Inv(mod/pk,pk)%mod;//�ⲽ���Ǻܶ� �����ת��ģmod�����£�
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
