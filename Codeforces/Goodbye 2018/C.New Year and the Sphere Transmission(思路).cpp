/*
把$1$从序列中拿出去。
假设我们要走到$v$这个数，那么有$a*k\equiv v\ (mod\ n)$，也就是$a*k-b*n=v,\ a,b\in\mathbb{N}$。然后我们知道当且仅当$\gcd(n,k)\mid v$ 时方程有解。也就是当$\gcd(n,k)=g$时，一定会走到$g$的倍数这些数，有$\frac{n}{g}$个。同样等差数列求和就行了。
*/
#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
typedef unsigned long long ull;
const int N=1e6+5;

LL Ans[N];
std::map<LL,bool> vis;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void Work(int n)
{
	int t=0; vis.clear();
	for(int k=1; k<=n; ++k)
	{
		int p=(1+k-1)%n+1; LL s=1;
		while(p!=1) s+=p, p=(p+k-1)%n+1;
		if(!vis[s]) vis[s]=1, Ans[++t]=s, printf("(%d,%d)=%I64d\n",n,k,s);
	}
	std::sort(Ans+1,Ans+1+t);
	printf("%d\n",n);
	for(int i=1; i<=t; ++i) printf("%d ",Ans[i]);
	puts(""); puts("");
}

int main()
{
//	int n=read(),t=0;
//	for(int i=1; i<=40; ++i) Work(i); return 0;

	int n=read(),t=0;
	for(int i=1; 1ll*i*i<=n; ++i)
		if(!(n%i))
		{
			int g=i;
			Ans[++t]=(1ll*n*n-1ll*(g-2)*n)/(2*g);
			if(1ll*i*i!=n) g=n/i, Ans[++t]=(1ll*n*n-1ll*(g-2)*n)/(2*g);
		}
	std::sort(Ans+1,Ans+1+t);
	t=std::unique(Ans+1,Ans+1+t)-Ans-1;
	for(int i=1; i<=t; ++i) printf("%I64d ",Ans[i]);

	return 0;
}
