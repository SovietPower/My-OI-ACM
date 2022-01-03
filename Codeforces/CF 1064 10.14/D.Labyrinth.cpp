#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2005;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

const int D[]={-1,1};
int n,m,r,c,X,Y;
char s[N];
bool mp[N][N],vis[N][N];
struct Node
{
	int x,y,r1,r2;
};
std::queue<Node> q;

void BFS()
{
	int ans=0;
	q.push((Node){r,c,X,Y});
	vis[r][c]=1;
	while(!q.empty())
	{
		++ans;
		Node tmp=q.front(); q.pop();
		int x=tmp.x,y=tmp.y,r1=tmp.r1,r2=tmp.r2;
		for(int i=x-1; i>0; --i)
		{
			if(!mp[i][y]) break;
			if(vis[i][y]) break;//continue;
			vis[i][y]=1, q.push((Node){i,y,r1,r2});
		}
		for(int i=x+1; i<=n; ++i)
		{
			if(!mp[i][y]) break;
			if(vis[i][y]) break;//continue;
			vis[i][y]=1, q.push((Node){i,y,r1,r2});
		}
		for(int i=0; i<2; ++i)
		{
			int yn=y+D[i];
			if(!mp[x][yn]||vis[x][yn]) continue;
			vis[x][yn]=1;
			if(r1>0&&i==0) q.push((Node){x,yn,r1-1,r2});
			if(r2>0&&i==1) q.push((Node){x,yn,r1,r2-1});
		}
	}
	printf("%d\n",ans);
}

int main()
{
	n=read(),m=read(),r=read(),c=read(),X=read(),Y=read();
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s+1);
		for(int j=1; j<=m; ++j)
			if(s[j]=='.') mp[i][j]=1;
			else mp[i][j]=0;
	}
	BFS();

	return 0;
}
