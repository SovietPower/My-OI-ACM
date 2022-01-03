/*
920kb	8544ms
考虑暴力，每次枚举三个点，答案就是$\frac12\sum_{k<j<i}(i-k)\times(j-k)$。
注意到叉积有分配率，所以固定$k$，枚举$i,j$，$Ans=\frac12\sum_{k<i}(i-k)\sum_{k<j<i}(j-k)$，前缀和即可。
还有个问题是叉积是有符号的。初始时将所有点按纵坐标排序，枚举$k$的时候将所有向量$i-k$按极角排序。因为$i>k$，$i$都在$k$的上方，向量之间不会超过$180^{\circ}$，符号不会变，直接前缀和就行了。
算的时候似乎会爆`double`，用`long long`存就好了。
复杂度$O(n^2\log n)$。
另外可以直接求出向量的极角或斜率，不需要每次cmp算一次叉积。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3005;

struct Vec
{
	LL x,y;
	Vec(LL x=0,LL y=0):x(x),y(y) {}
	Vec operator +(const Vec &a)const {return Vec(x+a.x, y+a.y);}
	Vec operator -(const Vec &a)const {return Vec(x-a.x, y-a.y);}
	Vec operator *(const LL a)const {return Vec(x*a, y*a);}
	LL operator *(const Vec &a)const {return x*a.y-y*a.x;}
	inline bool operator <(const Vec &a)const {return y<a.y||(y==a.y&&x<a.x);}
}p[N],v[N];
typedef Vec Point;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline bool cmp(const Vec &a,const Vec &b)
{
	return a*b>0;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) p[i]=(Point){read(),read()};
	std::sort(p+1,p+1+n);
	LL ans=0;
	for(int i=1; i+2<=n; ++i)
	{
		for(int j=i+1; j<=n; ++j) v[j]=p[j]-p[i];
		std::sort(v+i+1,v+n+1,cmp);
		Vec s=v[i+1];
		for(int j=i+2; j<=n; ++j) ans+=s*v[j], s=s+v[j];
	}
	printf("%lld.%d\n",ans>>1,ans&1?5:0);

	return 0;
}
