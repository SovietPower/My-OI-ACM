/*
483ms	161100KB
$Description$
给定$n$个数对$A_i,B_i$。你可以进行任意次以下两种操作：
1. 选择一个位置$i$，令$A_i=A_i+1$，花费$B_i$。必须存在一个位置$j$，满足$A_i=A_j,\ i\neq j$，才可以进行。
2. 选择一个位置$i$，令$A_i=A_i-1$，花费$-B_i$。必须存在一个位置$j$，满足$A_i=A_j+1$，才可以进行。
你需要对于所有$i\in[1,n]$，求使得$A_1,A_2,...,A_i$两两不同的最小花费是多少。
$n,A_i\leq2\times10^5,\ 1\leq B_i\leq n且互不相同$。

$Solution$
考虑如果$A_i$互不相同，若存在$A_i+1=A_j$，则可以交换$A_i,A_j$，花费为$B_i-B_j$。所以最后序列会被分成$A_i$连续的若干段，且每段$B_i$递减。
如果$A_i$有可能相同，可以先把$A_i$变成互不相同（把相同的位置上的数移到该连续段的右端点$+1$处，并查集维护），再进行同样的操作。

设数$A_i$最终变成了$A_i'$（按$B_i$排序后被放到了$A_i'$位置去），我们发现$i$的贡献就是$(A_i'-A_i)\times B_i$，也就是所有数的贡献是$\sum_i A_i'\times B_i-\sum_i A_i\times B_i$。所以我们只需要在按$B_i$排序的过程中维护每个元素新的位置及贡献（其实维护位置就是维护在连续段中的排名，直接插入即可）。
具体就是，对于一个连续段，以$B_i$为下标建线段树。最后$B_i$是递减的，所以每个区间的贡献就是，$左区间的\sum B_i\times 右区间的元素个数$（当然这只是段内相对排名改变的贡献，连续段整体还有 $连续段左端点\times\sum B_i$的贡献）。

加入一个$A_i$时，可能把两个连续段合并在一起。把原先两个连续段的贡献减掉，然后线段树合并两段，再加上合并后的段的贡献即可。

复杂度$O(n\log n)$（为啥$Tutorial$上写的是$O(n\log^2n)$...？没细看...）。

注意数组大小要开$4e5$！不是$2e5$！（值域会扩大）
当你连WA 8遍且发现输出都不一样的时候，基本就是RE了= = 气死我了
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=4e5+3;//4e5 not 2e5!

int fa[N],R[N],root[N];
LL Ans;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	#define S N*20
	int tot,sz[S],son[S][2];
	LL sum[S];
	#undef S
	#define Update(x) sz[x]=sz[ls]+sz[rs], sum[x]=sum[ls]+sum[rs]
	void Insert(int &x,int l,int r,int pos)
	{
		if(!x) x=++tot;
		if(l==r) {sz[x]=1, sum[x]=pos; return;}
		int m=l+r>>1;
		pos<=m ? Insert(lson,pos) : Insert(rson,pos);
		Update(x);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x|y;
		Ans-=sum[ls]*sz[rs]+sum[son[y][0]]*sz[son[y][1]];
		ls=Merge(ls,son[y][0]), rs=Merge(rs,son[y][1]);
		Ans+=sum[ls]*sz[rs], sz[x]+=sz[y], sum[x]+=sum[y];// Update(x); 不要写Update...（虽然这题能过）
		return x;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Merge(int x,int y)
{
	x=Find(x), y=Find(y), fa[y]=x;
	Ans-=T.sum[root[x]]*x+T.sum[root[y]]*y;
	root[x]=T.Merge(root[x],root[y]);
	Ans+=T.sum[root[x]]*x;
	R[x]=R[y];
}

int main()
{
	const int n=read();
	for(int i=1; i<N; ++i) R[i]=i, fa[i]=i;
	for(int i=1; i<=n; ++i)
	{
		int a=read(),b=read(),p=root[a]?R[Find(a)]+1:a;
		Ans-=1ll*a*b, T.Insert(root[p],1,n,b), Ans+=1ll*p*b;
		if(root[p-1]) Merge(p-1,p);
		if(root[p+1]) Merge(p,p+1);
		printf("%I64d\n",Ans);
	}

	return 0;
}
