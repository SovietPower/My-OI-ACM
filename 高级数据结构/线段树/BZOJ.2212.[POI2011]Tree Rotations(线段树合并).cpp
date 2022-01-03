/*
80628kb	7088ms
$Description$
给定一棵n个叶子的二叉树，每个叶节点有权值(1<=ai<=n)。可以任意的交换两棵子树。问最后顺序遍历树得到的叶子权值序列中，最少的逆序对数是多少。
$Solution$
很重要的一点是在子树内部交换左右儿子对其它子树是没有影响的。（当然更大区间内交换两棵子树对子树内部也是没有影响的）
所以DFS，对每个节点的两棵子树，如果换了更优就换，不优就不换。
怎么统计两棵子树换/不换产生的逆序对数呢，用两棵子树的值域线段树合并解决。换/不换产生的逆序对数根据子树的大小关系判断就行了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int n;
LL Ans;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define S N*19//只有建树、合并的话 nlogn就够了 n(logn+1)!
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,sz[S],son[S][2];

	void Insert(int &x,int l,int r,int p)
	{
		sz[x=++tot]=1;
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) Insert(lson,l,m,p);
		else Insert(rson,m+1,r,p);
	}
	int Merge(int x,int y,LL &ans1,LL &ans2)
	{
		if(!x||!y) return x^y;
		ans1+=1ll*sz[rson]*sz[son[y][0]], ans2+=1ll*sz[lson]*sz[son[y][1]];
		lson=Merge(lson,son[y][0],ans1,ans2);
		rson=Merge(rson,son[y][1],ans1,ans2);
		sz[x]+=sz[y];// sz[x]=sz[lson]+sz[rson]; 这种写法在合并叶子节点时不对啊！（y更新不了x）
		return x;
	}
//	void Print(int x,int l,int r)
//	{
//		if(!x) return;
//		printf("%d:%d~%d sz:%d\n",x,l,r,sz[x]);
//		if(l==r) ;
//		else Print(lson,l,l+r>>1), Print(rson,(l+r>>1)+1,r);
//	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int DFS()//返回root 
{
	int v=read();
	if(v) {int x; T.Insert(x,1,n,v); return x;}
	LL ans1=0, ans2=0;
	int rt=T.Merge(DFS(),DFS(),ans1,ans2);//当然参数顺序是反着的 
	Ans+=std::min(ans1,ans2);
	return rt;
}

int main()
{
	n=read(), DFS(), printf("%lld\n",Ans);
	return 0;
}
