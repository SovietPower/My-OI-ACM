/*
1684ms	23800KB
$Description$
$q$次操作，每次给定点的坐标$(x,y)$，表示加入一个点$(x,y)$，或删除一个点$(x,y)$，或询问：至少需要在平面中加入多少个点，才能使得当前所有点关于$(0,0)-(x,y)$这条直线对称。
$q\leq2\times10^5,\ 1\leq x,y\leq 112904$。
$Solution$
两个点关于$(0,0)-(x,y)$对称，则它们到原点的距离是一样的，即位于同一个圆上。
可以猜到的一个结论是，以原点为圆心画圆，交到整点上的点不会很多。即方程$x^2+y^2=r^2$的正整数解$(x,y)$不会很多。
所以每加入一个点$i$，枚举和它在一个圆上的点$j$，给$i,j$的对称轴的答案$-2$，$i$自己做对称轴的答案$-1$；删掉一个点$i$，就给$i,j$的对称轴的答案$+2$，给$i$做对称轴的答案$+1$。
对于询问直接输出即可。
*/
#include <map>
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5,M=113000;

std::set<pr> st[N];
std::map<LL,int> id;
std::map<int,int> Ans[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Getid(LL d)
{
	static int Index=0;
	return id.count(d)?id[d]:id[d]=++Index;
}
void Calc(int x,int y,int &xn,int &yn)
{
	int g=std::__gcd(x,y);//g!=0
	xn=x/g, yn=y/g;
}

int main()
{
	for(int Q=read(),tot=0; Q--; )
	{
		int opt=read(),x=read(),y=read(),xn,yn;
		if(opt==1)
		{
			int p=Getid(1ll*x*x+1ll*y*y);
			for(std::set<pr>::iterator it=st[p].begin(); it!=st[p].end(); ++it)
				Calc((*it).first+x,(*it).second+y,xn,yn), Ans[xn][yn]+=2;
			st[p].insert(mp(x,y)), Calc(x,y,xn,yn), ++Ans[xn][yn], ++tot;
		}
		else if(opt==2)
		{
			int p=Getid(1ll*x*x+1ll*y*y); st[p].erase(mp(x,y));
			for(std::set<pr>::iterator it=st[p].begin(); it!=st[p].end(); ++it)
				Calc((*it).first+x,(*it).second+y,xn,yn), Ans[xn][yn]-=2;
			Calc(x,y,xn,yn), --Ans[xn][yn], --tot;
		}
		else Calc(x,y,xn,yn), printf("%d\n",tot-Ans[xn][yn]);
	}

	return 0;
}
