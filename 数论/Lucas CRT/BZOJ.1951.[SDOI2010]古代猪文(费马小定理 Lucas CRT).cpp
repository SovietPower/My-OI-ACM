/*
1380kb	156ms
$Description$
给定N,G，求$$G^{\sum_{k|N}C_n^k}\mod\ 999911659$$ 
$Solution$
由费马小定理，可以先对次数化简，即求$\sum_{k|N}C_n^k\mod\ 99991168$，然后快速幂就可以解决。
可以把999911659分解成4个质因数，分别用Lucas定理求解然后用CRT合并即可。
要注意费马小定理成立的条件: a,p互质，即G!=mod.
*/
#include <cmath>
#include <cstdio>
#include <algorithm>
#define P (999911658)
#define mod (999911659)
typedef long long LL;
const int Pi[5]={2,3,4679,35617};

int cnt,divi[100005],r[5],fac[40000];

int FP(LL x,int k,LL p)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return (int)t;
}
inline int inv(int v,int p){
	return FP(v,p-2,p);
}
inline int C(int n,int m,int p){
	if(n<m) return 0;
	return fac[n]*inv(fac[m]*fac[n-m]%p,p)%p;
}
int Lucas(int n,int m,int p)
{
	int res=1;
	for(; m&&res; n/=p,m/=p)
		(res*=C(n%p,m%p,p))%=p;
	return res;
}
void Ex_gcd(int a,int b,int &x,int &y){
	if(!b) x=1,y=0;
	else Ex_gcd(b,a%b,y,x),y-=a/b*x;
}
int CRT()
{
	int Mi,x,y,res=0;
	for(int i=0; i<4; ++i)
	{
		Mi=P/Pi[i], Ex_gcd(Mi,Pi[i],x,y);
		x=(x%Pi[i]+Pi[i])%Pi[i], (res+=1ll*r[i]*Mi%P*x%P)%=P;
	}
	return res;
}

int main()
{
	int g,n;
	scanf("%d%d",&n,&g);
	if(g==mod) {putchar('0'); return 0;}
	for(int i=1,lim=sqrt(n); i<=lim; ++i)
		if(!(n%i))
		{
			divi[++cnt]=i;
			if(i*i!=n) divi[++cnt]=n/i;
		}
	fac[0]=1;
	for(int k=0; k<4; ++k)
	{
		for(int i=1; i<=Pi[k]; ++i) fac[i]=fac[i-1]*i%Pi[k];
		for(int i=1; i<=cnt; ++i)
			(r[k]+=Lucas(n,divi[i],Pi[k]))%=Pi[k];
	}
	printf("%d",FP(g,CRT(),mod));

	return 0;
}
