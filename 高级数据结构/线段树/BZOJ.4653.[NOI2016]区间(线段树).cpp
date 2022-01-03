/*
42136kb	8316ms
考虑二分。那么我们可以按区间长度从小到大枚举每个区间，对每个区间可以得到一个可用区间长度范围。
我们要求是否存在一个点被这些区间覆盖至少$m$次。这可以用线段树区间加、求max维护（或者在线段树上二分）。
但这是两个$\log$的。
我们不二分，按长度枚举每个区间。这样边枚举边判一下是否有点被覆盖$m$次就好了。
复杂度$O(n\log n)$。
动态开点值域线段树MLE 95分啊。。
另外动态开点的区间修改，下传标记的时候要先判有没有儿子（没有要新建节点）。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e5+5;

int ref[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Interval
{
	int l,r,len;
	Interval() {}
	Interval(int l,int r):l(l),r(r) {len=r-l;}
	bool operator <(const Interval &x)const
	{
		return len<x.len;
	}
}A[N];
struct Segment_Tree
{
	#define S N<<3
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson ls,l,m
	#define rson rs,m+1,r
	int tot,mx[S],tag[S];
	#undef S

	#define Update(x) mx[x]=std::max(mx[ls],mx[rs])
	#define Upd(x,v) tag[x]+=v,mx[x]+=v
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Modify(int rt,int l,int r,int L,int R,int val)
	{
		if(L<=l && r<=R) {Upd(rt,val); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,val);
		if(m<R) Modify(rson,L,R,val);
		Update(rt);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	#define S 1,1,cnt

	int n=read(),m=read(),t=0;
	for(int i=1; i<=n; ++i) ref[++t]=read(),A[i]=Interval(ref[t-1],ref[++t]=read());
	std::sort(A+1,A+1+n);

	std::sort(ref+1,ref+1+t); int cnt=1;
	for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i].l=Find(A[i].l,cnt), A[i].r=Find(A[i].r,cnt);

	int ans=2e9;
	for(int l=1,r=1; r<=n; ++r)
	{
		while(T.mx[1]<m && r<=n) T.Modify(S,A[r].l,A[r].r,1), ++r;
		--r;
		if(T.mx[1]>=m)
		{
			while(T.mx[1]>=m) T.Modify(S,A[l].l,A[l].r,-1), ++l;
			ans=std::min(ans,A[r].len-A[l-1].len);
		}
		else break;
	}
	printf("%d\n",ans==2e9?-1:ans);

	return 0;
}
