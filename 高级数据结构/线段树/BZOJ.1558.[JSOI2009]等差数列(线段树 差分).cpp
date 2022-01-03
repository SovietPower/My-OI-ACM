/*
12460kb	2476ms
首先可以把原序列$A_i$转化成差分序列$B_i$去做。
这样对于区间加一个等差数列$(l,r,a_0,d)$，就可以转化为$B_{l-1}$+=$a_0$，$B_r$-=$(r-l)*d+a_0$，$B_{l...r-1}$+=$d$。
对于查询，似乎只需要求区间$b_i$的连续段个数？
并不是，比如：
$A:\ 0\ 1\ 3\ 6\ 10\\B:\ \ \ 1\ 2\ 3\ 4$
答案是$3$而不是$4$，我们可以这样划分：$\{0,1\},\{3,6\},\{10\}$，或是$\{0,1\},\{3\},\{6,10\}$等等，得到三个等差数列。
为什么会不是$4$呢，除了两个数也是一个等差数列外，如果我们选择了差分序列中的$1,4$，也就是选$\{0,1\},\{6,10\}$划分成两个等差数列，那$A_3=3$是属于$B_2=2$还是$B_3=3$呢？
问题其实在于，区间中间那个数只能属于左右等差数列中的一个（或是相等的时候可以把两个等差数列连起来）。

> 然而网上好多题解都没有明说这件事啊？只看到两三篇是这个意思的（[这个](https://blog.csdn.net/XHRlyb/article/details/79439580)和[这个](https://www.cnblogs.com/galaxies/p/bzoj1558.html)，[yyb的](http://www.cnblogs.com/cjyyb/p/8557066.html)其实也是吧），其它题解只是写了下$s$的定义，一点关于"左右端点选不选"是什么的解释都没有（当然也许只是我不能理解）。
当然只是个人理解咯。（表示我一共想了三种理解哪种都能和代码对应上，但前两种并不能说过去）

然后，小区间内部的答案在合并成大区间时是不会变的，要考虑的只是端点属于哪个区间的问题。
所以可以用线段树维护，令$L,R$表示当前区间的$B_l,B_r$，$s_0,s_1,s_2,s_3$分别表示，左右端点都不属于这个区间（不与这个区间中的数构成等差数列）时的答案， 左端点属于而右端点不属于这个区间的答案，右端点属于而左端点不属于这个区间的答案，左右端点都属于这个区间的答案。
有这些就可以合并区间了，这里就可以见代码了。
询问的答案，就是询问区间合并后的$s_3$。
因为是在差分后的序列上做，询问$[l,r]$是查询$[l,r-1]$，还要注意边界问题。
复杂度$O(q\log n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int L,R,s0,s1,s2,s3;//s0:(l,r) 左右都不属于 s1:[l,r) s2:(l,r] s3:[l,r] 
	inline Node operator +(const Node &b)
	{
		Node c;
		c.L=L, c.R=b.R; int v=R==b.L;
		c.s0=std::min(s2+b.s1-v, std::min(s0+b.s1, s2+b.s0));
		c.s1=std::min(s3+b.s1-v, std::min(s3+b.s0, s1+b.s1));
		c.s2=std::min(s2+b.s3-v, std::min(s0+b.s3, s2+b.s2));
		c.s3=std::min(s3+b.s3-v, std::min(s1+b.s3, s3+b.s2));
		return c;
	}
};
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,rt<<1
	#define rson m+1,r,rt<<1|1
	#define S N<<2
	int tag[S];
	Node t[S];
	#undef S
	#define Upd(x,v) t[x].L+=v, t[x].R+=v, tag[x]+=v
	#define Update(rt) t[rt]=t[ls]+t[rs]
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r)
		{
			t[rt]=(Node){A[l],A[l],0,1,1,1};
			return;
		}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Upd(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
		Update(rt);
	}
	void ModifyP(int l,int r,int rt,int p,int v)
	{
		if(l==r) {Upd(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		p<=m ? ModifyP(lson,p,v) : ModifyP(rson,p,v);
		Update(rt);
	}
	Node Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return t[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)+Query(rson,L,R);
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline char GetOpt()
{
	register char c=gc();
	while(c!='A'&&c!='B') c=gc();
	return c;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	if(n==1)
	{
		for(int Q=read(); Q--; )
			if(GetOpt()=='B') puts("1");
		return 0;
	}
	--n;
	for(int i=1; i<=n; ++i) A[i]=A[i+1]-A[i];
	T.Build(1,n,1);
	for(int Q=read(); Q--; )
		switch(GetOpt())
		{
			case 'A':
			{
				int l=read(),r=read(),a=read(),d=read();
				if(l<r) T.Modify(1,n,1,l,r-1,d);
				if(l>1) T.ModifyP(1,n,1,l-1,a);
				if(r<=n) T.ModifyP(1,n,1,r,(l-r)*d-a);//r!=n!
				break;
			}
			case 'B':
			{
				int l=read(),r=read();
				if(l!=r) printf("%d\n",T.Query(1,n,1,l,r-1).s3);
				else puts("1");
				break;
			}
		}
	return 0;
}
