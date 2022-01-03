//http://www.cnblogs.com/SovietPower/p/8353374.html
//注意求单值欧拉函数 
#include<cstdio>
#include<cstring>
typedef long long LL;
const int N=1e7+3,M=10005;

int p,val[N],P[M+3],cnt;
bool NP[M+3];

void Init()
{
	for(int i=2;i<M;++i)
	{
		if(!NP[i]) P[++cnt]=i;
		for(int j=1;j<=cnt&&i*P[j]<M;++j)
		{
			NP[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
int FP(LL x,int k,LL p)
{
	LL t=1;
	for(;k;k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
int Get_Phi(int n)//O(sqrt(n))求单值欧拉函数 
{
	LL res=1;int mod=n;
	for(int t,i=1;i<=cnt&&P[i]*P[i]<=n;++i)
		if(!(n%P[i]))
		{
			n/=P[i], (res*=(P[i]-1))%=mod;
			while(!(n%P[i])) n/=P[i],(res*=P[i])%=mod;
		}
	if(n>1) (res*=n-1)%=mod;//别忘n本身可能是个质数 
	return res;
}
int Calc(int n)
{
	if(val[n]!=-1) return val[n];
	int t=Get_Phi(n);
	return val[n]=FP(2,Calc(t)+t,n);
}

int main()
{
	Init();
	int t; memset(val,0xff,sizeof val), val[1]=0;
	for(scanf("%d",&t);t--;)
	{
		scanf("%d",&p);
		printf("%d\n",Calc(p));
	}
	return 0;
}
