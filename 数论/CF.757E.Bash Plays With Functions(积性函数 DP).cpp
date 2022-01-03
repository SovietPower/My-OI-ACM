//http://www.cnblogs.com/SovietPower/p/8324134.html
#include<cmath>
#include<cstdio>
#include<cctype>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e6+3,M=21,mod=1e9+7,MAXIN=1<<18;

int r,n,f[N+3][21],Primes[100000],cnt;
char IN[MAXIN],*SS=IN,*TT=IN;
bool Not_Prime[N+3];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
#define Mod(a) (a>=mod)?a-=mod:0
void Init()
{
//	Not_Prime[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!Not_Prime[i]) Primes[++cnt]=i;
		for(int j=1;j<=cnt&&Primes[j]*i<N;++j)
		{
			Not_Prime[i*Primes[j]]=1;
			if(!(i%Primes[j])) break;
		}
	}
	f[0][0]=1;//f_r(p^0)=1
	for(int i=1;i<M;++i) f[0][i]=2;
	for(int sum=0,i=1;i<N;++i,sum=0)
		for(int j=0;j<M;++j)
		{
			sum+=f[i-1][j], Mod(sum);
			f[i][j]+=sum, Mod(f[i][j]);
		}
}
int Solve(int r,int n)
{
	int ans=1,m=sqrt(n+0.5);
	for(int i=1;i<=cnt&&Primes[i]<=m;++i)
	{
		if(n%Primes[i]) continue;
		int t=0;
		while(!(n%Primes[i])) n/=Primes[i],++t;
		ans=1LL*ans*f[r][t]%mod;
	}
	if(n>1) ans=1LL*ans*f[r][1]%mod;
	return ans;
}

int main()
{
#ifndef	ONLINE_JUDGE
	freopen("757.in","r",stdin);
#endif

	Init();
	int t=read(),r,n;
	while(t--)
		r=read(),n=read(),printf("%d\n",Solve(r,n));
	return 0;
}
