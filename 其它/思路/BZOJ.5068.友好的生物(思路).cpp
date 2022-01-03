/*
3120kb	232ms
$Description$
求$\max\{\sum_{i=1}^{k-1}(C_i*|a_{x,i}-a_{y,i}|)-C_k*|a_{x,k}-a_{y,k}|\}$
$Solution$
首先可以直接将$C_k$乘到$a_{i,k}$里。然后我们要求$\max\{\sum_{i=1}^{k-1}|a_{x,i}-a_{y,i}|-|a_{x,k}-a_{y,k}|\}$
因为只需要求某两个数的最大值，所以我们把绝对值改掉，求：$$\max\{\sum_{i=1}^{k-1}\pm(a_{x,i}-a_{y,i})-|a_{x,k}-a_{y,k}|\}$$
然后按$a_{j,k}$排序，$2^{k-1}$枚举$a_{j,i}$的符号，一定存在一种情况使得$a_{x,i}-a_{y,i}$都为正。
枚举符号后维护前缀最小值就行了。
复杂度$O(n2^{k-1})$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 350000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5;

int K;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int a[5];
	bool operator <(const Node &x)const{
		return a[K]<x.a[K];
	}
}A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read(),C[7]; K=read()-1;
	for(int i=0; i<=K; ++i) C[i]=read();
	for(int i=1; i<=n; ++i)
		for(int j=0; j<=K; ++j) A[i].a[j]=read()*C[j];

	std::sort(A+1,A+1+n); int ans=-1e8;
	for(int s=0,lim=1<<K+1; s<lim; ++s)
	{
		int mn=1e8;
		for(int i=1; i<=n; ++i)
		{
			int now=-A[i].a[K];//这个忘了== 
			for(int j=0; j<K; ++j)
				if(s>>j&1) now+=A[i].a[j];
				else now-=A[i].a[j];
			ans=std::max(ans,now-mn), mn=std::min(mn,now);
		}
	}
	printf("%d\n",ans);

	return 0;
}
