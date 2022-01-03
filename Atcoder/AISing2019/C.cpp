#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pc putchar
//#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define ID(x,y) ((x-1)*m+y)
typedef long long LL;
const int N=405,Way[]={1,0,-1,0,1};

int n,m,mp[N][N],vis[N][N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
LL DFS(int X,int Y)
{
	static int qx[N*N],qy[N*N];
	int h=0,t=1,c[2]={0,0}; qx[0]=X, qy[0]=Y, vis[X][Y]=1;
	while(h<t)
	{
		int x=qx[h],y=qy[h++];
		++c[mp[x][y]];
		for(int i=0,xn,yn; i<4; ++i)
			if((xn=x+Way[i]) && xn<=n && (yn=y+Way[i+1]) && yn<=m && !vis[xn][yn] && mp[xn][yn]^mp[x][y])
				vis[xn][yn]=1, qx[t]=xn, qy[t++]=yn;
	}
	return 1ll*c[0]*c[1];
}

int main()
{
	static char s[N];
	n=read(),m=read();
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s+1);//black:0 white:1
		for(int j=1; j<=m; ++j) mp[i][j]=s[j]=='.';
	}
	LL ans=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(!vis[i][j] && !mp[i][j]) ans+=DFS(i,j);
	printf("%lld\n",ans);

	return 0;
}
