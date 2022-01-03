/*
1.162s	486.703MB
$Description$
ά��һ�����������ֲ�����
1.Add x,y������һ���ڵ㣬���ڵ�Ϊ$x$��ȨΪ$y$��
2.Query x,y����ѯ���Ϊ$x$���յ���$y$�������е�����·����Ȩ���͡�
$Solution$
**Sol 1**
�������������DFS���Լ�$val[x]$��ʾ$1$�ŵ㵽$x$��·��Ȩֵ���ͣ�ÿ�β�ѯ����һ��$y$��������$val[x]$�������$val[z]$��
$y$������һ�����䣬���߶�����Trie��ok�ˡ�
ÿ��$Add$��$val[node]$��������������������Trie��ÿ��$Query$��һ����������$val[x]$�������ֵ��
���Ӷ�$O(q\log q\log v)$��
**Sol 2**
������������DFS��ע�⵽ ��ѯ��ʵ����������һ������Ĳ�ѯ���ڿɳ־û�Trie����$Trie[r]-Trie[l-1]$��$size$�Ϳ��Խ����
��ô�޸ľ�Ӧ����ǰ׺�Ĳ���Trie������״������Trie��ok�ˡ���ѯʱ$r$��$l-1$����״�����ϵ����нڵ㶼��Ҫ���ǡ�
���Ӷ�$O(q\log q\log v)$���������߶���С�ܶࡣ
**Sol 3**
ͬ$Sol 2$��ע�⵽ ��ѯ��ʵ����������һ������Ĳ�ѯ�����ǿ��Էֿ顣
��ÿ���齨һ��Trie������ʱ�����Ӧ���Trie����ѯʱ�������Trie����ɢ����ֱ��$O(\sqrt n)$��$O(1)$��ѯ��
����СΪ$s$��$Add$����Ϊ$n$��$Query$����Ϊ$m$�����Ӷ�$O(n\log v+m(\frac ns\log v+2s))=O(n\log v+m\sqrt(n\log v))$�������ǳ��ǳ�С��
ps:
ע��1�Žڵ�Ҫ����Ȩֵ0��
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
