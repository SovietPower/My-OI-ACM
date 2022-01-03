/*
5028kb	1036ms
首先旗杆的顺序没有影响，答案之和在某一高度帆的总数有关。所以先把旗杆按高度排序。
设高度为$i$的帆有$s_i$个，那么答案是$\sum\frac{s_i(s_i-1)}{2}$，显然我们要让每一行（高度）的帆数都尽量少。
然后可以想到二分，二分每一行的帆数不超过$mid$是否可行。显然我们从最高的旗杆的最大高度部分往下填就可以了，要用线段树维护。复杂度$O(n\log^2n)$。
但是不需要这个二分啊，每次找到$s_i$最小的位置，把$k$个帆填进去就行了。
那么显然把旗杆从低到高排序，每次覆盖$s_i$最小的区间，就可以保证正确性了。
线段树维护，把这$k$个位置填到$[h-k+1,h]$。这个区间的左端点可能不是一段完整的连续值域区间的左端点，需要将在该一部分平移到该连续段左端点去覆盖来保证$s_i$递减。对此就找到$h-k+1$位置处连续段的左右端点$L,R$，判一下$R$是否$<h$就好了。（画个图很容易理解，初始时就可能是这样的）
复杂度$O(n\log n)$。
可以用树状数组写，虽然查询位置是两个$\log$的，但是常数太小了没O2线段树比不过。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

pr A[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int mn[S],tag[S];
	#undef S
	#define Upd(rt,v) mn[rt]+=v,tag[rt]+=v
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	#define PushDown(rt) Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Upd(rt,1); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R);
		if(m<R) Modify(rson,L,R);
		Update(rt);
	}
	int FindPos(int l,int r,int rt,int p)
	{
		while(l!=r)
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			p<=m ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return mn[rt];
	}
	int FindL(int l,int r,int rt,int val)
	{
		while(l!=r)
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			mn[ls]<=val ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return l;
	}
	int FindR(int l,int r,int rt,int val)
	{
		while(l!=r)
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			mn[ls]<val ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return mn[rt]==val?l:l-1;
	}
	LL Calc(int l,int r,int rt)
	{
		if(l==r) return 1ll*mn[rt]*(mn[rt]-1)>>1;
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		return Calc(lson)+Calc(rson);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	#define S 1,lim,1
	const int n=read();
	for(int i=1,h; i<=n; ++i) h=read(),A[i]=std::make_pair(h,read());//h,k
	std::sort(A+1,A+1+n);
	int lim=A[n].first;
	for(int i=1; i<=n; ++i)
	{
		int h=A[i].first,k=A[i].second;
		int mn=T.FindPos(S,h-k+1),L=T.FindL(S,mn),R=std::min(h,T.FindR(S,mn));
		if(L!=h-k+1)//if(R<h)
		{
			T.Modify(S,L,L+k-h+R-1);
			if(R<h) T.Modify(S,R+1,h);
		}
		else T.Modify(S,L,L+k-1);
	}
	printf("%lld\n",T.Calc(S));

	return 0;
}
