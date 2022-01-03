/*
记与起点相邻的点的集合为S。建反向图BFS。如果有一个点能从S中的两个点到达，则不行。
*/
#include <bits/stdc++.h>
#define pr pair<int,int>
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
using namespace std;
const int N = 1e5+10;

vector<int> e[N],vec;
int is[N], vis[N], tmp[N];
bool ban[N];
queue<pr> q;

int main()
{
	int n, m, t; cin>>n>>m>>t;
	for(int i=0; i<m; i++)
	{
		int u, v; scanf("%d%d",&u,&v);
		e[v].pb(u);
	}
	memset(is, 0, sizeof(is));
	memset(vis, 0, sizeof(vis));
	for(auto &y: e[t]) q.push(mp(y,y)), is[y] = 1;

	vis[t] = N;
	while(!q.empty())
	{
		int x=q.front().first,pre=q.front().second; q.pop();
		if(x!=pre) ban[x]=1;//, printf("ban x:%d pre:%d\n",x,pre);
		for(auto &v:e[x])
		{
			if(vis[v]>=2||v==pre) continue;
			if(vis[v]==1 && tmp[v]==pre) continue;
			else if(!vis[v]) tmp[v]=pre;
			++vis[v], q.push(mp(v,pre));
		}
	}
	for(int i=0; i<n; i++)
		if(is[i] && !ban[i]) vec.pb(i);
	cout<<vec.size()<<endl;
	for(auto &x: vec) printf("%d\n",x);

	return 0;
}/*
4 4 4
1 2 2 3 3 1 3 4
5 7 0
1 2 2 3 3 1 3 0 4 0 3 4 4 2
8 11 0
1 4 1 2 4 2 2 3 3 1 3 0 2 5 5 0 5 6 6 7 7 2
12 15 0
1 4 1 2 4 2 2 3 3 1 3 0
7 2 6 7 5 6 5 0
2 8 8 9 9 10 10 11 11 5
*/
