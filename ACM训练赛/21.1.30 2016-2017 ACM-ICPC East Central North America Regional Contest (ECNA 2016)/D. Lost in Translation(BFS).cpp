/*
31ms	4000KB
深度要最小：用BFS！深度最小时可以更新dis。
怎么就忘了最简单的那种BFS分层呢。（注意一下状态数）
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
using namespace std;
typedef long long LL;
const int N=1e5+5;

bool vis[N];
int dep[N];
LL dis[N];
struct Node2
{
	int x,dep;
	LL val;
};

struct Node{
	int to,val;
};
vector<Node> e[N];
map<string,int> mp;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read()+1,m=read();
	string s="English",t; mp[s]=1;
	for(int i=2; i<=n; ++i) cin>>s, mp[s]=i;
	int tot=n;
	for(int i=1,u,v,w; i<=m; ++i)
	{
		cin>>s, cin>>t;
		u=mp[s], v=mp[t], w=read();
		e[u].push_back((Node){v,w}), e[v].push_back((Node){u,w});
	}

	static std::queue<Node2> q;
	LL ans=0; q.push((Node2){1,0,0});
	memset(dis,0x3f,sizeof dis);
	for(int i=1; i<=n; ++i) dep[i]=N;
	while(!q.empty())
	{
		Node2 p=q.front(); q.pop();
		int x=p.x;
		dep[x]=std::min(dep[x],p.dep);
		if(p.dep==dep[x]) dis[x]=std::min(dis[x],p.val);
		if(vis[x]) continue;
		vis[x]=1;
		for(auto v:e[x])
			q.push((Node2){v.to,p.dep+1,v.val});
	}
	for(int i=1; i<=n; ++i)
		if(!vis[i]) return puts("Impossible"),0;
		else ans+=dis[i];
	printf("%lld\n",ans);
	

	return 0;
}
