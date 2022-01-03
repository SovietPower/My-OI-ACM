#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define pb push_back
#define fir first
#define sec second
#define mp std::make_pair
#define pr std::pair<int,int>

//-------------
#include <assert.h>
#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
//#define mp make_pair
#define x first
#define y second
//#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

//#include "graph.h"
//#include "graderlib.cpp"
static const int maxn = 210;

static int _n;
static bool _adj[maxn + 5][maxn + 5];

void init(int n) 
{
	_n = n;
	int m;
	assert(scanf("%d", &m) == 1);
	memset(_adj, 0, sizeof _adj);
	REP(i, 0, m)
	{
		int u, v;
		assert(scanf("%d%d", &u, &v) == 2);
		_adj[u][v] = _adj[v][u] = 1;
	}
}

static int _pa[maxn + 5];

static int _get(int x) { return _pa[x] == x ? x : _pa[x] = _get(_pa[x]); }

bool query(std::vector<pr> banned_edges)
{
	static bool banned[maxn + 5][maxn + 5];
	memset(banned, 0, sizeof banned);
	REP(i, 0, SZ(banned_edges)) 
	{
		banned[banned_edges[i].x][banned_edges[i].y] = 1;
		banned[banned_edges[i].y][banned_edges[i].x] = 1;
	}
	REP(i, 0, _n) _pa[i] = i;
	REP(i, 0, _n) REP(j, 0, _n - 1)
		if (_adj[i][j] && !banned[i][j]) _pa[_get(i)] = _get(j);
	REP(i, 1, _n) if (_get(i) != _get(0)) return 0;
	return 1;
}

//-------------

//#include "graph.h"

const int N=233;

int Enum,H[N],nxt[N<<1],to[N<<1],col[N];
bool tag[N][N];
std::vector<pr> tr;

inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x)
{
	for(int i=H[x],v; i; i=nxt[i])
		if(!col[v=to[i]]) tag[x][v]=tag[v][x]=1, tr.push_back(mp(x,v)), col[v]=col[x]^1, DFS(v);
}
std::vector<int> check_bipartite(int n)
{
	std::vector<pr> q;
	for(int x=0; x+1<n; ++x)
	{
		int now=x+1;
		while(now<n)
		{
			for(int i=now; i<n; ++i) q.push_back(mp(x,i));
			if(query(q)) break;
			for(int i=now; i<n; ++i) q.pop_back();
			int l=now,r=n-1,mid;
			while(l<r)
			{
				int mid=l+r>>1;
				for(int i=l; i<=mid; ++i) q.push_back(mp(x,i));
				if(query(q)) l=mid+1;
				else r=mid;
				for(int i=l; i<=mid; ++i) q.pop_back();
			}
			AE(x,l), now=l+1;
		}
	}
	col[0]=2, DFS(0);
	std::vector<int> ans; q.clear();
	for(int i=0; i<n; ++i)//Check if it's a Bipartite Graph
		for(int j=i+1; j<n; ++j)
			if(col[i]!=col[j] && !tag[i][j]) q.push_back(mp(i,j));
	for(int i=0,l=tr.size(); i<l; ++i)
	{
		q.push_back(tr[i]);
		if(query(q)) return ans;
		q.pop_back();
	}
	for(int i=0; i<n; ++i) if(col[i]==2) ans.push_back(i);
	return ans;
}

//--------------

int main() 
{
	freopen("graph3.in","r",stdin);
	int n;
	assert(scanf("%d", &n) == 1);
	init(n);
	std::vector<int> out = check_bipartite(n);
	printf("%d\n", SZ(out));
	REP(i, 0, SZ(out)) printf("%d ", out[i]);
	printf("\n");
    return 0;
}
