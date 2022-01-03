#include <map>
#include <set>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mod 998244353
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int A[N],C[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
int Solve(int n,LL k,int b)
{
	LL now=1;
	for(int i=1+b; i<=n; i+=2)
	{
		if(A[i]!=-1) continue;
		LL coef=1;
		if(i<=2)
		{
			if(i+2<=n && A[i+2]!=-1) coef=k-1;
			else coef=k;
		}
		else if(A[i-2]==-1)
		{
			if(i+2<=n && A[i+2]!=-1)
			{
				if(i-4>0 && A[i-4]==A[i+2]) coef=k-2;
				else
				{
					int t=FP(C[i-2],mod-2);
					now=(now*t%mod*(k-1)+now*(1-t+mod)%mod*(k-2))%mod;
					coef=1;
				}
			}
			else coef=k-1;
		}
		else
		{
			if(i+2<=n && A[i+2]!=-1)
			{
				if(A[i-2]==A[i+2]) coef=k-1;
				else coef=k-2;
			}
			else coef=k-1;
		}
		if(!b) printf("i:%d coef:%lld now:%lld\n",i,coef,now);
		C[i]=coef, now=now*coef%mod;
	}
	return now;
}

int main()
{
	int n=read(),k=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i+2<=n; ++i) if(A[i]==A[i+2] && A[i]!=-1) return puts("0"),0;
	printf("%d %d\n",Solve(n,k,0),Solve(n,k,1));
//	printf("%I64d\n",1ll*Solve(n,k,0)*Solve(n,k,1)%mod);

	return 0;
}
