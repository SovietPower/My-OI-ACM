/*
249ms	131600KB
$Description$
给定一个字符串s[1]。一个字符串序列s[]满足s[i]至少在s[i-1]中出现过两次(i>=2)。求最大的k，满足存在s[1]~s[k]。
$Solution$
一开始以为直接自底向上合并right，如果|right|>1就继续向上。这显然不对啊，这样出现次数>1不一定是在之前的子节点中出现次数>1。
如果串A出现在串B中两次，那么说明什么？用right(endpos)表示一个串出现位置的最右端点集合，则right(A)在s[right(B)-len(A),right(B)]中至少出现过两次。
而且对于在原串中在任意位置出现的B，A都满足上面的条件。
所以我们随便找一个pos[B]=某一个right(B)，A若在B中出现至少两次则满足right(A)在s[pos[B]-len(B)+len(A),pos[B]]中至少出现了两次（s为原串）。
所有节点的right我们可以通过线段树合并全部得到。
parent树上的父节点能转移到子节点。可以看出从上到下的DP，如果满足条件则更新，用B(子节点)作为新的A(下次匹配作为父节点)；不满足条件则保留之前的A（之前的父节点 更优）。
因为父节点$A$已经至少在子节点$B$中出现过一次了，所以只需要查$s[pos[B]-len(B)+len(A),pos[B]-1]$中是否存在$right(A)$（$A$的线段树中在该区间是否有值）。
（注意虽然$A$这里表示一个节点，似乎显然是用$mnlen(A)$更正确，而不是用$A$节点最长的串的长度$len(A)$，但是...实际上是没问题的，因为既然同在$A$节点...就有些奇妙的性质。不放心就写$mnlen$吧）
还是有一种神奇hash做法。。
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	static const int S=N*2*25;//最好是4nlogn...
	int tot,son[S][2];

	void Insert(int &x,int l,int r,int p)
	{
		/*if(!x)*/ x=++tot;
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) Insert(ls,l,m,p);
		else Insert(rs,m+1,r,p);
	}
	bool Query(int x,int l,int r,int L,int R)
	{
		if(!x) return 0;
		if(L<=l && r<=R) return 1;//有这个节点即可 
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(ls,l,m,L,R)||Query(rs,m+1,r,L,R);
			else return Query(ls,l,m,L,R);
		else return Query(rs,m+1,r,L,R);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x|y;
		int now=++tot;//!
		son[now][0]=Merge(ls,son[y][0]), son[now][1]=Merge(rs,son[y][1]);
		return now;
	}
};
struct Suffix_Automaton
{
	static const int S=N<<1;
	int n,tot,las,len[S],pos[S],son[S][26],fa[S],tm[S],A[S],root[S],f[S],top[S];
	Segment_Tree T;

	Suffix_Automaton() {tot=las=1;}
	void Insert(int c,int id)
	{
		int np=++tot,p=las;
		len[las=np]=len[p]+1, pos[np]=id;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1, pos[nq]=pos[q]/*!*/;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Solve()
	{
		n=read(); register char c=gc(); for(;!isalpha(c);c=gc());
		Insert(c-'a',1),T.Insert(root[las],1,n,1);
		for(int i=2; i<=n; ++i) Insert(gc()-'a',i),T.Insert(root[las],1,n,i);

		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=n; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;

		for(int i=tot,x=A[i]; i>1; x=A[--i]) root[fa[x]]=T.Merge(root[fa[x]],root[x]);
		int ans=1;
		for(int i=2,x=A[i],tp; i<=tot; x=A[++i])
		{
			if(fa[x]==1) {f[x]=1, top[x]=x; continue;}
			tp=top[fa[x]];
			if(T.Query(root[tp],1,n,pos[x]-len[x]+len[tp],pos[x]-1))//or pos[x]-len[x]+len[fa[tp]]+1
				f[x]=f[tp]+1, top[x]=x, ans=std::max(ans,f[x]);
			else f[x]=f[tp], top[x]=tp;
		}
		printf("%d\n",ans);
	}
}sam;

int main()
{
	sam.Solve();
	return 0;
}
