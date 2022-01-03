/*
求长度为$n$的本质不同的子串。拼成$2n$的串，哈希后枚举即可。注意要反过来求一遍。
三哈希会T。。
*/
#include <bits/stdc++.h>
#define gc() getchar()
#define LIM 2
#define seed1 31
#define seed2 131
#define seed3 137
typedef long long LL;
typedef unsigned long long ull;
const int N=3e5+5;

int A[N];
std::set<ull> st[3];
struct Hash
{
	ull seed,pw[N],hs[N];
	ull GetHash(int l,int r)
	{
		return hs[r]-pw[r-l+1]*hs[l-1];
	}
}h[3];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	h[0].seed=31, h[1].seed=37, h[2].seed=131;
	for(int i=0; i<LIM; ++i)
	{
		h[i].pw[0]=1; ull x=h[i].seed;
		for(int j=1; j<=200000; ++j) h[i].pw[j]=h[i].pw[j-1]*x;
	}
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=1; i<=n; ++i) A[i]=read();
		for(int i=1; i<=n; ++i) A[i+n]=A[i];
		int m=n<<1;
		for(int i=0; i<LIM; ++i)
			for(int j=1; j<=m; ++j)
				h[i].hs[j]=h[i].hs[j-1]*h[i].seed+A[j];
		int res=0;
		for(int i=1; i<=n; ++i)
		{
			bool f=0;
			for(int j=0; j<LIM; ++j)
				if(!st[j].count(h[j].GetHash(i,i+n-1))) {f=1; break;}
			if(f)
			{
				++res;
				for(int j=0; j<LIM; ++j)
					st[j].insert(h[j].GetHash(i,i+n-1));
			}
		}
	
		std::reverse(A+1,A+1+n), std::reverse(A+1+n,A+1+m);
		for(int i=0; i<LIM; ++i)
			for(int j=1; j<=m; ++j)
				h[i].hs[j]=h[i].hs[j-1]*h[i].seed+A[j];
		for(int i=1; i<=n; ++i)
		{
			bool f=0;
			for(int j=0; j<LIM; ++j)
				if(!st[j].count(h[j].GetHash(i,i+n-1))) {f=1; break;}
			if(f)
			{
				++res;
				for(int j=0; j<LIM; ++j)
					st[j].insert(h[j].GetHash(i,i+n-1));
			}
		}
		for(int i=0; i<LIM; ++i) st[i].clear();
		printf("%d\n",res);
	}

	return 0;
}
