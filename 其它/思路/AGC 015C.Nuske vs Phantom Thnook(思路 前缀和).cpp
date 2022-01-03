/*
89ms	52864KB
$Description$
给定n*m的蓝白矩阵，保证蓝格子形成的的同一连通块内，某蓝格子到达另一个蓝格子的路径唯一。
Q次询问。每次询问一个子矩形内蓝格子组成的连通块数。
$Solution$
不会形成环，即一个连通块是一棵树，即点数=边数+1。
那么对于一个子矩形，求它里面的蓝格子数n和蓝格子之间的边数m，n-m就是连通块数了。
横边竖边分开，都用前缀和维护。
如果有环，则边数>=点数就没法做了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2005;

int sp[N][N],sr[N][N]/*crosswise*/,sc[N][N]/*lengthways*/;
bool mp[N][N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),Q=read();
	for(int i=1; i<=n; ++i)
	{
		register char c=gc(); for(;!isdigit(c);c=gc());
		mp[i][1]=c-'0';
		for(int j=2; j<=m; mp[i][j++]=gc()-'0');
	}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			if(mp[i][j])
				sp[i][j]=sp[i-1][j]+sp[i][j-1]-sp[i-1][j-1]+1,
				sc[i][j]=sc[i-1][j]+sc[i][j-1]-sc[i-1][j-1]+mp[i-1][j],
				sr[i][j]=sr[i-1][j]+sr[i][j-1]-sr[i-1][j-1]+mp[i][j-1];
			else
				sp[i][j]=sp[i-1][j]+sp[i][j-1]-sp[i-1][j-1],
				sc[i][j]=sc[i-1][j]+sc[i][j-1]-sc[i-1][j-1],
				sr[i][j]=sr[i-1][j]+sr[i][j-1]-sr[i-1][j-1];
		}
	for(int x,y,x2,y2; Q--; )
	{
		x=read(),y=read(),x2=read(),y2=read();
		int p=sp[x2][y2]-sp[x-1][y2]-sp[x2][y-1]+sp[x-1][y-1],
			e=sr[x2][y2]-sr[x-1][y2]-sr[x2][y]+sr[x-1][y]+sc[x2][y2]-sc[x][y2]-sc[x2][y-1]+sc[x][y-1];
		printf("%d\n",p-e);
	}
	return 0;
}
