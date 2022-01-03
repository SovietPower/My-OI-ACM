/*
3226ms	4692kb
$Description$
选最多$m$个物品，使得它们的$(Σvi)^{dv}-(s_{max}-s_{min})^{du}$最大。
$Solution$
先把物品按s排序就可以直接判断后一项。
我们发现当要判断的区间的长度<=m时，区间内的所有数都要选(后一项都确定了)。
当区间长度>m时，自然是选v最大的m个。可以用链表把v最小的逐个删去。
发现删掉x的话我们只需要用x附近m个数更新答案。因为如果区间更大，也是会在删掉更多数的时候更新答案。
复杂度$O(nm)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define fir first
#define val second
#define mp std::make_pair
#define pr std::pair<int,int>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int n,m,ds,dv;
LL Ans;
pr A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool cmp(int a,int b){
	return A[a].val<A[b].val;
}
inline void Update(LL sv,LL ss)
{
	if(ds) ss*=ss; if(dv) sv*=sv;
	Ans=std::max(Ans,sv-ss);
}
void Solve1()
{
	for(int i=1; i<=n; ++i)
		for(int j=i,sum=0,si=A[i].fir,lim=std::min(i+m-1,n); j<=lim; ++j)
			sum+=A[j].val, Update(sum,A[j].fir-si);
}
void Solve2()
{
	static int id[N],L[N],R[N];
	R[0]=1, L[n+1]=n;
	for(int i=1; i<=n; ++i) id[i]=i,L[i]=i-1,R[i]=i+1;
	std::sort(id+1,id+1+n,cmp);
	for(int i=1,x,l,r,t; i<=n; ++i)
	{
		x=id[i], l=L[x], r=R[x], t=m-1;
		int sum=A[x].val;
		for(; t&&l; --t,l=L[l]) sum+=A[l].val;
		for(; t&&r<=n; --t,r=R[r]) sum+=A[r].val;
		if(t) break;//长度<=m 
		l=R[l], r=L[r];
		while(l<=x&&r<=n)//维护一个长m的**包含x**的区间 
			Update(sum,A[r].fir-A[l].fir), sum+=A[r=R[r]].val-A[l].val, l=R[l];
		L[R[x]]=L[x], R[L[x]]=R[x];//为了方便还是先更新再删吧 后面的如果不更新它的答案就不会影响它的区间 
	}
}

int main()
{
	n=read(),m=read(),ds=read()-1,dv=read()-1;
	for(int i=1,t; i<=n; ++i) t=read(),A[i]=mp(t,read());
	std::sort(A+1,A+1+n);
	Solve1(), Solve2(), printf("%lld\n",Ans);

	return 0;
}
