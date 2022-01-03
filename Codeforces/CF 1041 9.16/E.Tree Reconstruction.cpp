//构造方式是一次确定一条链。倒序加入queue就不用priority_queue了。。so复杂度O(n)。
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n,dis[N];
bool lk[N][N];
std::priority_queue<int> q0,q1;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int u,v,i=1; i<n; ++i)
	{
		u=read(),v=read();
		if(v!=n) return puts("NO"),0;
		++dis[u];
	}
	int sum=0;
	for(int i=1; i<n; ++i)
		if(!dis[i]) q0.push(i);
		else q1.push(i), sum+=dis[i]-1;
	if(q0.size()!=sum) return puts("NO"),0;
	while(!q1.empty())
	{
		int x=q1.top(); q1.pop();
		int y=n,z;
		for(int i=1; i<dis[x]; ++i)
		{
			z=q0.top(); q0.pop();
			if(z>x) return puts("NO"),0;
			lk[y][z]=1, y=z;
		}
		lk[x][y]=1;
	}
	puts("YES");
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(lk[i][j]) printf("%d %d\n",i,j);

	return 0;
}
