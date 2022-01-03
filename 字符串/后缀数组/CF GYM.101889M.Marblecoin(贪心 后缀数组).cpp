/*
109ms	12000KB
$Description$
有$n$个栈，每个栈$i$里有若干个数$a_{i,j}$（值域为$[1,300]$）。
现在要依次取出所有$m$个元素，设依次取出的数为$a_1,a_2,...$，最小化$a_1\times365^{m-1}+a_2\times365^{m-2}+...+a_m$（即取出的数每保留一天价值$\times365$）。
$Solution$
因为数的最大值为$300$，所以每次一定是取最小的数（就考虑一个$365$进制，后面的数再大加起来也比不过当前的权值）。
那最简单的就是拿堆来维护最小值。问题是如果当前有很多最小值，堆不能判断选哪个之后是最优的。
可以发现每次比较最小值时，比较的应该是个后缀。所以我们可以把所有后缀排序，也就是将每个栈用`301`拼在一起排序就ok了。
*/
#include <bits/stdc++.h>
#define gc() getchar()
#define mod 1000000007
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=5e5+5;

int A[N],B[N];
std::priority_queue<pr> q;
struct Suffix_Array
{
	int sa[N],rk[N],sa2[N],tm[N];
	void Build(int *a,int n)
	{
		int *x=rk,*y=sa2,m=301;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]=a[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[i]]--]=i;
		for(int k=1,p=0; k<n; k<<=1,m=p,p=0)
		{
			for(int i=n-k+1; i<=n; ++i) y[++p]=i;
			for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;

			for(int i=0; i<=m; ++i) tm[i]=0;
			for(int i=1; i<=n; ++i) ++tm[x[i]];
			for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
			for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

			std::swap(x,y), x[sa[1]]=p=1;
			for(int i=2; i<=n; ++i)
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
			if(p>=n) break;
		}
		for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	}
	void Solve(int *a,int *b,int m,int n)
	{
		LL ans=0;
		for(int i=1; i<=m; ++i) q.push(mp(-rk[b[i]],b[i]));
		for(int t=n-m; t--; )
		{
			assert(!q.empty());
			int x=q.top().second; q.pop();
			ans=(ans*365+a[x])%mod;
			if(a[x+1]<301) q.push(mp(-rk[x+1],x+1));
		}
		printf("%lld\n",ans*365%mod);
	}
}sa;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int m=read(),n=0;
	for(int i=1; i<=m; ++i,A[++n]=301)
		for(int k=(B[i]=n+1,read()); k--; A[++n]=read());
	sa.Build(A,n), sa.Solve(A,B,m,n);

	return 0;
}
