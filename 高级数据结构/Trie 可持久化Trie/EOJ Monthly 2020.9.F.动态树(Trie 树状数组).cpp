/*
1.162s	486.703MB
$Description$
维护一棵树，有两种操作：
1.Add x,y，插入一个节点，父节点为$x$边权为$y$。
2.Query x,y，查询起点为$x$，终点在$y$的子树中的最大简单路径边权异或和。
$Solution$
**Sol 1**
先离线求出树的DFS序，以及$val[x]$表示$1$号点到$x$的路径权值异或和，每次查询即求一个$y$子树中与$val[x]$异或最大的$val[z]$。
$y$子树即一个区间，用线段树套Trie就ok了。
每次$Add$将$val[node]$插入包含它的所有区间的Trie，每次$Query$求一下区间中与$val[x]$异或的最大值。
复杂度$O(q\log q\log v)$。
**Sol 2**
依旧离线先求DFS序。注意到 查询其实就是序列上一个区间的查询，在可持久化Trie中用$Trie[r]-Trie[l-1]$的$size$就可以解决。
那么修改就应该是前缀的插入Trie，用树状数组套Trie就ok了。查询时$r$和$l-1$在树状数组上的所有节点都需要考虑。
复杂度$O(q\log q\log v)$，常数比线段树小很多。
**Sol 3**
同$Sol 2$，注意到 查询其实就是序列上一个区间的查询，我们可以分块。
对每个块建一棵Trie，插入时插入对应块的Trie。查询时对整块查Trie，零散部分直接$O(\sqrt n)$次$O(1)$查询。
设块大小为$s$，$Add$次数为$n$，$Query$次数为$m$，复杂度$O(n\log v+m(\frac ns\log v+2s))=O(n\log v+m\sqrt(n\log v))$，常数非常非常小。
ps:
注意1号节点要插入权值0。
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define BIT 30
#define gc() getchar()
//#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int cnt,Enum,H[N],nxt[N],val[N],L[N],R[N];
//char IN[MAXIN],*SS=IN,*TT=IN;
struct Queries
{
	int opt,x,y;
}q[N];
struct TRIE
{
	#define S N*19*31
	int tot,son[S][2],sz[S];
	#undef S
	void Insert(int x,int v)
	{
		++sz[x];
		for(int i=BIT; ~i; --i)
		{
			int c=v>>i&1;
			if(!son[x][c]) son[x][c]=++tot;
			x=son[x][c], ++sz[x];
		}
	}
	int Query(int x,int v)
	{
		if(!x) return 0;
		int res=0;
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1;
			son[x][c]?res|=1<<i:c^=1;
			x=son[x][c];
		}
		return res;
	}
}Trie;
struct Bit
{
	int n,root[N];
	std::vector<int> v1,v2;
	#define lb(x) (x&-(x))
	void Modify(int p,int v)
	{
		for(; p<=n; p+=lb(p))
			!root[p]&&(root[p]=++Trie.tot), Trie.Insert(root[p],v);
	}
	void GetP(int p,std::vector<int> &vec)
	{
		for(; p; p^=lb(p)) vec.push_back(root[p]);
	}
	int Query(int l,int r,int v)
	{
		std::vector<int>().swap(v1), std::vector<int>().swap(v2);
		GetP(l-1,v1), GetP(r,v2);
		int res=0;
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1,s=0;
			for(auto j:v1) s-=Trie.sz[Trie.son[j][c]];
			for(auto j:v2) s+=Trie.sz[Trie.son[j][c]];
			s>0?res|=1<<i:c^=1;
			for(auto &j:v1) j=Trie.son[j][c];
			for(auto &j:v2) j=Trie.son[j][c];
		}
		return res;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline bool GetOpt()
{
	char c=gc();
	while(!isalpha(c)) c=gc();
	return c=='Q';
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v;
}
void DFS(int x)
{
	static int Index=0;
	L[x]=++Index;
	for(int v=H[x]; v; v=nxt[v]) DFS(v);
	R[x]=Index;
}

int main()
{
	int Q=read(); cnt=1;
	for(int i=1,x; i<=Q; ++i)
		switch(GetOpt())
		{
			case 0: x=read(),val[++cnt]=val[x]^read(),AE(x,cnt),q[i]=(Queries){0,x,cnt}; break;
			case 1: x=read(),q[i]=(Queries){1,x,read()}; break;
		}
	DFS(1);

	T.n=cnt, T.Modify(1,0);
	for(int i=1; i<=Q; ++i)
		switch(q[i].opt)
		{
			case 0: T.Modify(L[q[i].y],val[q[i].y]); break;
			case 1: printf("%d\n",T.Query(L[q[i].y],R[q[i].y],val[q[i].x])); break;
		}

	return 0;
}
