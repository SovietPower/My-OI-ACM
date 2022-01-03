/*
62ms	4100KB
因为BFS一般是可以保证到达一个点时代价最小，所以考虑BFS。
本题有向左和向右两个代价。显然如果上下没有格子阻碍，我们可以先一直向上下扩展状态。
然后，如果一直向左或是向右，那么BFS到的点显然代价最小。
如果要走回头路（即直接向上的路被堵住，但能绕上去），那么假设向左边走要走$a$步才能向右走绕回去，向右边走要$b$步才能向左走绕回去。那么前者向右也要走$a$步，后者向左也要走$b$步。所以我们只保证向左走的步数尽量少，就可以保证到达某一个点时向右走的步数也尽量少。好像也很符合BFS性质？直接BFS？
但是向左走的步数少不代表距离近。比如下图，起点为白点，要到达绿点，显然从白点向左出发到它花费少（花费指向左向右的步数）。但是如果直接BFS，因为左边上上下下浪费了时间，所以实际先到绿点的是向白点右边出发的路径。这当然不优（花费多）。
因为向上向下是不计代价的（也就是距离为$0$），所以BFS到一个点时，要把它上下能直接到的点同时加入队列（代价相同，也就是距离相同，当然在BFS里要同时入队），而不是在把它弹出队首时才在队列中加入上下的点（BFS的意义？后加入的点花费/距离比之前的点高。但实际它们代价是一样的）。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2005;
const int D[]={-1,1};

int n,m,r,c,X,Y;
bool ok[N][N];
struct Node
{
	int x,y,r1,r2;
};
std::queue<Node> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Extend(int x,int y,int r1,int r2)
{
	for(int i=x; ok[i][y]; --i)
		ok[i][y]=0, q.push((Node){i,y,r1,r2});
	for(int i=x+1; ok[i][y]; ++i)
		ok[i][y]=0, q.push((Node){i,y,r1,r2});
}
void BFS()
{
	int ans=0;
	Extend(r,c,X,Y);
	while(!q.empty())
	{
		++ans;
		Node tmp=q.front(); q.pop();
		int x=tmp.x,y=tmp.y,r1=tmp.r1,r2=tmp.r2;
		if(r1&&ok[x][y-1]) Extend(x,y-1,r1-1,r2);
		if(r2&&ok[x][y+1]) Extend(x,y+1,r1,r2-1);
	}
	printf("%d\n",ans);
}

int main()
{
	n=read(),m=read(),r=read(),c=read(),X=read(),Y=read();
	for(int i=1; i<=n; ++i)
	{
		register char c=gc(); while(c!='*'&&c!='.') c=gc();
		ok[i][1]=c=='.';
		for(int j=2; j<=m; ++j) ok[i][j]=gc()=='.';
	}
	BFS();

	return 0;
}
