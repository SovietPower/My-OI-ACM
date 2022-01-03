/*
0.11s	35M
$Description$
给定一棵$n$个点的树，每个点是黑色或白色。两个人轮流操作，每次可以选一个白色的点，将它到根节点路径上的所有点染黑。不能操作的人输，求先手是否能赢。如果能，输出第一步选择哪些节点能赢。
$n\leq10^5$。
$Solution$
对于叶子节点，如果能染色，$SG(x)=1$，否则$=0$。
考虑从下往上算每棵子树的$SG$值。设$SG(x)$表示$x$子树的$SG$值，$g(x)$表示对$x$这棵子树操作能得到的后继的$SG$值集合（只考虑$x$子树），那么$SG(x)=\mathbb{mex}\{g(x)\}$。

考虑如何计算$g(x)$。令$sum[x]=sg(v_1)\ \mathbb{xor}\ sg(v_2)\ \mathbb{xor}...,\ v_i\in son[x]$。
若$x$是黑点，假设这次操作选了$v_i$子树中的某个点，那么其它子树状态不变，$v_i$子树的后继状态会变成$g(v_i)$中的某个，所以$g(x)=sum[x]\ \mathbb{xor}\ sg(v_i)\ \mathbb{xor}\ (g(v_i)中的某个值)$。
把子树内每个$g(v_i)$整体$\mathbb{xor}$一个数，合并起来，就可以得到$g(x)$了。
若$x$是白点，多了一种选$x$的后继，选$x$后得到状态的$SG$值就是$sum[x]$。所以在$g(x)$中再插入一个$sum[x]$即可。

还要支持求$\mathbb{mex}$，可以用$01Trie$维护。合并的时候可以启发式合并，$O(n\log^2n)$，也可以类似线段树合并做到$O(n\log n)$。

对于第二问，考虑选择一个节点后局面的$SG$值。容易发现就是除去它到根节点路径上的点的所有点的$SG$值的异或和。
记$up[x]$表示除去$x$到根节点路径上的点外，所有节点的$SG$值异或和，那么$up[x]=up[fa[x]]^{\wedge}sum[fa[x]]^{\wedge}SG(x)$。选择$x$后$x$的各棵子树是独立的，局面的$SG$值就是$up[x]^{\wedge}sum[x]$（$up$也可以直接$DFS$的时候传个参）。
所以如果$up[x]^{\wedge}sum[x]=0$，选这个点就是必胜的。

这个$SG$值的最大值是啥啊...
注意$Trie$要特判叶子的地方（尤其是`Merge`，注意像线段树合并一样判下叶子）（我怎么老是写错...）。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define Bit 16
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],root[N],sg[N],sum[N],up[N];
bool col[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	#define S N*20
	#define ls son[x][0]
	#define rs son[x][1]
	int tot,son[S][2],tag[S];
	bool full[S];
	#define Update(x) full[x]=full[ls]&&full[rs]
	inline void Upd(int x,int v,int dep)
	{
//		if(dep<0) return;
		if(v>>dep&1) std::swap(ls,rs);
		tag[x]^=v;
	}
	inline void PushDown(int x,int dep)
	{
		if(dep&&tag[x]) Upd(ls,tag[x],dep-1), Upd(rs,tag[x],dep-1), tag[x]=0;
	}
	void Insert(int &x,int v,int dep)
	{
		x=++tot;
		if(dep<0) {full[x]=1; return;}
		v>>dep&1 ? Insert(rs,v,dep-1) : Insert(ls,v,dep-1);
	}
	int Merge(int x,int y,int dep)
	{
		if(!x||!y) return x|y;
		if(dep<0) return x;
		PushDown(x,dep), PushDown(y,dep);
		ls=Merge(ls,son[y][0],dep-1), rs=Merge(rs,son[y][1],dep-1);
		Update(x); return x;
	}
	int Mex(int x,int dep)
	{
		if(!x||dep<0) return 0;
		PushDown(x,dep);
		return full[ls]?(1<<dep)+Mex(rs,dep-1):Mex(ls,dep-1);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x,int fa)
{
	if(!col[x]) T.Insert(root[x],0,Bit);
	int s=0;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
			DFS1(v,x), s^=sg[v], T.Upd(root[v],sg[v],Bit), root[x]=T.Merge(root[x],root[v],Bit);
	if(s) T.Upd(root[x],s,Bit);
	sum[x]=s, sg[x]=T.Mex(root[x],Bit);
}
void DFS2(int x,int fa)
{
	up[x]=up[fa]^sum[fa]^sg[x];
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa) DFS2(v,x);
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) col[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1,0), sum[0]=sg[1], DFS2(1,0);
	bool f=0;
	for(int x=1; x<=n; ++x) if(!col[x]&&!(sum[x]^up[x])) f=1, printf("%d\n",x);
	if(!f) puts("-1");

	return 0;
}
