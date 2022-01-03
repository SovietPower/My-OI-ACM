/*
10496kb	888ms(Rank1!)
$Description$
有n组人要一起开一个圆桌会议（编号为$0\sim n-1$），会议的圆桌上有m个位置（编号为$0\sim m-1$）。每个组有ai个人，他们需要被安排在（li，(li+1)%m，(li+2)%m，…，ri）的座位范围内。每个座位只能安排一个人就坐，并且每个人都需要被安排一个座位。判断是否存在满足条件的座位安排。
$n\leq 10^5,\ m\leq 10^9$。
$Solution$
先考虑链。题目相当于求是否存在完备匹配。那么由Hall定理，对于任意一个区间[L,R]，都要满足[li,ri]完全在[L,R]中的ai之和sum小于等于总位置数，即R-L+1。（其实用不到Hall定理，显然）
为什么不是子集呢，因为区间并和子集等价，所有区间并都是要验证的。
而且可以发现，只有当R为某个r[i]，L为某个l[j]时，[L,R]才有必要验证。
所以我们将区间按r[]排序，枚举每个r[i]作为R。限制条件为sum<=R-L+1即sum+L-1<=R，对于前面所有位置，即L∈[1,R]，我们可以直接用线段树维护每个位置的sum+L-1，查询最大值就可以了。
每次枚举到i，会使L∈[1,l[i]]时+ai，这个区间加就行了。
至于环，拆环为链就可以了。
但是有个问题，比如m=5,([1,3],2),([3,2],3)，会分成区间[1,3],[3,7],[6,8]，[3,2]实际是包含[1,3]的，但是[1,3]被分成了[3,3]和[6,7]，它的a就不会就加上了。
因为r=l-1时，长为m，会把另一个[l,r]与复制出来的[l+m,r+m]分割开，导致都不包含在[r,l-1]内。
因为这些区间长度都为m，所以只需要先判一下整个区间即可。
r[]不需要离散化，否则注意是与ref[r]比较。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5;

int n,m,ref[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Opt
{
	int l,r,a;
	Opt() {}
	Opt(int l,int r,int a):l(l),r(r),a(a) {}
	bool operator <(const Opt &x)const{
		return r<x.r;
	}
}q[N];
struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	int mx[N<<2],tag[N<<2];

	#define Update(rt) mx[rt]=std::max(mx[lson],mx[rson])
//	#define Add(rt,v) mx[rt]+=v, tag[rt]+=v
//	#define PushDown(rt) Add(lson,tag[rt]), Add(rson,tag[rt]), tag[rt]=0
	inline void Add(int rt,int v){
		mx[rt]+=v, tag[rt]+=v;
	}
	void PushDown(int rt){
		Add(lson,tag[rt]), Add(rson,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		tag[rt]=0;
		if(l==r) mx[rt]=ref[l]-1;//ref!
		else Build(l,l+r>>1,lson), Build((l+r>>1)+1,r,rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Add(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(ToL,L,R,v);
		if(m<R) Modify(ToR,L,R,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mx[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(ToL,L,R),Query(ToR,L,R));
			else return Query(ToL,L,R);
		return Query(ToR,L,R);
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
	int Case=read();
	while(Case--)
	{
		n=read(),m=read(); int Q=0,t=0; long long sum=0;
		for(int i=1,l,r,a; i<=n; ++i)
		{
			ref[++t]=l=read(),r=read(),sum+=(a=read());
			if(l<=r) q[++Q]=Opt(l,r,a), q[++Q]=Opt(l+m,r+m,a), ref[++t]=l+m/*!*/;
			else q[++Q]=Opt(l,r+m,a);
		}
		if(sum>m) {puts("No"); continue;}
		std::sort(q+1,q+1+Q);
		std::sort(ref+1,ref+1+t); int cnt=1;
		for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
		for(int i=1; i<=Q; ++i) q[i].l=Find(q[i].l,cnt);//, q[i].r=Find(q[i].r,cnt);
		n=cnt, T.Build(1,n,1);
		bool f=1;
		for(int i=1; i<=Q; ++i)
		{
			T.Modify(1,n,1,1,q[i].l,q[i].a);
			if(T.Query(1,n,1,1,q[i].l/*l对?用r还得离散化...*/)>q[i].r) {f=0; break;}//ref[r]
		}
		puts(f?"Yes":"No");
	}
	return 0;
}
