/*
2260kb	544ms(2260kb	1768ms)
$Description$
有$n$个外星人，第$i$个外星人会在时间$a_i$出现，离你距离$d_i$，且必须在时间$b_i$之前被消灭。
你有一个武器，可秒杀半径为$r$的圆内的所有外星人。$r$可任意调整，但每攻击一次会消耗$r$单位能量。求消灭所有外星人的最小消耗能量。
$n\leq 300, a_i,b_i,d_i\leq 10^4$。
$Solution$
考虑出现时间在[l,r]内的敌人，设最远的敌人距离为$d_{max}$，我们至少要用一次半径$r=d_{max}$的攻击以消灭它。
如果我们选择在$t$时刻攻击这个距离最远的，那么时间区间跨越$t$的其它敌人也会被顺带消灭。
这样就划分成了两个子区间的问题。
先对时间区间离散化，然后区间DP，对当前区间找出距离最远的敌人，然后枚举消灭它的时刻$t$。
复杂度$O(n^3)$。
因为要找距离最远的，所以先对敌人排序，可以有效优化常数。。（而且结构体确实要比数组慢？）
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=605;

int ref[N],f[N][N];
struct Node
{
	int l,r,dis;
	bool operator <(const Node &x)const
	{
		return dis>x.dis;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	for(int T=read(); T--; )
	{
		int n=read(),t=0;
		for(int i=1; i<=n; ++i) ref[++t]=A[i].l=read(),ref[++t]=A[i].r=read(),A[i].dis=read();
		std::sort(A+1,A+1+n);

		std::sort(ref+1,ref+1+t); int cnt=1;
		for(int i=2; i<=t; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
		for(int i=1; i<=n; ++i) A[i].l=Find(A[i].l,cnt), A[i].r=Find(A[i].r,cnt);

		for(int len=0; len<cnt; ++len)
			for(int i=1; i+len<=cnt; ++i)
			{
				int j=i+len,mx=0;
				for(int k=1; k<=n; ++k)
					if(i<=A[k].l && A[k].r<=j) {mx=k; break;}
				if(!mx) {f[i][j]=0; continue;}
				int tmp=1000000000;
				for(int k=A[mx].l,R=A[mx].r,cost=A[mx].dis; k<=R; ++k)//不是i~j。。
					tmp=std::min(tmp,f[i][k-1]+f[k+1][j]+cost);
				f[i][j]=tmp;
			}
		printf("%d\n",f[1][cnt]);
	}
	return 0;
}
