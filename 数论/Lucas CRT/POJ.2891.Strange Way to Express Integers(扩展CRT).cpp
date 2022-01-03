#include <cstdio>
#include <cctype>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

LL n,m[N],r[N];

inline LL read()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
LL Exgcd(LL a,LL b,LL &g,LL &x,LL &y)
{
	if(!b) g=a, x=1ll, y=0ll;
	else Exgcd(b,a%b,g,y,x),y-=a/b*x;
}
LL Ex_CRT()
{
	LL M=m[1],R=r[1],x,y,g,t;
	for(int i=2; i<=n; ++i)
	{
		Exgcd(M,m[i],g,x,y);
		if((r[i]-R)%g) return -1ll;
		x*=(r[i]-R)/g, t=m[i]/g, x=(x%t+t)%t;//相当于M*(x/((ri-R)/g)) ≡ g(mod mi/g)?不管了就这么理解吧 
		R+=M*x, M*=t, R%=M;
	}
	return (R%M+M)%M;
}

int main()
{
	while(~scanf("%lld",&n))
	{
		for(int i=1; i<=n; ++i) m[i]=read(),r[i]=read();
		printf("%lld\n",Ex_CRT());
	}
	return 0;
}
