/*
342ms	11700KB
$Description$
给定一个序列$h_i$，求$\max_{1\leq i<j\leq n}(h_i+h_j)*(j-i)$。
$n\leq10^6$。
$Solution$
这种区间题考虑分治，如何求过$mid$的区间的答案。
可以发现对左边区间只有递增的$h_i$是有用的，同理右边区间只需要考虑递减的$h_i$。
找出单调的这些$h_i$记为$A_i$，然后考虑对左区间的每个$A_i$找到右边最优匹配的那个位置$p_i$，那么$p_i$是单调增加的。（可以想象二维平面上两点构成的矩形面积，或者感性理解一下）
也就是满足决策单调性。分治换一种写法，先弄出整个序列的单调的$h_i$。然后直接暴力求出当前区间$mid$的最优匹配点$p$，然后对$[l,mid-1]$、$[mid+1,r]$区间再递归，其需考虑的决策范围为$[L,p]$和$[p,R]$。
每次复杂度$O(决策范围)$，即每层$O(n)$，每层会删$1,2,4,...$个元素所以是$O(\log)$层，复杂度$O(n\log n)$。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int A1[N],A2[N],h[N];
LL Ans;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
#define Calc(p) (1ll*(h[A1[mid]]+h[A2[p]])*(A2[p]-A1[mid]))
void Solve(int l1,int r1,int l2,int r2)
{
	if(l1>r1) return;
	int mid=l1+r1>>1,pos=l2;
	for(int i=l2+1; i<=r2; ++i)
		if(Calc(i)>Calc(pos)) pos=i;
	Ans=std::max(Ans,Calc(pos));
	Solve(l1,mid-1,pos,r2), Solve(mid+1,r1,l2,pos);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) h[i]=read();
	int cnt1=1,cnt2=1; A1[1]=1, A2[1]=n;
	for(int i=2; i<=n; ++i)
		if(h[i]>h[A1[cnt1]]) A1[++cnt1]=i;
	for(int i=n-1; i; --i)
		if(h[i]>h[A2[cnt2]]) A2[++cnt2]=i;
	Solve(1,cnt1,1,cnt2), printf("%lld\n",Ans);

	return 0;
}
