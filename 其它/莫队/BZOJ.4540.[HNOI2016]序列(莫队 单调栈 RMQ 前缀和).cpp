/*
13240kb	3876ms->2980ms
**莫队：**
这种区间询问问题考虑一下莫队。
考虑移动右端点$r\to r+1$的时候怎么更新答案。
设$r+1$左边第一个比$A_{r+1}$小的数是$A_p$，那么$Ans$+=$(r+1-p)*A_{r+1}$；同理再找到$p$右边第一个比$A_p$小的数$A_{p'}$，$Ans$+=$(p-p')*A_p$；再找$p'$左边第一个比$A_{p'}$小的数......
这样怎么快速确定一个边界呢？
令$[l,r+1]$的最小值是$A_x$（用$RMQ$得到），处理到$x$位置后，$Ans$+=$(x-l+1)*A_x$就可以了。
而左边第一个比$A_i$小的数的位置可以单调栈维护出来，记为$L_i$。
因为每个数作为最小值时的区间是不会相交的，大概就是会形成一个树形结构。反正是可以用一个类似前缀和的东西维护，记为$sum_i=sum_{L_i}+(i-L_i)*A_i$（右端点在$i$，左端点在$[1,i]$时的答案）。
这样移动右端点$r\to r+1$的时候，$Ans$+=$sum_{r+1}-sum_x+(x-l+1)*A_x$，就可以$O(1)$更新了。
对于左端点，还要再反着维护一个$sum$。
复杂度$O(n\log n+n\sqrt{n})$。

**优化：**
对于询问$[l,r]$，令$[l,r]$的区间最小值为$A_p$。
那么对于左端点在$[l,p]$，右端点在$[p,r]$的子区间，最小值都是$A_p$，所以$p$的贡献就是$A_p\times(p-l+1)\times(r-p+1)$。
当子区间左右端点都在$(p,r]$时，答案就是$sum_r+sum_{r-1}+...+sum_{p+1}-sum_p\times(r-p)$。
记$s_i=\sum_{j=1}^isum_j$，那么答案就是$s_r-s_p-sum_p\times(r-p)$。
同理对于子区间左右端点在$[l,p)$时，反着维护一个$s$。
预处理出来就可以在线$O(1)$回答询问了，复杂度$O(n\log n)$。

**线段树：**
[这儿](https://blog.csdn.net/ruoruo_cheng/article/details/54585851)写的挺详细的，想再写一写。
这种$\sum_{i=l}^r\sum_{j=i}^r$的询问，把$[l,r]$中的子区间写出来。比如拿样例来说，$l=1,\ r=5$，每个子区间的最小值为：
$1\ \ 1\ \ 1\ \ 1\ \ 3\\1\ \ 1\ \ 1\ \ 1\\2\ \ 2\ \ 4\\2\ \ 2\\5$
当询问区间为$[l,r]$时，答案就是第$1$行到第$r$行中，前$l\sim r$列的和。
也就是每次右端点由$r-1$移动到$r$，是给区间$i\sim r,\ 1\leq i\leq r$分别加了一个值$\min\limits_{j=i}^r\{a_j\}$，也就是上面的三角中多了第$r$行。
如果此时询问右端点就是$r$，那答案就是$[l,r]$此时的区间和。

观察每一行的区间加，每次$A_r$会覆盖$r$前面一段区间，然后就不变和上一次一样了。
而$A_r$会覆盖的区间就是$[p+1,r]$，$p$是$r$前面第一个比$A_r$小的位置，可以单调栈预处理。
也就是我们把$[p+1,r]$的$val$改成$A_r$，然后所有位置的$sum$+=$val$。

怎么维护呢？
记此时的区间$val$的和为$sum$，区间长度为$len$，要修改的值为$v$。不妨把$[l,r]$的答案记作$his$，也就是$[l,r]$中所有点各历史版本的$val$的和。
那么修改就是：$sum'=v*len$，更新$his$就是：$his'=his+sum'$（表示不理解为什么都写的$+sum$啊QAQ）。

要用线段树高效维护区间修改，就得能维护标记合并。
把转移用矩阵写出来，就是这样：$$\begin{bmatrix}len & sum & his \\\end{bmatrix}
\begin{bmatrix}
1 & a & c \\
0 & b & d \\
0 & 0 & 1 \\
\end{bmatrix}=\begin{bmatrix}len' & sum' & his' \\\end{bmatrix}$$

维护$a,b,c,d$四个值。修改的参数就是$a=v,b=c=d=0$，更新$his$的参数是$d=1,a=b=c=0$，单位矩阵（初始化）是$b=1,a=c=d=0$。
虽然参数用不到$c$，但是矩阵结合的时候会改变$c$，但不会影响其他不维护的位置，所以要维护$c$。
这样利用矩阵的结合律，就可以维护标记合并了。

复杂度$O(n\log n)$。

ST表的一二维顺序一定要改过来。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <assert.h>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,INF=0x7fffffff;

int bel[N],A[N],sk[N],Log[N],pos[18][N];
LL suml[N],sumr[N],Ans[N];
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
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int Min(int x,int y)
{
	return A[x]<=A[y]?x:y;
}
inline int Query(int l,int r)
{
	int k=Log[r-l+1];
	return Min(pos[k][l],pos[k][r-(1<<k)+1]);
}
void Init_ST(const int n)
{
	for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1;
	for(int j=1; j<=Log[n]; ++j)
		for(int t=1<<j-1,i=n-t; i; --i)
			pos[j][i]=Min(pos[j-1][i],pos[j-1][i+t]);
}
inline LL UpdL(int l,int r)
{
	int p=Query(l,r);
	return suml[l]-suml[p]+1ll*(r-p+1)*A[p];
}
inline LL UpdR(int l,int r)
{
	int p=Query(l,r);
	return sumr[r]-sumr[p]+1ll*(p-l+1)*A[p];
}

int main()
{
	const int n=read(),Q=read(),size=sqrt(n);
	for(int i=1; i<=n; ++i) bel[i]=i/size, A[i]=read(), pos[0][i]=i;
	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};

	Init_ST(n), A[0]=-INF;
	for(int i=1,top=0; i<=n; ++i)
	{
		while(A[sk[top]]>A[i]) --top;
		sumr[i]=sumr[sk[top]]+1ll*(i-sk[top])*A[i], sk[++top]=i;
	}
	A[sk[0]=n+1]=-INF;
	for(int i=n,top=0; i; --i)
	{
		while(A[sk[top]]>A[i]) --top;
		suml[i]=suml[sk[top]]+1ll*(sk[top]-i)*A[i], sk[++top]=i;
	}
	std::sort(q+1,q+1+Q);
	LL Now=0;
	for(int i=1,l=1,r=0; i<=Q; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l>ln) Now+=UpdL(--l,r);//l的减 或 r的加 要先进行，否则就会出现l>r的情况 然后Query的时候就gg了 
		while(r<rn) Now+=UpdR(l,++r);
		while(l<ln) Now-=UpdL(l++,r);
		while(r>rn) Now-=UpdR(l,r--);
		Ans[q[i].id]=Now;
	}
	for(int i=1; i<=Q; printf("%lld\n",Ans[i++]));

	return 0;
}
