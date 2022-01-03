/*
4955ms	1584kb
**Subtask1：**
暴力的话，猜可以$2^n$枚举点集$A,B$，将除了$A,B$之间的边全部删掉，然后询问。一定有至少一组$A,B$返回连通。
设二分图两边的点集分别是$S,T$，能猜到此时$S=A,T=B$。假设$S\cap A\neq\emptyset$且$T\cap A\neq\emptyset$，那$A,B$连通说明$S,T$通过同一个点连通，显然不会，因此$T\cap A=\emptyset$。同理$S\cap B\neq\emptyset$。所以有$S=A,T=B$。询问次数$O(2^n)$。
**Subtask2：**
如果图是二分图，考虑找到原图的一棵生成树，然后就可以黑白染色找出$S$了。
尝试依次删掉图中所有边。如果删掉一条边时由连通变为不连通，说明它在生成树上，保留这条边，否则删掉这条边。最终一定剩下$n-1$条边，就是原图的生成树。
询问次数$O(\frac{n(n-1)}{2})$。
**Subtask3：**
找生成树时一条一条枚举边太慢了，可以二分。如果删掉$1\sim mid$中的边图仍连通，就删掉，否则找到那条必须边保留。
这样的事件会进行$n-1$次，每次需要二分$\log\frac{n(n-1)}{2}\approx2\log n$次。
黑白染色后得到$S,T$，只靠生成树是可以连接$S,T$的。如果图不是二分图，那么把$S,T$之间的非树边全删掉，一定存在某一条树边，使得删掉这条树边后图仍连通。
总询问次数$2(n-1)\log n+n-1$。
**Subtask4：**
考虑对点二分，把二分时$2$的常数去掉。
枚举每个点，二分它与哪个点之间的边必须保留即可。
询问次数$n\log n$。
*/
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

#include "graph.h"

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
