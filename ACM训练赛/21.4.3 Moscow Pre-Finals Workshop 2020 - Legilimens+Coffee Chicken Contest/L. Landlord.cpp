/*
78ms	0KB
$Description$
给定无限大平面上的两个矩形，求它们将平面分成几个连通块。
$Solution$
对给定的$4$个点离散化，然后直接DFS求连通块数。
离散化的时候对所得下标乘$2$再$+1$得到新下标，再标记$vis=1$会很方便。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=20,Way[5]={1,0,-1,0,1};

int refx[N],refy[N],vis[N][N];
struct Point
{
	int x1,y1,x2,y2;
}A[2];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int *a,int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(a[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l*2+1;
}
void DFS(int x,int y)
{
	vis[x][y]=1;
	for(int i=0; i<4; ++i)
	{
		int xn=x+Way[i],yn=y+Way[i+1];
		if(xn && yn && xn<N && yn<N && !vis[xn][yn]) DFS(xn,yn);
	}
}

int main()
{
	for(int T=read(); T--; )
	{
		for(int i=0; i<2; ++i) A[i]=(Point){read(),read(),read(),read()};
		int tx=0,ty=0;
		for(int i=0; i<2; ++i) refx[++tx]=A[i].x1, refx[++tx]=A[i].x2;
		for(int i=0; i<2; ++i) refy[++ty]=A[i].y1, refy[++ty]=A[i].y2;
		std::sort(refx+1,refx+1+tx), std::sort(refy+1,refy+1+ty);
		tx=std::unique(refx+1,refx+1+tx)-refx-1;
		ty=std::unique(refy+1,refy+1+ty)-refy-1;

		memset(vis,0,sizeof vis);
		for(int i=0; i<2; ++i)
		{
			int l1=Find(refx,A[i].x1,tx),r1=Find(refx,A[i].x2,tx);
			int l2=Find(refy,A[i].y1,ty),r2=Find(refy,A[i].y2,ty);
			for(int a=l1; a<=r1; ++a) vis[a][l2]=1, vis[a][r2]=1;
			for(int b=l2; b<=r2; ++b) vis[l1][b]=1, vis[r1][b]=1;
		}
		int res=0;
		for(int i=1; i<N; ++i)
			for(int j=1; j<N; ++j)
				if(!vis[i][j]) ++res, DFS(i,j);
		printf("%d\n",res);
	}

	return 0;
}
