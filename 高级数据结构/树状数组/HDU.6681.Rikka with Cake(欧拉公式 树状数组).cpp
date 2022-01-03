/*
904MS	3148K
$Description$
$n*m$矩形内给定$k$条射线，求矩形内划分成的连通块数。
$Solution$
一个能看出来的结论：联通块数=交点数+1.
证明是用欧拉公式/定理：区域数R+顶点V-边数E=2.
设射线间交点数为$c$，则总边数为$4+射线数n+射线与矩形交叉产生n+射线交叉产生2c$
总顶点数为$4+射线本身n+与矩形相交产生n+c$（任何一个点就是一个顶点）
所有区域数就是$R=2+4+2n+2c-4-n-n-c=c+2$，矩形外也算一个区域所以答案为$c+1$。

求交点数方法很多。
**Sol1:**
将垂直向下的射线和水平的射线按$y$排序，按顺序枚举，并对$x$建树状数组。水平射线就用两个（或一个）树状数组前缀或后缀+1；垂直射线就查一下单点的值。
然后再对垂直向上的射线求一遍就ok了。
**Sol2:**
将所有射线按$y$排序，按顺序枚举，并对$x$建树状数组。垂直射线出现时就用树状数组单点+1，消失时单点-1；水平射线就查一下前缀或后缀区间的值（后缀就是当前垂直射线总数-前缀的）。
（和Sol1一样的，不过用垂直射线修改只需要一遍。树状数组是$x$还是$y$也是一样的（就是区间修改还是单点修改的区别））
**Sol3:**
对于向下的射线$(xi,yi)$，求向左的射线$(xj,yj)$中满足$xj>xi$且$yj<yi$的射线个数，和向右的射线$(xj,yj)$中满足$xj<xi$且$yj<yi$的射线个数。
对于向上的射线，反转一下$y$坐标和水平射线的方向再求一次。
然后求解过程就是二位偏序，排序+树状数组即可。

代码为$Sol2$（好像都要$2k$次树状数组）。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int A[N];
struct Segment
{
	int type,x,y;//0:U 1:D 2:L 3:R
	bool operator <(const Segment &s)const
	{
		return y<s.y;
	}
}seg[N];
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-(x))
	void Add(int p)
	{
		for(; p<=n; p+=lb(p)) ++t[p];
	}
	void Delete(int p)
	{
		for(; p<=n; p+=lb(p)) --t[p];
	}
	int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res;
	}
}T;

inline int read()
{
	int now=0; char c=gc();
	for(; !isdigit(c); c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now;
}
inline int Get()
{//0:U 1:D 2:L 3:R
	char c=gc(); for(; !isalpha(c); c=gc());
	return c=='U'?0:c=='D'?1:c=='L'?2:3;
}
inline int Find(int r,int x)
{
	int l=1,mid;
	while(l<r)
		if(A[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	for(int Case=read(); Case--; )
	{
		int L=read(),R=read(),n=read();
		for(int i=1,x,y; i<=n; ++i)
			A[i]=x=read(), y=read(), seg[i]=(Segment){Get(),x,y};
		std::sort(A+1,A+1+n);
		int cnt=1;
		for(int i=2; i<=n; ++i) if(A[i]!=A[i-1]) A[++cnt]=A[i];
		for(int i=1; i<=n; ++i) seg[i].x=Find(cnt,seg[i].x);
		std::sort(seg+1,seg+1+n);

		int ans=1,sum=0; T.n=cnt;
		for(int i=1; i<=n; ++i) seg[i].type==1&&(T.Add(seg[i].x),++sum);
		for(int i=1; i<=n; ++i)
			switch(seg[i].type)
			{
				case 0: ++sum, T.Add(seg[i].x); break;
				case 1: --sum, T.Delete(seg[i].x); break;
				case 2: ans+=T.Query(seg[i].x); break;
				case 3: ans+=sum-T.Query(seg[i].x-1); break;
			}
		for(int i=1; i<=n; ++i) seg[i].type==0&&(T.Delete(seg[i].x),0);
		printf("%d\n",ans);
	}

	return 0;
}
