/*
1620kb	184ms
不预处理:836kb	288ms
答案就是C(n,m1)*C(n-m1,m2)*C(n-m1-m2,m3)...使用扩展Lucas求解。
一个很简单的优化就是把pi,pi^ki次方存下来，因为每次分解p都是很慢的。
注意最后p不为1要把p再存下来！(质数)
预处理阶乘。不想麻烦就开longlong。
*/
#include <cmath>
#include <cstdio>
typedef long long LL;

int cnt,P[500],PK[500];
LL fac[100005];//开longlong！
LL FP(LL x,int k,LL p)
{
	LL t=1ll;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
LL Exgcd(LL a,LL b,LL &x,LL &y)
{
	if(!b) x=1,y=0;
	else Exgcd(b,a%b,y,x),y-=a/b*x;
}
LL Inv(LL a,LL p)
{
	LL x,y; Exgcd(a,p,x,y);
	return (x%p+p)%p;
}
LL Fact(LL x,LL pi,LL pk)//Calc x! % (pk=pi^ki)(x!中无pi因子)
{
	if(!x) return 1ll;
	LL res=1ll;
	if(x>=pk) res=FP(fac[pk],x/pk,pk);
	res=res*fac[x%pk]%pk;
	return res*Fact(x/pi,pi,pk)%pk;
}
int C(LL n,LL m,LL pi,LL pk,LL mod)//int
{
	if(n<m) return 0;
	fac[0]=1;
	for(int i=1; i<=pk; ++i)
		if(i%pi) fac[i]=1ll*fac[i-1]*i%pk;
		else fac[i]=fac[i-1];
	LL a=Fact(n,pi,pk),b=Fact(m,pi,pk),c=Fact(n-m,pi,pk);int k=0;
	for(LL i=n; i; i/=pi) k+=i/pi;
	for(LL i=m; i; i/=pi) k-=i/pi;
	for(LL i=n-m; i; i/=pi) k-=i/pi;
	LL res=a*Inv(b,pk)%pk*Inv(c,pk)%pk*FP(pi,k,pk)%pk;
	return res*(mod/pk)%mod*Inv(mod/pk,pk)%mod;
}
LL Solve(int n,int m,int p)
{
	if(!n) return 1ll;
	int res=0;
	for(int i=1; i<=cnt; ++i) (res+=C(n,m,P[i],PK[i],p))%=p;
	return (LL)res;
}

int main()
{
	int n,m,p,t[9];
	scanf("%d%d%d",&p,&n,&m);
	int sum=0;
	for(int i=1; i<=m; ++i) scanf("%d",&t[i]),sum+=t[i];
	if(sum>n) {puts("Impossible"); return 0;}
	int now=p;
	for(int i=2,lim=sqrt(p+0.5); i<=lim; ++i)
		if(!(now%i))
		{
			int pk=1;
			while(!(now%i)) now/=i,pk*=i;
			P[++cnt]=i, PK[cnt]=pk;
			if(now==1) break;
		}
	if(now!=1) P[++cnt]=now,PK[cnt]=now;
	LL res=1ll;
	for(int i=1; i<=m; ++i) (res*=Solve(n,t[i],p))%=p,n-=t[i];
	printf("%lld",res);

	return 0;
}
