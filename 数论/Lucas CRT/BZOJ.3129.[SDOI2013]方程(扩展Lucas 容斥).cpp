/*
1620kb	1364ms
预处理前:840kb	10552ms
如果n个未知数是正整数且没有限制，那么方案数是C(m-1,n-1).(把m个数分割成n份)
不需要把x变为非负整数解，然后去求C(n-k+1,k).(当然无所谓吧。。按标程来)
>=的限制很好做，减去即可。那么对于xi<=Ai的我们容斥，去掉x的限制，然后把x>Ai的减掉。
利用扩展Lucas计算组合数.复杂度O(2^{n1}*Ex_Lucas).
复杂度有点高了。。扩展Lucas预处理阶乘！(预处理后飞快啊，以前从来没预处理。。)
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e4+23;

int n,P,n1,n2,m,A[10],cnt,pi[666],pk[666];
LL Ans,fac[100005]/*这个开多大还是不清楚*/;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
LL FP(LL x,int k,LL p)
{
	LL t=1ll;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
void Exgcd(int a,int b,int &x,int &y)
{
	if(!b) x=1,y=0;
	else Exgcd(b,a%b,y,x),y-=a/b*x;
}
inline LL inv(int a,int p)
{
	int x,y; Exgcd(a,p,x,y);
	return (LL)((x%p+p)%p);
}
void Init_P(int p)
{
	for(int i=2,lim=sqrt(p+1); i<=lim; ++i)
		if(!(p%i))
		{
			int _pk=1;
			while(!(p%i)) p/=i,_pk*=i;
			pi[++cnt]=i, pk[cnt]=_pk;
			if(p==1) break;
		}
	if(p!=1) pi[++cnt]=pk[cnt]=p;
}
LL Fact(int n,int pi,int pk)
{
	if(!n) return 1ll;//边界！ 
	LL res=1ll;
	if(n>=pk) res=FP(fac[pk],n/pk,pk);
	(res*=fac[n%pk])%=pk;
	return res*Fact(n/pi,pi,pk)%pk;
}
LL C(int n,int m,int pi,int pk,int mod)
{
	fac[0]=1;
	for(int i=1; i<=pk; ++i)
		if(i%pi) fac[i]=fac[i-1]*i%pk;
		else fac[i]=fac[i-1];
	LL a=Fact(n,pi,pk),b=Fact(m,pi,pk),c=Fact(n-m,pi,pk);int k=0;
	for(int i=n; i; i/=pi) k+=i/pi;
	for(int i=m; i; i/=pi) k-=i/pi;
	for(int i=n-m; i; i/=pi) k-=i/pi;
	LL res=a*inv(b,pk)%pk*inv(c,pk)%pk*FP(pi,k,pk)%pk;
	return 1ll*res*(mod/pk)%mod*inv(mod/pk,pk)%mod;
}
LL Ex_Lucas(int n,int m)
{
	if(n<m) return 0ll;
	LL res=0;
	for(int i=1; i<=cnt; ++i)
		(res+=C(n,m,pi[i],pk[i],P))%=P;
	return res;
}
void DFS(int p,int cnt,int sum)
{
	if(p>n1)
		if(cnt&1) (Ans-=Ex_Lucas(m-sum-1,n-1))%=P;//前边的数减去A[i]，即满足>A[i]。
		else (Ans+=Ex_Lucas(m-sum-1,n-1))%=P;//C(m-sum-1,n-1) not C(n-sum-1,m-1)!
	else DFS(p+1,cnt,sum),DFS(p+1,cnt+1,sum+A[p]);
}

int main()
{
	int T=read(); P=read();
	Init_P(P);
	while(T--)
	{
		n=read(),n1=read(),n2=read(),m=read();
		LL tot=0;
		for(int i=1; i<=n1; ++i) A[i]=read();
		for(int i=1; i<=n2; ++i) m-=read()-1;//去下界 
		if(m<=1) {puts("0"); continue;}
		if(m==n) {puts("1"); continue;}
		Ans=0ll, DFS(1,0,0), printf("%lld\n",(Ans+P)%P);//取模！
	}
	return 0;
}
