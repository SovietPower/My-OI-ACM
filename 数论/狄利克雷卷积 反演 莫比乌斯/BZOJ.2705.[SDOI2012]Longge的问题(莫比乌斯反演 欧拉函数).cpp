//928kb	56ms
//http://www.cnblogs.com/SovietPower/p/8745879.html
//×¢Òâd£¡
#include <cmath>
#include <cstdio>
typedef long long LL;
const int N=1<<16;

int cnt,P[N>>3];
LL n;
bool Not_p[N+3];

void Make_Table(int N)
{
	for(int i=2; i<=N; ++i)
	{
		if(!Not_p[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<=N; ++j)
		{
			Not_p[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
LL Phi(LL x)
{
	LL res=1;
	for(int i=1; i<=cnt&&1ll*P[i]*P[i]<=x; ++i)
		if(!(x%P[i]))
		{
			x/=P[i], res*=(P[i]-1);
			while(!(x%P[i])) x/=P[i], res*=P[i];
		}
	if(x>1) res*=x-1;
	return res;
}

int main()
{
	scanf("%lld",&n);
	Make_Table(sqrt(n)+1);
	LL res=0;
	int lim=sqrt(n);
	for(int i=1,lim=sqrt(n); i<=lim; ++i)
		if(!(n%i)) res+=1ll*i*Phi(n/i)+1ll*(n/i)*Phi(i);//!
	if(1ll*lim*lim==n) res-=lim*Phi(lim);
	printf("%lld",res);

	return 0;
}
