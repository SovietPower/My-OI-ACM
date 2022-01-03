/*
1951ms	32664kb
树状数组做法：
基本思路不变（一维扩展到多维，最后一列单独维护）。
对于每一行（除最后一列），有影响的只是对这一行的操作。
那么对于某一行，可以算出某次操作删掉的是第几次补在这一行后的数（或者是原数列中的哪个数）。同样是查k大值计算。
因为总共只会有q个补在某行后面的数，可以直接用vector存每一行每次补在后面的数。最后一列一样。
求k大值（第k个存在的数）线段树平衡树都行。二分+树状数组也可以。
因为不能动态开点开n+1棵树状数组，所以离线，每次对每一行用树状数组求，然后改初始状态。
最后对最后一列也求一遍即可。
复杂度$O(n\log^2n)$。但常数小啊。（但还是比线段树慢？）
我竟然用边表存每一行的询问mdzz（顺序会反）。
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int qx[N],qy[N],pos[N];
std::vector<LL> e[N],v[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct BIT
{
	int n,t[N*4];//2n! 再开一倍因为预处理 
	#define lb(x) (x&-x)
	inline void Add(int p)
	{
		for(; p<=n; p+=lb(p)) ++t[p];
	}
	inline void Delete(int p)
	{
		for(; p<=n; p+=lb(p)) --t[p];
	}
	inline int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res;
	}
	void Init(int nn)
	{
		n=nn, ++t[n];
		for(int i=1; i<n; ++i) ++t[i]/*init:a[i]=1*/, t[i+lb(i)]+=t[i];//i+lb(i)>n
	}
	inline int Kth(int k)
	{
		int l=1,r=n,mid;
		while(l<r)
			if(Query(mid=l+r>>1)<k) l=mid+1;
			else r=mid;
		return l;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),q=read();
	for(int i=1; i<=q; ++i)
	{
		qx[i]=read(),qy[i]=read();
		if(qy[i]!=m) e[qx[i]].push_back(i);
	}

	T.Init(std::max(n,m)+q);
	for(int x=1; x<=n; ++x)
	{
		for(int i=0,j,l=e[x].size(); i<l; ++i)
			j=e[x][i], T.Delete(pos[j]=T.Kth(qy[j]));
		for(int i=0,l=e[x].size(); i<l; ++i) T.Add(pos[e[x][i]]);
	}
	for(int i=1,x,y,p; i<=q; ++i)
	{
		x=qx[i],y=qy[i];
		T.Delete(p=T.Kth(x));
		LL ans= p<=n?(LL)p*m:v[0][p-n-1];
		if(y!=m)
		{
			v[x].push_back(ans);
			ans= pos[i]<m?(1ll*(x-1)*m+pos[i]):v[x][pos[i]-m];
		}
		v[0].push_back(ans);
		printf("%lld\n",ans);
	}

	return 0;
}
