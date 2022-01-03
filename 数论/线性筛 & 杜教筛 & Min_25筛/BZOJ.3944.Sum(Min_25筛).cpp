/*
3128kb	4632ms
https://www.cnblogs.com/SovietPower/p/10104516.html
*/
#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=47000<<1;

int n,m,Sqr,cnt,P[N>>2],h[N],w[N];
LL sp[N],g[N];

inline int ID(int x)
{
	return x<=Sqr?x:m-n/x+1;
}
LL S_Phi(int x,int y)
{
	if(x<=1||P[y]>x) return 0;
	LL res=g[ID(x)]-sp[y-1]+y-1;
	for(int i=y; i<=cnt&&P[i]*P[i]<=x; ++i)//p*p当然<=n 
		for(LL p=P[i],p1=p,t=p-1; 1ll*p1*p<=x/*这里会爆int!*/; p1*=p,t*=p)
			res+=1ll*(S_Phi(x/p1,i+1)+p)*t;//x/p1不是n/p1!
	return res;
}
int S_Mu(int x,int y)
{
	if(x<=1||P[y]>x) return 0;
	int res=h[ID(x)]+y-1;//-h!
	for(int i=y; i<=cnt&&P[i]*P[i]<=x; ++i)
		res-=S_Mu(x/P[i],i+1);
	return res;
}
void Solve()
{
	scanf("%d",&n), Sqr=sqrt(n);
	if(!n) return (void)puts("0 0");
	cnt=m=0;
	for(LL i=1; i<=n; i=w[m]+1ll)
		w[++m]=n/(n/i), g[m]=(1ll*w[m]*((LL)w[m]+1)>>1)-1, h[m]=w[m]-1;//(LL)w[m]+1!!!
	for(int j=2; j<=Sqr; ++j)
		if(g[j]!=g[j-1])
		{
			P[++cnt]=j, sp[cnt]=sp[cnt-1]+j; int lim=j*j;
			for(int i=m; lim<=w[i]; --i)
			{
				int k=ID(w[i]/j);
				g[i]-=1ll*j*(g[k]-sp[cnt-1]);//不取模。。
				h[i]-=h[k]-cnt+1;
			}
		}
	for(int i=1; i<=m; ++i) g[i]-=h[i], h[i]=-h[i];
	printf("%lld %d\n",S_Phi(n,1)+1,S_Mu(n,1)+1);//f(1)!
}

int main()
{
	int T;
	for(scanf("%d",&T); T--; Solve());
	return 0;
}
