/*
39460kb	3068ms
对树DFS得到括号序列。比如这样一个括号序列：`[A[B[E][F[H][I]]][C][D[G]]]`。
那比如$D,E$间的最短距离，就是将$D,E$间的括号序列取出：`][[][]]][][`，然后去掉其中匹配的括号，得到：`]][[`。
所以$D,E$在树上的最短距离为$4$。因为左边一个右括号就表示向上一层，右边一个左括号就表示向下一层。

对一个区间记一个二元组$(a,b)$，表示该区间（去掉匹配括号后的）括号序列是`]]..][..[`，一共$a$个`]`，$b$个`[`。
那这个区间左右端点的距离就是$a+b$，我们要维护最大的$a+b$（假设是求两黑点间的最大距离，那这个区间的左右端点都是黑点才能更新答案）。
记左右区间的状态分别是$(a_1,b_1),(a_2,b_2)$。
那两个区间合并后的状态是：
$b_1\leq a_2$时，$=(a_1+a_2-b_1,\ b_2)$
$b_1>a_2$时，$=(a_1,\ b_2+b_1-a_2)$
$a+b$的值其实就是$a_1+b_2+|a_2-b_1|=a_1+b_2+\max(a_2-b_1,\ b_1-a_2)=\max(a_1-b_1+(a_2+b_2),\ a_1+b_1+(b_2-a_2))$。
也就是这个区间的答案有两种更新方式：左区间的$\max\{a-b\}+$右区间的$\max\{a+b\}$，或是，左区间的$\max\{a+b\}+$右区间的$\max\{b-a\}$。
所以我们对每个区间维护$a,b,\max\{a-b\},\max\{b-a\},\max\{a+b\}$。
（注意更新答案是要求两端点都是黑点，所以能更新$\max\{a-b\}$的要包含区间右端点且区间左端点必须是黑点，同理更新$\max\{b-a\}$的要包含区间左端点且区间右端点必须是黑点，而$\max\{a+b\}$我们要根据区间左右端点是否必须为黑点维护两个值。）
而两区间合并后的$a-b$，无论$b_1,a_2$的大小关系，都是$a_1-b_1+a_2-b_2$；$b-a$就是$b_1-a_2+b_2-a_2$。也就是两区间的这两个信息可以直接相加合并。
（如$max\{a-b\}$，可以由右区间的$\max\{a-b\}$得到，或是$\max\{a_1-b_1\}+a_2-b_2$得到，右区间的$a_2,b_2$是必选的）

记$\max\{a-b\}$为$vab$，$\max\{b-a\}$为$vba$。
对于包含区间左端点且区间右端点为黑点的$\max\{a+b\}$（记作$vr$好了，对应的就记作$vl$），合并左右子区间的时候，要么是从左儿子的$vr_l$直接转移，要么是用左儿子的和+右儿子的一些和转移。
而合并得到$a+b$的时候是这样的：$\max(a_1-b_1+(a_2+b_2),\ a_1+b_1+(b_2-a_2))$，也就是要么是左区间的$a-b+$右区间的$\max\{a+b\}$，即$a_l-b_l+vr_r$，要么是左区间的$a-b+$右区间的$\max\{b-a\}$，即$a_l+b_l+vba_r$。
$vr$同理。

那状态$a,b$以及这$4$个$\max$都能合并了，维护一下就好咯。（具体见代码吧，挺好理解的）
复杂度$O(n\log n)$。

注意建树的时候就是建出`[A[B[E][F[H][I]]][C][D[G]]]`这样的长度$3n$的序列，$A,B,...$代表的是点的编号。修改的时候改对应字母位置即可。（因为就算去掉字母，括号是一定的，而且查的时候也只是查两字母之间的括号数）
对端点必须为黑点的要求，如果某点是白点或是括号，将各值设成$-INF$即可。
还是感觉这个建树好迷啊...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=N*3,INF=1<<29;

int A[M],Enum,H[N],nxt[N<<1],to[N<<1],pos[N],col[N];//0:close 1:open
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S M<<2
	int ans[S],a[S],b[S],vab[S],vba[S],vl[S],vr[S];//vab:max{a-b} vba:max{b-a} vl:max{a+b}且左端点为黑点 
	#undef S
	inline void Init(int p,int rt)
	{
		a[rt]=A[p]==-2, b[rt]=A[p]==-1, ans[rt]=-INF;//a是右括号 b是左括号。。
		if(A[p]<0 || col[A[p]]) vab[rt]=vba[rt]=vl[rt]=vr[rt]=-INF;
		else vab[rt]=vba[rt]=vl[rt]=vr[rt]=0;
	}
	inline void Update(int rt)
	{
		int l=ls,r=rs;
		a[rt]=a[l]+std::max(0,a[r]-b[l]), b[rt]=b[r]+std::max(0,b[l]-a[r]);
		ans[rt]=std::max(std::max(ans[l],ans[r]),std::max(vab[l]+vr[r],vl[l]+vba[r]));
		vab[rt]=std::max(vab[r],a[r]-b[r]+vab[l]);
		vba[rt]=std::max(vba[l],b[l]-a[l]+vba[r]);
		vl[rt] =std::max(vl[r],std::max(vab[l]+a[r]+b[r],vl[l]+b[r]-a[r]));
		vr[rt] =std::max(vr[l],std::max(a[l]-b[l]+vr[r],a[l]+b[l]+vba[r]));
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {Init(l,rt); return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int p)
	{
		if(l==r) {Init(l,rt); return;}
		int m=l+r>>1;
		p<=m ? Modify(lson,p) : Modify(rson,p);
		Update(rt);
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
inline char GetOpt()
{
	register char c=gc();
	while(c!='C'&&c!='G') c=gc();
	return c;
}
void DFS(int x)
{
	static int Index=0;
	A[++Index]=-1, A[pos[x]=++Index]=x;
	for(int i=H[x]; i; i=nxt[i]) if(!pos[to[i]]) DFS(to[i]);
	A[++Index]=-2;
}

int main()
{
	#define S 1,cnt,1
	const int n=read(),cnt=n*3;
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS(1), T.Build(S);
	for(int Q=read(),tot=n,x; Q--; )
		switch(GetOpt())
		{
			case 'C': col[x=read()]^=1, tot+=col[x]?-1:1, T.Modify(S,pos[x]); break;
			case 'G': tot>1?printf("%d\n",T.ans[1]):tot==1?puts("0"):puts("-1"); break;
		}
	return 0;
}
