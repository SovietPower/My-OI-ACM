#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

struct Node
{
	int v,p;
	bool operator <(const Node &x)const
	{
		return v==x.v?p<x.p:v>x.v;
	}
}A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	static int Ans[N];
	static bool vis[N];
	int n=read(),m=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=(Node){read(),i};
	std::sort(A+1,A+1+n);
	LL sum=0;
	for(int i=1; i<=K*m; ++i) vis[A[i].p]=1, sum+=A[i].v;
	int cnt=0;
	for(int i=1,t=0; i<=n; ++i)
		if(vis[i] && ++t==m)
			t=0, Ans[++cnt]=i;
	printf("%I64d\n",sum);
	for(int i=1; i<cnt; ++i) printf("%d ",Ans[i]);

	return 0;
}
