/*
309ms	4172kB
$Description$
二维平面上有$n$个玩家，每个玩家在$(x_i,y_i)$处。有一个补给箱掉落在$(X,Y)$处，其中$Y$已知$X$不确定。
每个玩家在一个单位时间内会向补给箱移动一个单位，移动规则：向上下移动到和$Y$同一横坐标后再左右，直到到补给箱处。若两个或多个玩家同时在非补给箱位置的某处相遇则会全部出局。
求$X$不确定情况下出局的最多人数和最少人数。
$Solution$
这题过的人少但不难。。
易知两个或多个人相遇的条件是，他们到$(X,Y)$的曼哈顿距离相同，即$|x_i-X|+|y_i-Y|$相同。
考虑枚举$X$（最多考虑$2n$个），对于$(X,Y)$左边的人，若相遇，则有$|X-x_i|+|y_i-Y|$相同，也就是$|y_i-Y|-x_i$相同。从左到有枚举$X$并记录某个值是否出现即可。
对于$X$右边的就是$|y_i-Y|+x_i$相同。

然后是某些细节：三个曼哈顿距离相同的点$i,j,k$，前两个可能会早就相遇然后out，第三个不会出局。可以发现要么是前两个$x$相同，要么是$x_i<x_j<x_k$，$k$不出局。对于前一种情况记录每个值的$las$，后一种情况记一个$tag$即可。
注意下多个人同时出局的情况。
此外我这个写法要注意，$x$相同的点只能在$X$枚举到$x$时更新一次答案（否则不对）。
写的有些乱，不多说了。。自己模拟下就ok。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,M=3e5+15,lim=1e5+2;

int tag[M],tmp[M],las[M];
struct Node
{
	int val,x;
	bool operator <(const Node &a)const
	{
		return x==a.x?val<a.val:x<a.x;
	}
}A[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		int n=read(),y=read();
		for(int i=1,X,Y; i<=n; ++i) X=read(), Y=read(), A[i]=(Node){std::abs(Y-y)-X+lim,X};//[-1e5,1e5)->(0,2e5]
		std::sort(A+1,A+1+n);
		int cnt=n;
		for(int i=1; i<n; ++i) if(A[i].x+1<A[i+1].x) A[++cnt]=(Node){0,A[i].x+1};
		A[++cnt]=(Node){0,0}, A[++cnt]=(Node){0,A[n].x+1}, std::sort(A+1,A+1+cnt);

		A[0].x=A[1].x-1, A[cnt+1].x=A[cnt].x+1;
		for(int i=1,ans=0,t,x,j,a; i<=cnt; i=j)
		{
			for(j=i,a=ans; A[j].x==A[i].x; ++j)
			{
				tmp[j]=a;
				if(t=A[j].val)
				{
					x=A[j].x;
					if(las[t])
						if(las[t]==x) tag[t]?++ans:ans+=2, las[t]=0, tag[t]=0;
						else if(!tag[t]) ans+=2, las[t]=x, tag[t]=1;
						else las[t]=x, tag[t]=0;
					else las[t]=x;
				}
			}
		}
		for(int i=1,t; i<=cnt; ++i) tag[t=A[i].val]=0, las[t]=0, t&&(A[i].val+=2*A[i].x);//(0,2e5)->(1e5,3e5)

		int mn=N,mx=0;
		for(int i=cnt,ans=0,t,x,j; i; i=j)
		{
			mn=std::min(mn,ans+tmp[i]), mx=std::max(mx,ans+tmp[i]);
			for(j=i; A[j].x==A[i].x; --j)
			{
				if(t=A[j].val)
				{
					x=A[j].x;
					if(las[t])
						if(las[t]==x) tag[t]?++ans:ans+=2, las[t]=0, tag[t]=0;
						else if(!tag[t]) ans+=2, las[t]=x, tag[t]=1;
						else las[t]=x, tag[t]=0;
					else las[t]=x;
				}
			}
		}
		for(int i=1; i<=cnt; ++i) tag[A[i].val]=0, las[A[i].val]=0;
		printf("%d %d\n",n-mx,n-mn);
	}

	return 0;
}
