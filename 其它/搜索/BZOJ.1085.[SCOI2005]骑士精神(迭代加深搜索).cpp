/*
820kb	84ms
最小步数这类，适合用迭代加深搜索。
用空格走代替骑士。
搜索时记录上一步防止来回走。
不需要每次判断是否都在位置，可以计算出不在对应位置的骑士有多少个。而且每次复原一个骑士至少需要一步。
空格是不计算未复原骑士数的。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define n (5)
typedef long long LL;
const int way_x[9]={1,1,2,2,-2,-2,-1,-1},way_y[9]={2,-2,1,-1,1,-1,2,-2};
const int End[6][6]=
{{0},
{0,1,1,1,1,1},
{0,0,1,1,1,1},
{0,0,0,2,1,1},
{0,0,0,0,0,1},
{0,0,0,0,0,0},
};

int mp[7][7];
char s[10];

bool DFS(int x,int y,int left,int sum,int las)
{
	if(sum>left) return 0;
	if(!sum) return 1;
	for(int xn,yn,res,i=0; i<8; ++i)
		if(i!=7-las&&(xn=x+way_x[i])>0&&(yn=y+way_y[i])>0&&xn<=n&&yn<=n)
		{
			res=sum;
			if(mp[xn][yn]==End[xn][yn]) ++res;

			std::swap(mp[x][y],mp[xn][yn]);

			if(mp[x][y]==End[x][y]) --res;

			bool f=DFS(xn,yn,left-1,res,i);
			if(f) return 1;
			std::swap(mp[x][y],mp[xn][yn]);
		}
	return 0;
}

int main()
{
	int T,sx,sy,init; scanf("%d",&T);
	while(T--)
	{
		for(int i=1; i<=n; ++i)
		{
			scanf("%s",s+1);
			for(int j=1; j<=n; ++j)
				if(s[j]!='*') mp[i][j]=s[j]-'0';
				else mp[i][j]=2,sx=i,sy=j;
		}
		init=0;
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				if(mp[i][j]!=End[i][j]) ++init;//init:至少需要多少步。
		if(sx!=3||sy!=3) --init;//空格不计算未复原骑士数。
//		printf("init:%d\n",init);
		for(int dep=init; ; ++dep)
			if(dep==16) {puts("-1"); break;}
			else if(DFS(sx,sy,dep,init,8)) {printf("%d\n",dep); break;}
	}
	return 0;
}
