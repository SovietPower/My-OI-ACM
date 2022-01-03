#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=105;

bool lk[N][N];
std::vector<pr> pos[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read();
	for(int i=1,u,v; i<=m; ++i) u=read(),v=read(),lk[u][v]=lk[v][u]=1;
	int r=1;
	for(int i=1; i<=n; ++i)
	{
		pos[i].push_back(mp(r,i));
		for(int j=i+1; j<=n; ++j)
			if(lk[i][j])
				pos[i].push_back(mp(r+j-1,i)),pos[j].push_back(mp(r+j-1,j));
		r+=n;
	}
	for(int i=1; i<=n; ++i)
	{
		int l;
		printf("%d\n",l=pos[i].size());
		for(int j=0; j<l; ++j) printf("%d %d\n",pos[i][j].first,pos[i][j].second);
	}

	return 0;
}
