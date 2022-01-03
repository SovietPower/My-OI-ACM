#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int P[7]={2,3,5,7,11,13,17};
const int mod=1e6+5;

LL Ans;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

LL FP(LL x,int k,LL p)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return t;
}
inline LL Mult(LL a,LL b,LL p)
{
	LL tmp=a*b-(LL)((long double)a/p*b+1e-8)*p;
	return tmp<0?tmp+p:tmp;
}
bool Miller_Rabin(LL x)
{
	if(x==2) return 1;
	if(!(x&1)) return 0;
	for(int i=0; i<7; ++i)
		if(x==P[i]) return 1;
		else if(!(x%P[i])) return 0;
	LL u=x-1,now,las; int t=0;
	while(!(u&1)) u>>=1,++t;
	for(int i=0; i<7; ++i)
	{
		now=FP(P[i],u,x);
		for(int j=1; j<=t; ++t)
		{
			las=now, now=Mult(now,now,x);
			if(now==1&&las!=1&&las!=x-1) return 0;
		}
		if(now!=1) return 0;
	}
	return 1;
}
LL Pho(LL n,LL delta)
{
	
	
}
void Find(LL x)
{
	if(x==1) return;
	if(Miller_Rabin(x)) {Ans=std::min(Ans,x); return;}
	LL t=x;
	while(t==x) 
	Find()
}

int main()
{
	int T=read(); LL n;
	while(T--)
		n=read(),Ans=0,Find(n),Ans==n?puts("Prime"):printf("%lld\n",Ans);
	return 0;
}
