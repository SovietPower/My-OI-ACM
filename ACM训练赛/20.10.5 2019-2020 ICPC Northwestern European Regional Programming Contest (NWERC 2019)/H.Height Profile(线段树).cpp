/*
218ms	3100KB
$Description$
给定一条有$n$个上升或下降区域的折线（包含$n+1$个点）。
$k$次询问每次给定$g$，设$h[i]$表示$i$处的高度，求最长的区间$[l,r]$满足$\frac{h[r]-h[l]}{r-l}\geq g$（$l,r$为任意实数）。
$n\leq 10^5, k\leq 50$。
$Solution$
首先只考虑$l,r$取整数点的情况。
若$[l,r]$满足条件，则有$\frac{h[r]-h[l]}{r-l}\geq g$，即$h[r]-gr\geq h[l]-gl$，令$A[i]=h[i]-gi$，对每个点求最靠前的使得$A[i]\geq A[j]$的$j$即可。
如果$l,r$为实数，容易发现$[l,r]$一定是恰好包含 只取整数点时答案最大的区间中的一个（否则区间可以延伸），且$l,r$至少有一个是整数（如果都是实数说明两边线段的斜率都很优，如果斜率相等则可以任取完整的一边，如果有一边更优则一定不需要取另一边）。
所以先 离散化+树状数组/线段树维护区间最小值 求出取整数点时的答案，再对所有可能的区间往左右两边延伸即可。
延伸的时候就是解方程：设此时由$l$向左多取$p$
$$h_r-gr=h_l-(h_l-h_{l-1})p-g(l-p)\\A_r-A_l=(h_{l-1}-h_l+g)p\\p=\frac{A_r-A_l}{h_{l-1}-h_l+g}=\frac{A_r-A_l}{A_{l-1}-A_l}$$

由向右时同理。
（不知道二分为什么不对（WA on test 3）... 可二分的叭？）
读入忘了乘负号 改了一晚hhh
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,INF=1e9;

int h[N],tmp[N],A[N],Ref[N];
struct Segment_Tree
{
	#define S N<<2
	int mn[S];
	#undef S
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	void Build(int l,int r,int rt)
	{
		if(l==r) {mn[rt]=A[l]; return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	int Query(int l,int r,int rt,int v)
	{
		if(l==r) return l;
		int m=l+r>>1;
		if(mn[ls]<=v) return Query(lson,v);
		return Query(rson,v);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int Read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	for(c=gc();isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read()+1,Q=read();
	for(int i=1; i<=n; ++i) h[i]=read();
	for(; Q--; )
	{
		int g=Read();
		for(int i=1; i<=n; ++i) Ref[i]=A[i]=h[i]-g*i;

		int ans=0; T.Build(1,n,1);
		for(int i=1; i<=n; ++i)
			ans=std::max(ans,i-(tmp[i]=T.Query(1,n,1,A[i])));
		if(!ans) {puts("-1"); continue;}

		double ans2=ans;
		for(int r=1,l; r<=n; ++r)
			if((l=tmp[r])>1 && r-l==ans && h[l-1]-h[l]+g!=0)//left
				ans2=std::max(ans2,r-l+1.0*(A[r]-A[l])/(h[l-1]-h[l]+g));
		for(int r=1,l; r<n; ++r)
			if(r-(l=tmp[r])==ans && h[r]-h[r+1]+g!=0)//right
				ans2=std::max(ans2,r-l+1.0*(A[r]-A[l])/(h[r]-h[r+1]+g));
		printf("%.9f\n",ans2);
	}

	return 0;
}
