#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define pb push_back
#define fir first
#define sec second
#define mp std::make_pair
#define pr std::pair<int,int>

#include "graph.h"

const int N=233,M=N*N/2;

int Enum,H[N],nxt[N<<1],to[N<<1],col[N];
pr e[M];
bool tag[M];

inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x)
{
	for(int i=H[x],v; i; i=nxt[i])
		if(!col[v=to[i]]) col[v]=3-col[x], DFS(v);
}
std::vector<int> check_bipartite(int n)//2(n-1)logn+n-1
{
	int m=0;
	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j) e[++m]=mp(i,j);
	for(int T=n-1,now=1; T--; )
	{
		int l=now,r=m,mid;
		while(l<r)
		{
			int mid=l+r>>1;
			std::vector<pr> q;
			for(int i=1; i<=mid; ++i) if(!tag[i]) q.push_back(e[i]);
			if(query(q)) l=mid+1;
			else r=mid;
		}
		AE(e[r].fir,e[r].sec), tag[r]=1, now=r+1;
	}
	std::vector<int> ans;
	col[0]=1, DFS(0);
	for(int i=1; i<=m; ++i)//Check if it's a Bipartite Graph
		if(tag[i])
		{
			std::vector<pr> q; q.push_back(e[i]);
			for(int j=1; j<=m; ++j)
				if(!tag[j] && col[e[j].fir]!=col[e[j].sec]) q.push_back(e[j]);
			if(query(q)) return ans;
		}
	for(int i=0; i<n; ++i) if(col[i]==1) ans.push_back(i);
	return ans;
}
