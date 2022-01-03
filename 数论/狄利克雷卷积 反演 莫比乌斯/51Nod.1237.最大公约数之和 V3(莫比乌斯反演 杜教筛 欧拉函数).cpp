//http://www.cnblogs.com/SovietPower/p/8412639.html
//前缀和不要忘取模。。
#include<cstdio>
#include<cstring>
typedef long long LL;
const int N=4500000,mod=1e9+7;

int P[N>>2],cnt,phi[N+3];
LL n,sum[N+3],sum2[100000];
bool Not_P[N+3];

void Init()
{
	phi[1]=1;
	for(int i=2;i<=N;++i)
	{
		if(!Not_P[i]) P[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*P[j]<=N;++j)
		{
			Not_P[i*P[j]]=1;
			if(i%P[j]) phi[i*P[j]]=phi[i]*(P[j]-1);
			else {phi[i*P[j]]=phi[i]*P[j]; break;}
		}
	}
	for(int i=1;i<=N;++i) sum[i]=sum[i-1]+phi[i], sum[i]>=mod?sum[i]-=mod:0;
}
LL FP(LL x,LL k)
{
	LL t=1;
	for(;k;k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}
const LL inv2=FP(2,mod-2);
LL Calc(LL x)
{
	if(x<=N) return sum[x];
	else if(~sum2[n/x]) return sum2[n/x];
	LL t=x%mod, res=t*(t+1)%mod*inv2%mod;
	for(LL i=2,las;i<=x;i=las+1)
		las=x/(x/i),(res-=(las-i+1)*Calc(x/i)%mod)%=mod;
	return sum2[n/x]=(res+mod)%mod;
}

int main()
{
	Init();//scanf("%I64d",&n);
	scanf("%lld",&n);
	memset(sum2,0xff,sizeof sum2);
	LL res=0;
	for(LL i=1,las,t;i<=n;i=las+1)
		las=n/(n/i), t=n/i%mod, (res+=t*t%mod*(Calc(las)-Calc(i-1)+mod)%mod)%=mod;
	printf("%lld",res);

	return 0;
}//9800581876
