/*
31ms	500KB
模拟。。就是判断一下直线相交的时候的情况。
直接判断加入一个点之前与之后两条直线的点的位置关系，再用一个变量临时存面积，区域结束时加入答案即可，但我写麻烦了。。
结果是不仅要判的多，遇到递减序列需要将序列反过来变成递增（注意y会变化！！）。
*/
#include <cstdio>
#include <cctype>
#include <cassert>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=25005,INF=1<<28;

LL Ans[N];
bool vis[50005];
struct Node
{
	int x,y;
}down[N],up[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int m=read(),n=read(),yd=read();
	for(int i=1; i<=m; ++i) down[i].x=read(),down[i].y=read(),assert(!vis[down[i].x]),vis[down[i].x]=1;
	int yu=read();
	for(int i=1; i<=n; ++i) up[i].x=read(),up[i].y=read(),assert(!vis[up[i].x]),vis[up[i].x]=1;
	if((yd>down[1].y)^(yu>up[1].y)) return puts("0 0"),0;

	int tag=0;
	if(yd>down[1].y)//zbl
	{
		std::reverse(up+1,up+1+n), std::reverse(down+1,down+1+m);
		tag=1, up[n+1].y=yu, yu=up[1].y, down[m+1].y=yd, yd=down[1].y;
		for(int i=1; i<=n; ++i) up[i].x*=-1;
		for(int i=1; i<=m; ++i) down[i].x*=-1;
	}

	int cnt=0,las=INF; up[n+1].x=INF, down[m+1].x=INF;
	for(int i=1,j=1; i<=n||j<=m; )//i:up j:down
	{
		if(up[i].x<down[j].x)
		{
			int x=up[i].x,y=up[(i++)+tag].y;
			if(yu>yd)
				if(las<INF) Ans[cnt]+=1ll*(x-las)*(yu-yd), las=x;
				else ;
			else if(y>yd) las=x, ++cnt;
			yu=y;
		}
		else
		{
			int x=down[j].x,y=down[(j++)+tag].y;
			if(yu>yd)
				if(y<yu)
					if(las<INF) Ans[cnt]+=1ll*(x-las)*(yu-yd), las=x;
					else ;
				else Ans[cnt]+=1ll*(x-las)*(yu-yd), las=INF;
			yd=y;
		}
	}
	if(las<INF) --cnt;
	LL ans=0;
	for(int i=1; i<=cnt; ans+=Ans[i++]);
	printf("%d %lld\n",cnt,ans);

	return 0;
}
