/*
25ms	2444kb
$Description$
记$mss(A)$为序列A的最大子段和，求$\sum_{1\leq i\leq j\leq n}mss([A_i,...,A_j])$。
$n\leq 10^5$。
$Solution$
是不是能够用线段树做，也就是可以区间合并做的，都可以考虑过不过$mid$的答案啊（也就是分治）。
想到分治就容易点了。

对于求最大子段和的过程，考虑分治。
考虑过$mid$的区间$[l,r]$，答案要么是$[l,mid]$中最大的一段，要么是$[mid+1,r]$中最大的一段，要么是$[l',mid]$与$[mid+1,r']$的两段和。且$r$向右过程中答案会从情况一变成情况三再变成情况二。
第一种直接算。
第二种容易发现，最优解的取值在若干个点$p_i$，且越往右最优解$f(p_i)=\text{mss}(mid+1,p_i)$越大，也就是$r$在$[p_{i-1}+1,p_i]$中时第二种情况的答案就是$f(p_i)$。
第三种同理，$\max_{l'}[l',mid]$直接求，$[mid+1,r']$最优解的取值也是若干个点$p_i$，越往右$g(p_i)=\text{sum}(mid+1,p_i)$越大，$r$在$[p_{i-1}+1,p_i]$中答案为$g(p_i)$。
在$l$从右往左的过程中第一种情况的贡献是单增的，所以有更多位置的$r$选择第一种情况做答案而不选择二三。同理情况二贡献单减，选择三位置的$r$会更多。所以可以用单调性或二分求以二三情况作为最优解的$r$区间，求出来算一下个数即可。
（没必要找出最优的那些$p_i$，令$f(i)=\max\{f(i),f(i-1)\},\ g(i)=\max\{g(i),g(i-1)\}$然后就可以单调性/二分位置）
复杂度$O(n\log n)$或$O(n\log^2n)$。（题解是树状数组我人傻了）

思路很简单，细节可能有点多？比着写了一个还是挺有意思的。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb push_back
typedef long long LL;
typedef unsigned long long ull;
const int N=1e5+5,INF=1e9+10;

int A[N];
LL f[N],g[N];
ull Ans;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Solve(const int l,const int r)
{
	if(l>r) return;
	if(l==r) {Ans+=A[l]; return;}
	int m=l+r>>1;
//R //这样用代码块写感觉还行啊 
	{
		LL sum=0,mxMR=-INF,now=0,ansR=-INF;
		for(int i=m+1; i<=r; ++i)//f:与mid相连的mss  g:不需与mid相连的mss 
		{
			sum+=A[i], mxMR=std::max(sum,mxMR);
			now=std::max(now,0ll)+A[i], ansR=std::max(ansR,now);
			f[i]=mxMR, g[i]=ansR;//f:f g:d
		}
	}
//L
	{
		LL sum=0,mxLM=-INF,now=0,ansL=-INF;
		for(int i=m; i>=l; --i)
		{
			sum+=A[i], mxLM=std::max(sum,mxLM);
			now=std::max(now,0ll)+A[i], ansL=std::max(ansL,now);
			f[i]=mxLM, g[i]=ansL;
		}
	}
	ull now=0,res=0;//ull!
	for(int i=l; i<=m; ++i) res+=g[i];//[l~mid,mid]
	for(int i=m+1; i<=r; ++i) now+=g[i];

	int p1=m+1,p2=m+1,cnt1=0,cnt2=0;
	//[mid+1,p1):g[i]*cnt1  [p1,p2):(f[i]+f[r])*cnt2  [p2,r]:g[r]
	//g[p] -> f[i]+f[p] -> g[i]
	//左边的f[i],g[i]需要用cnt维护（与当前i有关），右边的用now维护（与i无关） 
	for(int i=m; i>=l; --i)
	{
		while(p2<=r && g[p2]<f[i]+f[p2]) now+=f[p2]-g[p2], ++p2, ++cnt2;
		while(p1<p2 && f[i]+f[p1]<g[i]) now-=f[p1], ++p1, --cnt2, ++cnt1;
		while(p2<=r && p1==p2 && g[p2]<g[i]) now-=g[p2], ++p1, ++p2, ++cnt1;
		res+=now+g[i]*cnt1+f[i]*cnt2;
	}
	Ans+=res;
	Solve(l,m-1), Solve(m+1,r);
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	Solve(1,n), printf("%llu\n",Ans);

	return 0;
}
