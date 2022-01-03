/*
61ms	2400KB
任意一对总要有个满足的，任找一对分解质因数就可以了。
分解质因数的过程很zz。。不用筛直接枚举到sqrt(n)就行了。。
分解完后要判一次。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,A[N],B[N],P[N],cnt;
bool not_P[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Make_Table(int n)
{
	for(int i=2; i<=n; ++i)
	{
		if(!not_P[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<=n; ++j)
		{
			not_P[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
bool Check(int x)
{
	for(int i=1; i<=n; ++i) if(A[i]%x && B[i]%x) return 0;
	return 1;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read(), B[i]=read();
	Make_Table(sqrt(std::max(A[1],B[1])));
	int now=A[1];
	for(int i=1; i<=cnt&&P[i]<=now; ++i)
		if(!(now%P[i]))
		{
			if(Check(P[i])) return printf("%d\n",P[i]),0;
			if(P[i]*P[i]!=now && now!=P[i] && Check(now/P[i])) return printf("%d\n",now/P[i]),0;
			while(!(now%P[i])) now/=P[i];
		}
	if(now!=1 && Check(now)) return printf("%d\n",now),0;

	now=B[1];
	for(int i=1; i<=cnt&&P[i]<=now; ++i)
		if(!(now%P[i]))
		{
			if(Check(P[i])) return printf("%d\n",P[i]),0;
			if(P[i]*P[i]!=now && now!=P[i] && Check(now/P[i])) return printf("%d\n",now/P[i]),0;
			while(!(now%P[i])) now/=P[i];
		}
	if(now!=1 && Check(now)) return printf("%d\n",now),0;
	puts("-1");

	return 0;
}
