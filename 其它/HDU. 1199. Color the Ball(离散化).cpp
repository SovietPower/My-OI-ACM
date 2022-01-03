/*
$Description$
给$n$个矩形，依次在矩形中染某种颜色（会覆盖之前该位置染的颜色），求最后每种颜色出现的面积和。$n\leq 1000$。
$Solution$
同1199，将$4n$个矩形端点离散化（对$x,y$分别），然后暴力染离散化后矩阵中的颜色。
注意$(1,1),(2,2)$这样矩形的面积是$1$不是$4$，所以染色的实际范围是$[l,r-1],[u,d-1]$。
还是同1199，位置$(i,j)$处的面积即$(X[i+1]-X[i])\cdot(Y[j+1]-Y[j])$。注意$X[nx+1]=X[nx]+1, Y[ny+1]=Y[ny]+1$（不过该位置也没有颜色）。
复杂度$O(n^2)$。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e4+5;

LL Ref[N];
int col[N];
struct Opt
{
	int l,r,v;
}A[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
char Get()
{
	char c=gc(); while(c!='w'&&c!='b') c=gc();
	return c;
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		int m=0;
		for(int i=1; i<=n; ++i) A[i]=Opt{read(),read(),Get()=='w'};
		for(int i=1; i<=n; ++i) Ref[++m]=A[i].l, Ref[++m]=A[i].r, Ref[++m]=A[i].r+1;
		std::sort(Ref+1,Ref+1+m);
		m=std::unique(Ref+1,Ref+1+m)-Ref-1;
		for(int i=1; i<=n; ++i)
		{
			int l=std::lower_bound(Ref+1,Ref+1+m,A[i].l)-Ref;
			int r=std::lower_bound(Ref+1,Ref+1+m,A[i].r)-Ref;
			for(int j=l,v=A[i].v; j<=r; ++j) col[j]=v;
		}
		LL ans=0,l=0,r=0; Ref[m+1]=Ref[m]+1;
		for(int i=1,las=-1; i<=m; ++i)
			if(col[i])
			{
				if(las==-1) las=i;
				if(Ref[i+1]-Ref[las]>ans) ans=Ref[i+1]-Ref[las], l=Ref[las], r=Ref[i+1]-1;
			}
			else las=-1;
		if(ans) printf("%lld %lld\n",l,r);
		else puts("Oh, my god");
		memset(col,0,m+2<<2);
	}

	return 0;
}
