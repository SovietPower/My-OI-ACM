/*
64956kb	1288ms
$Description$
给定一棵有根树，每个点有点权$v_i$。选最多的点，使得对于任意选择的两点$i,j$，若$i$是$j$的祖先，则$v_i>v_j$。
输出最多能选择的点数。选的点不必须连通。
$n\leq 2\times 10^5$。
$Solution$
考虑树退化为链的情况，就是求一个最长(严格)上升子序列。
对于树，不同子树间是互不影响的。仿照序列上的LIS，对每个点x维护一个状态集合，即合并其子节点的集合，然后用val[x]替换掉第一个大于它的数（有等于的就不换了）。
最后根节点状态集合的大小就是答案了。
关于替换数，可以先找到这个数的位置，如果有这个数就不用管了；没有的话插入进去，然后递归回去，找到一个靠右的位置删掉。
当然其实不用线段树合并这么麻烦，直接上multiset启发式合并就可以了。。
注意是合并了子树的状态，so叶节点sz[]>1也是对的！不要直接置为0！
*/
#include <cstdio>
#include <cctype>
#include <cassert>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5;

int n,A[N],cnt,ref[N],root[N],Enum,H[N],nxt[N],to[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define S N*19
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,sz[S],son[S][2];
	bool flag;

	#define Update(x) sz[x]=sz[lson]+sz[rson]
	void Delete(int x,int l,int r)
	{
		if(l==r)
		{
			flag=0, --sz[x];//not sz[x]=0!
			return;
		}
		if(sz[lson]) Delete(lson,l,l+r>>1);
		else/*if(sz[rson])*/ Delete(rson,(l+r>>1)+1,r);
		Update(x);
	}
	void Insert(int &x,int l,int r,int p)
	{
		if(!x) x=++tot;
		if(l==r)
		{
			if(!sz[x]) flag=1, ++sz[x];
			return;
		}
		int m=l+r>>1;
		if(p<=m)
		{
			Insert(lson,l,m,p);
			if(flag&&sz[rson]) Delete(rson,m+1,r);//新建的时候肯定删不了啊(没有右子树) 
		}
		else Insert(rson,m+1,r,p);
		Update(x);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x^y;
		lson=Merge(lson,son[y][0]), rson=Merge(rson,son[y][1]);
		sz[x]+=sz[y], sz[y]=0; return x;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	/*if(u)*/ to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
int Find(int x)
{
	int l=1, r=cnt, mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
void DFS(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		DFS(to[i]), root[x]=T.Merge(root[x],root[to[i]]);
	T.flag=0, T.Insert(root[x],1,cnt,A[x]);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read(), AddEdge(read(),i);

	std::sort(ref+1,ref+1+n), cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i]);

	DFS(1), printf("%d\n",T.sz[root[1]]);

	return 0;
}
