/*
$Description$
无限个的球，初始为黑。$n$次操作，每次给区间$[l,r]$将其中所有球染成黑色或白色，求操作后最长连续的白球段在哪。$n\leq 2000,\ 1\leq l,r\lt 2^{31}$。
$Solution$
将$2n$个端点离散化，然后暴力对离散化后区间染色，求最长连续段。
但有个问题是：$[1,2]$染白，$[4,5]$染白，中间没有$3$，离散化后$[1,5]$会连在一起。所以离散化的时候加入点$3,6$，即每个区间加入$r+1$，避免与下一区间相连。
然后$i$位置的长度即$Ref[i+1]-Ref[i]$。要设$Ref[m+1]=Ref[m]+1$，但注意加$1$会爆$int$。
复杂度$O(n^2)$。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=3e2+5;

int col[N][N],Refx[N],Refy[N],Ans[105];
struct Opt
{
	int x1,y1,x2,y2,c;
}A[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int X,Y,T=1; scanf("%d%d",&X,&Y),X&&Y; ++T)
	{
		int n=read(),tx=0,ty=0;
		if(T!=1) pc('\n');//最后一个test不能换行 这换行也太阴间了吧 绝了 
		for(int i=1; i<=n; ++i) A[i]=Opt{read(),read(),read(),read(),read()};
		for(int i=1; i<=n; ++i)
			Refx[++tx]=A[i].x1, Refx[++tx]=A[i].x2,
			Refy[++ty]=A[i].y1, Refy[++ty]=A[i].y2;
		std::sort(Refx+1,Refx+1+tx), tx=std::unique(Refx+1,Refx+1+tx)-Refx-1;
		std::sort(Refy+1,Refy+1+ty), ty=std::unique(Refy+1,Refy+1+ty)-Refy-1;

		for(int i=1; i<=n; ++i)
		{
			int lx=std::lower_bound(Refx+1,Refx+1+tx,A[i].x1)-Refx;
			int rx=std::lower_bound(Refx+1,Refx+1+tx,A[i].x2)-Refx-1;
			int ly=std::lower_bound(Refy+1,Refy+1+ty,A[i].y1)-Refy;
			int ry=std::lower_bound(Refy+1,Refy+1+ty,A[i].y2)-Refy-1;
			int c=A[i].c;
			for(int a=lx; a<=rx; ++a)
				for(int b=ly; b<=ry; ++b)
					col[a][b]=c;
		}
		Refx[tx+1]=Refx[tx]+1, Refy[ty+1]=Refy[ty]+1;
		for(int i=1; i<=tx; ++i)
			for(int j=1; j<=ty; ++j)
				Ans[col[i][j]]+=(Refx[i+1]-Refx[i])*(Refy[j+1]-Refy[j]);

		int ans=0;
		printf("Case %d:\n",T);
		for(int i=1; i<=100; ++i)
			if(Ans[i]) ++ans, printf("%d %d\n",i,Ans[i]);
		if(ans>1) printf("There are %d colors left on the wall.\n",ans);//搁着学英语呢 
		else printf("There is %d color left on the wall.\n",ans);

		memset(col,0,sizeof col);
		memset(Ans,0,sizeof Ans);
	}

	return 0;
}
