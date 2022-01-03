/*
26132kb	15528ms
**莫队 前缀和 单调栈：**（非正解，不开O2 70分，开O2~~以及BZOJ算总时限~~可以A）
可以先做一下[HNOI2016 序列](https://www.cnblogs.com/SovietPower/p/10286483.html)，（如果这道题也能那么做的话）感觉算是那道题的加强版。因为这个要多维护好多东西。。
做完那题就容易发现我们需要维护什么了。假设我们要从$[l,r-1]$转移到$[l,r]$，首先找到区间最大值$p$的位置，然后$[l,p]$之间的贡献很好算，维护两个前缀和表示前面/后面的单调子序列中，比它大的有多少个。麻烦的是$[p+1,r]$里面的...
刚开始想的是再维护两个前缀和，查询的时候求一下$[L[r]+1,r-1]$（$L[x]$为$x$左边第一个比$A_x$大的数）中的最大值，再同样统计一下。
然而细节贼特么多，写+调了3h，发现LOJ上有O2还T了一个点= =（洛谷倒过了，感动）。
对比[$mjt$的代码](https://www.cnblogs.com/mjtcn/p/10072954.html)发现（orz），莫队转移的时候多了一次查询最小值影响特别大。。
又想了想发现一个前缀和就可以，然后又改+调~~+颓~~了2h=-=。但是跑的比较快啦~~不开O2也有$70$分啦~~（$mjt$$30$分2333）。
不是很好解释，但很好理解，只是细节问题。。
复杂度$O(n\sqrt n)$。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,INF=1<<30;

int P1,P2,bel[N],A[N],ref[N],st[18][N],Log[N],sk[N],L[N],R[N],sl[N],sr[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,id;
	bool operator <(const Quries &x)const
	{
		return bel[l]==bel[x.l]?r<x.r:bel[l]<bel[x.l];
	}
}q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Query(int l,int r)//return pos
{
	int k=Log[r-l+1];
	return ref[std::max(st[k][l],st[k][r-(1<<k)+1])];//比写A[x]>A[y]?x:y 快0.4s+...
}
void Init_ST(const int n)
{
	for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1;
	for(int j=1; j<=Log[n]; ++j)
		for(int t=1<<j-1,i=n-t; i; --i)
			st[j][i]=std::max(st[j-1][i],st[j-1][i+t]);
}
inline LL UpdL(int l,int r)
{
	if(l==r) return 0;
	int p=Query(l+1,r),R=std::min(p,::R[l]),tot=R-l,num=sl[l+1]-sl[R]+1;
	return (LL)num*P1+(tot-num)*P2+(R<p?(sl[R]-sl[p])*P2:(::R[l]>r)?(r-p)*P2:0);
}
inline LL UpdR(int l,int r)
{
	if(l==r) return 0;
	int p=Query(l,r-1),L=std::max(p,::L[r]),tot=r-L,num=sr[r-1]-sr[L]+1;
	return (LL)num*P1+(tot-num)*P2+(L>p?(sr[L]-sr[p])*P2:(::L[r]<l)?(p-l)*P2:0);
}

int main()
{
	static LL Ans[N];

//	freopen("sf.in","r",stdin);
//	freopen("sf.out","w",stdout);

	const int n=read(),Q=read(),P1=read(),P2=read(),size=sqrt(n); ::P1=P1,::P2=P2;
	for(int i=1; i<=n; ++i) st[0][i]=A[i]=read(), ref[A[i]]=i, bel[i]=i/size;
	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+Q);

	Init_ST(n);
	A[sk[0]=0]=INF;
	for(int i=1,top=0; i<=n; ++i)//sr[i]:递减子序列中，i左边有多少个比它大的数 sr2[i]:贡献2 
	{
		while(A[sk[top]]<=A[i]) --top;//R[sk[top--]]=i;
		sr[i]=sr[L[i]=sk[top]]+1, sk[++top]=i;//sr2[i]=sr2[sk[top]]+(i-sk[top]-1)*P2+P1,
	}
	A[sk[0]=n+1]=INF;
	for(int i=n,top=0; i; --i)
	{
		while(A[sk[top]]<=A[i]) --top;//L[sk[top--]]=i;
		sl[i]=sl[R[i]=sk[top]]+1, sk[++top]=i;//sl2[i]=sl2[sk[top]]+(sk[top]-i-1)*P2+P1,
	}
	LL Now=0;
	for(int l=1,r=0,i=1; i<=Q; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l>ln) Now+=UpdL(--l,r);
		while(r<rn) Now+=UpdR(l,++r);
		while(l<ln) Now-=UpdL(l++,r);
		while(r>rn) Now-=UpdR(l,r--);
		Ans[q[i].id]=Now;
	}
	for(int i=1; i<=Q; printf("%lld\n",Ans[i++]));

	return 0;
}
