#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=12;
const int d0x[]={-1,-2,-2,-1,1,2,2,1},d0y[]={-2,-1,1,2,2,1,-1,-2};
const int d1x[]={-1,-1,1,1},d1y[]={-1,1,1,-1};

int n,A[N][N];
struct Node
{
	int x,y,now,lasw,way,c1,c2;
};

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void BFS()
{
	static bool vis[N][N][102][4][3];
	static std::queue<Node> q;
	int sx=0,sy=0,ed=n*n,ans1=1e9,ans2=1e9;
	for(int i=1; i<=n&&!sx; ++i)
		for(int j=1; j<=n; ++j) if(A[i][j]==1) {sx=i,sy=j; break;}

	vis[sx][sy][1][3][0]=vis[sx][sy][1][3][1]=vis[sx][sy][1][3][2]=1;
	q.push((Node){sx,sy,1,3,0,0,0});//Âí Ê¿ ³µ 
	q.push((Node){sx,sy,1,3,1,0,0});
	q.push((Node){sx,sy,1,3,2,0,0});
	while(!q.empty())
	{
		Node tmp=q.front(); q.pop();
		int x=tmp.x,y=tmp.y,now=tmp.now,lasw=tmp.lasw,way=tmp.way,c1=tmp.c1,c2=tmp.c2;
		if(c1>ans1||(c1==ans1&&c2>=ans2)) continue;
		if(A[x][y]==now) ++now;
		if(now>ed)
		{
//			printf("Get! x:%d y:%d now:%d way:%d c1:%d c2:%d\n",x,y,now,way,c1,c2);
			if(c1<ans1) ans1=c1,ans2=c2;
			else if(c1==ans1) ans2=std::min(ans2,c2);
			continue;
		}
//		if(!way) printf("Ma: ");
//		else if(way==1) printf("Shi: ");
//		else printf("Ju: ");
//		if(way==1)printf("Now(%d): x:%d y:%d now:%d lasw:%d way:%d c1:%d c2:%d\n",A[x][y],x,y,now,lasw,way,c1,c2);
		int w=way; ++c1;
		if(!w)
		{
			for(int i=0,xn,yn; i<8; ++i)
			{
				xn=x+d0x[i],yn=y+d0y[i];
				if(xn<1||xn>n||yn<1||yn>n||vis[xn][yn][now][lasw][w]) continue;
				vis[xn][yn][now][lasw][w]=1, q.push((Node){xn,yn,now,lasw,w,c1,c2});
			}
		}
		else if(w==1)
		{
			for(int i=0,xn,yn; i<4; ++i)
			{
				xn=x+d1x[i],yn=y+d1y[i];
				if(xn<1||xn>n||yn<1||yn>n||vis[xn][yn][now][lasw][w]) continue;
				vis[xn][yn][now][lasw][w]=1, q.push((Node){xn,yn,now,lasw,w,c1,c2});
			}
		}
		else if(w==2)
		{
			for(int xn=1; xn<=n; ++xn)
			{
				if(x==xn||vis[xn][y][now][lasw][w]) continue;
				vis[xn][y][now][lasw][w]=1, q.push((Node){xn,y,now,lasw,w,c1,c2});
			}
			for(int yn=1; yn<=n; ++yn)
			{
				if(y==yn||vis[x][yn][now][lasw][w]) continue;
				vis[x][yn][now][lasw][w]=1, q.push((Node){x,yn,now,lasw,w,c1,c2});
			}
		}
		lasw=way, ++c2;
		for(w=0; w<3; ++w)
			if(w!=way)
			{
				if(vis[x][y][now][lasw][w]) continue;
				vis[x][y][now][lasw][w]=1, q.push((Node){x,y,now,lasw,w,c1,c2});
			}
	}
	printf("%d %d\n",ans1,ans2);
}

int main()
{
//	freopen(".out","w",stdout);
	n=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) A[i][j]=read();
	BFS();

	return 0;
}
