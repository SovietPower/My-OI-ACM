/*
1400kb	460ms
$Description$
有$n$个任务，完成一个任务需要$1$时刻，并会获得$v_i$的收益（只获得一次）。
每一时刻只能做一个任务，且每个任务只能在$[l_i,r_i]$的时刻内做。求最大收益。
$n\leq5000,l_i,r_i\leq10^8$。
$Solution$
我为啥不会堆的$O(n^2\log n)$做法啊。。（官方题解：https://wenku.baidu.com/view/c64d851ba8114431b90dd846.html）
首先可以跑费用流。因为要对区间连边所以要线段树优化。复杂度还是有点高，可以卡过BZOJ4276（BZOJ2034就算了 区间范围1e8）。
假设同一时刻有多个任务要完成时，会有冲突，我们自然是选价值最高的。
我们按收益从大到小排序，如果收益大的能选，那么一定先选（这只可能导致同在这个时刻的任务不能选，但反正只能选一个，显然选最大的优）。
那现在的问题是，如何在必选某些任务的情况下，判断当前能不能选。
可以每次跑匈牙利判断一下，不过是$n^3$，但是好像能过smg？
我们将任务区间按左端点排序，要选的任务应该尽量往前排，给后面腾时间。如果当前任务因为时间晚不能做，就尝试把前面的任务往后挤。
具体实现：对当前任务i枚举它区间的时刻，如果当前时刻没有任务就安排给它；
否则设当前时刻的任务为x，若r[x]>r[i]，尝试将x往后挤，最后如果能把x匹配到另一个位置就成功匹配，否则i就不可能匹配了；
如果r[x]<=r[i]，尝试把i往下一个时刻放。
时刻肯定不能直接枚举。我们发现有用的时刻最多只有$n$个。即每个位置的下一个可匹配的位置。
所以对区间离散化一下就行了。
> 贪心算法正确性的一个解释
考虑匈牙利算法，从大到小一个一个匹配，一个点一旦在匹配中，那么一直在匹配里面。 
复杂度$O(n^2)$。
有个小优化是，上面说的x如果在之前被判为不可行，后面就没必要继续DFS了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5005;

int ref[N],lk[N],tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int l,r,v;
	bool operator <(const Node &x)const{
		return v>x.v;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Lower(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline int Upper(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<=x) l=mid+1;
		else r=mid;
	return l;
}
bool DFS(int x,int l,int r)
{
	if(l>r) return 0;
	int p=lk[l];
	if(!p) return lk[l]=x,1;
	if(A[p].r>A[x].r)
		if(!tag[p]&&DFS(p,l+1,A[p].r)) return lk[l]=x,1;
		else return tag[p]=1,0;
	return DFS(x,l+1,r);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=(Node){ref[i]=read(),read(),read()};
	std::sort(ref+1,ref+1+n); ref[n+1]=1e9;
	for(int i=2; i<=n; ++i) ref[i]=std::max(ref[i-1]+1,ref[i]);
	for(int i=1; i<=n; ++i) A[i].l=Lower(A[i].l,n), A[i].r=Upper(A[i].r,n+1)-1;

	std::sort(A+1,A+1+n); long long ans=0;
	for(int i=1; i<=n; ++i)
		if(DFS(i,A[i].l,A[i].r)) ans+=A[i].v;
	printf("%lld\n",ans);

	return 0;
}
