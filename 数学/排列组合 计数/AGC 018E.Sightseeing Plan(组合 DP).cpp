/*
862ms	15744KB
https://www.cnblogs.com/SovietPower/p/9756236.html
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=2e6;

int fac[N+3],ifac[N+3];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
#define C(n,m) (1ll*fac[n+m]*ifac[n]%mod*ifac[m]%mod)//C(n+m,n)
int Calc(int x1,int y1,int sign1,int x2,int y2,int sign2,int X3,int X4,int Y3,int Y4)
{//(x1,y1)->(x2,y2)
	LL res=0;
	for(int x=X3; x<=X4; ++x)
		Add(res,1ll*(x+Y4+1)*C(x-x1,Y4-y1)%mod*C(x2-x,y2-Y4-1/*强制下一步离开y=Y4*/)%mod),
		Add(res,mod-1ll*(x+Y3)*C(x-x1,Y3-y1-1/*强制最后一步是到达y=Y3*/)%mod*C(x2-x,y2-Y3)%mod);
//		Add(res,1ll*(x-x1+Y4-y1+1)*C(x-x1,Y4-y1)%mod*C(x2-x,y2-Y4-1)%mod),
//		Add(res,mod-1ll*(x-x1+Y3-y1)*C(x-x1,Y3-y1-1)%mod*C(x2-x,y2-Y3)%mod);
	for(int y=Y3; y<=Y4; ++y)
		Add(res,1ll*(y+X4+1)*C(y-y1,X4-x1)%mod*C(y2-y,x2-X4-1)%mod),
		Add(res,mod-1ll*(y+X3)*C(y-y1,X3-x1-1)%mod*C(y2-y,x2-X3)%mod);
//		Add(res,1ll*(y-y1+X4-x1+1)*C(y-y1,X4-x1)%mod*C(y2-y,x2-X4-1)%mod),
//		Add(res,mod-1ll*(y-y1+X3-x1)*C(y-y1,X3-x1-1)%mod*C(y2-y,x2-X3)%mod);

	res%=mod;
	return sign1*sign2*res;
}

int main()
{
	fac[0]=fac[1]=1, ifac[N]=407182070;
	for(int i=2; i<=N; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=N; i; --i) ifac[i-1]=1ll*ifac[i]*i%mod;

	static int f[4][3],g[4][3];

	int x1=read(),x2=read(),x3=read(),x4=read(),x5=read(),x6=read(),
		y1=read(),y2=read(),y3=read(),y4=read(),y5=read(),y6=read();

	f[0][0]=x1-1, f[0][1]=y1-1, f[0][2]=1;
	f[1][0]=x2, f[1][1]=y1-1, f[1][2]=-1;
	f[2][0]=x1-1, f[2][1]=y2, f[2][2]=-1;
	f[3][0]=x2, f[3][1]=y2, f[3][2]=1;

	g[0][0]=x5, g[0][1]=y5, g[0][2]=1;
	g[1][0]=x6+1, g[1][1]=y5, g[1][2]=-1;
	g[2][0]=x5, g[2][1]=y6+1, g[2][2]=-1;
	g[3][0]=x6+1, g[3][1]=y6+1, g[3][2]=1;

	LL ans=0;
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			ans+=Calc(f[i][0],f[i][1],f[i][2],g[j][0],g[j][1],g[j][2],x3,x4,y3,y4);
	printf("%lld\n",(ans%mod+mod)%mod);

	return 0;
}
