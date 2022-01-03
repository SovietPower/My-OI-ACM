/*
171ms	98200KB
$Description$
有一张$n$个点的完全图，每个点的权值为$a_i$，两个点之间的边权为$a_i xor a_j$。求该图的最小生成树。
$n<=2*10^5,0<=ai<2^{30}$。
$Solution$
代码好神啊。
依旧是从高到低考虑每一位。对于当前位i，如果所有点在这一位都为0或1，不需要管（任何边在这一位都为0）。
否则可以把点分为两个集合，即i位为0和1的集合，这两个集合间必须存在一条边，且边权这一位只能为1。
考虑怎么高效得到两个集合间的最小边。可以将一个集合的$a_i$插入Trie，再枚举另一个集合的点在Trie上走。
这样枚举每一位然后合并两个集合的点，再递归到两边(该位为0或1)，就可以得到MST了。这也是Boruvka算法的过程，不过用Trie可以将每次需$O(m)$的迭代优化到$O(n\log a_{max})$。
实现细节：可以先对所有点建Trie，并直接在Trie树上DFS，存在左右儿子时即会分为两个集合。
将$a_i$从小到大插入Trie，这样可对每个节点维护一个区间，表示 满足根到该节点01取值 的序列下标区间。这样枚举时就不需要暴力$O(n)$了。
复杂度$O(n\log n\log a_{max})$。基本到不了吧。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define BIT 29
typedef long long LL;
const int N=2e5+5;

int read();
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define S N*31
	int n,A[N],tot,son[S][2],L[S],R[S];
	LL Ans;
	#undef S

	void Insert(int v,int id)
	{
		int x=0;
		for(int i=BIT; ~i; --i)
		{
			int c=v>>i&1;
			if(!son[x][c]) son[x][c]=++tot, L[tot]=R[tot]=id;
			x=son[x][c];
			L[x]=std::min(L[x],id), R[x]=std::max(R[x],id);
		}
	}
	int Query(int x,int v,int bit)
	{
		if(bit<0||L[x]==R[x]) return A[L[x]];//同样注意第0位还可以继续递归== 
		int c=v>>bit&1;
		return son[x][c]?Query(son[x][c],v,bit-1):(son[x][c^1]?Query(son[x][c^1],v,bit-1):0);
	}
	void DFS(int x,int bit)
	{
//		if(bit<0) return;
		if(!bit)
		{
			if(ls&&rs) Ans+=A[L[ls]]^A[L[rs]];//第0位还会有分叉 
			return;
		}
		if(ls&&rs)
		{
			int res=0x7fffffff;
			for(int i=L[ls],r=R[ls],p=rs; i<=r; ++i)
				res=std::min(res,A[i]^Query(p,A[i],bit-1));
			Ans+=res;
		}
		if(ls) DFS(ls,bit-1);
		if(rs) DFS(rs,bit-1);
	}
	void Solve()
	{
		n=read();
		for(int i=1; i<=n; ++i) A[i]=read();
		std::sort(A+1,A+1+n);
		for(int i=1; i<=n; ++i) Insert(A[i],i);
		DFS(0,BIT), printf("%I64d\n",Ans);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	T.Solve();
	return 0;
}
