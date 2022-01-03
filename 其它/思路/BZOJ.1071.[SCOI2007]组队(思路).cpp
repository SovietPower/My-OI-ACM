/*
976kb	2392ms
三个限制：
$Ah-AminH+Bv-BminV\leq C\to Ah+Bv\leq C+AminH+BminV$
$v\geq minV$
$h\geq minH$
记$s=Ah+Bv$。将序列按$s$从小到大排序。
$n^2$枚举$minV,minH$。如果固定$minV$，从小到大枚举$minH$时，满足$s\leq C+AminH+BminV$的位置是单增的。统计答案时可以判一下是否满足$v_i\geq minV$。
但还有$h_i\geq minH$的限制。因为$minH$是递增的，之前满足条件的后来可能不满足。用一个堆维护之前加入的最小的$h_i$即可，不满足条件就弹出。
但是$O(n^2\log n)$过不去。

问题在于怎么处理$h_i\geq minH$。按$h$排序然后$<minH$的都减掉？显然会多减掉一些不满足另外两个条件而未被统计的。
再观察一下限制，把$h,v$分开：$A(h-minH)\leq C+B(minV-v)$。
显然左式满足$\geq0$，那么也有$0\leq C+B(minV-v)\to minV\leq v\leq \frac CB+minV$。
好像就是$v$不能过大使得$h$过小？
$v\leq\frac CB+minV$时，限制一就成了$A(h-minH)+(\leq C的值)\leq C$。若$h\leq minH$，显然满足这个$s$的限制。
如果在$s$满足条件且$minV\leq v\leq \frac CB+minV$时$ans$++，限制一二仍旧满足。
如果$h<minH$且$minV\leq v\leq \frac CB+minV$，如上所说此时也满足$s$的限制，所以此时$ans$--减掉的就一定是之前统计过的了。所以就可以做到不重不漏了orz。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5005;

struct Node
{
	int h,v; LL s;
}a[N],b[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool cmps(const Node &a,const Node &b)
{
	return a.s<b.s;
}
inline bool cmph(const Node &a,const Node &b)
{
	return a.h<b.h;
}

int main()
{
	int n=read(),A=read(),B=read(),C=read();
	for(int i=1; i<=n; ++i) a[i].h=read(), a[i].v=read(), a[i].s=1ll*A*a[i].h+1ll*B*a[i].v, b[i]=a[i];
	std::sort(a+1,a+1+n,cmps);
	std::sort(b+1,b+1+n,cmph);
	int ans=0; a[n+1].s=1e18, b[n+1].h=0x7fffffff;
	for(int i=1,CdivB=C/B; i<=n; ++i)
	{//枚举minv 
		int mnv=a[i].v; LL mxv=CdivB+mnv,tmp=C+1ll*B*mnv;
		for(int j=1,l=1,r=1,cnt=0; j<=n; ++j)
		{//是从小到大枚举的minh啊→_→ 
			while(a[r].s<=tmp+1ll*A*b[j].h)
				cnt+=(a[r].v>=mnv && a[r].v<=mxv), ++r;
			while(b[l].h<b[j].h)
				cnt-=(b[l].v>=mnv && b[l].v<=mxv), ++l;
			ans=std::max(ans,cnt);
		}
	}
	printf("%d\n",ans);

	return 0;
}
