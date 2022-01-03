/*
57628kb	1692ms
$Description$
给定一个$1$到$n$的排列，$m$次两种操作：
1. 将$[l,r]$中的数升序排序
2. 将$[l,r]$中的数降序排序
最后询问$q$位置上的数字是多少。
$n,m\leq 10^5$。
$Solution$
对于序列上每一段连续区间的数我们都可以动态开点建一棵值域线段树。初始时就是n棵。
对于每次操作，我们可以将[l,r]的数分别从之前它所属的若干段区间中分离出来，合并。
对于升序与降序，只需要维护一个标记，若为降序，则给左区间大的那部分。
具体实现还要用set存下每棵线段树维护的区间左端点，便于快速查找包含[l,r]的区间；对每个区间维护其右端点便于快速得到区间大小。
时间、空间复杂度都是O((n+m)logn)！
Another Solution：
对于询问二分一个值，将所有数根据与这个值的大小关系设为0/1。模拟每次操作，就是将一段区间的0/1分别放在两边。用线段树维护区间和、区间覆盖即可。最后判断是否仅p之前全是0。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5;

int n,m,R[N],root[N],tmp[N];
bool type[N];//0:↑ 
std::set<int> st;
char IN[MAXIN],*SS=IN,*TT=IN;

struct Segment_Tree
{
	#define S N*34//!
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,top,sk[S],sz[S],son[S][2];

	#define Del_Node(x) sk[++top]=x
	inline int New_Node()
	{
		int x=top?sk[top--]:++tot;
		lson=rson=0, sz[x]=1;
		return x;
	}
	void Insert(int &x,int l,int r,int p)
	{
		x=New_Node();
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) Insert(lson,l,m,p);
		else Insert(rson,m+1,r,p);
	}
	void Split(int &y,int x,int k)//将线段树分为x,y两棵，使得sz[x]==k。
	{
		y=New_Node();
		int ls=sz[lson];
		if(ls<k) Split(son[y][1],rson,k-ls);
		else son[y][1]=rson, rson=0;
		if(ls>k) Split(son[y][0],lson,k);
		sz[y]=sz[x]-k, sz[x]=k;
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x^y;
		lson=Merge(lson,son[y][0]), rson=Merge(rson,son[y][1]);
		sz[x]+=sz[y], Del_Node(y); return x;
	}
	int Query(int x,int l,int r,int k)
	{
		if(l==r) return l;
		int ls=sz[lson], m=l+r>>1;
		if(ls>=k) return Query(lson,l,m,k);
		return Query(rson,m+1,r,k-ls);
	}
//	void Print(int x,int l,int r)
//	{
//		if(!x) return;
//		printf("%d:%d~%d sz:%d\n",x,l,r,sz[x]);
//		if(l==r) ;
//		else Print(lson,l,l+r>>1), Print(rson,(l+r>>1)+1,r);
//	}
//	void Output(int x){
//		printf("%d root:%d type:%d:\n",x,root[x],type[x]), Print(root[x],1,n), putchar('\n');
//	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Split(int x,int y)//将x~y划分为一段 
{
	if(y<x||y>=R[x]) return;
	if(!type[x]) T.Split(root[y+1],root[x],y-x+1);
	else root[y+1]=root[x], T.Split(root[x],root[y+1],R[x]-y);//保留右边那部分R[x]-x+1-y+x-1 
	R[y+1]=R[x], R[x]=y, type[y+1]=type[x], st.insert(y+1);
}
void Merge(int x,int y)
{
	if(x==y) return;//
	root[x]=T.Merge(root[x],root[y]);
	R[x]=R[y], st.erase(y);
}
int Query(int k)
{
	std::set<int>::iterator p=st.upper_bound(k);
	int x=*(--p); k-=x-1;
	return type[x]?T.Query(root[x],1,n,R[x]-x+2-k):T.Query(root[x],1,n,k);
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i)
		T.Insert(root[i],1,n,read()), st.insert(i), R[i]=i;
	std::set<int>::iterator p1,p2;
	for(int opt,l,r; m--; )
	{
		opt=read(), l=read(), r=read();
		p1=st.upper_bound(l), Split(*(--p1),l-1);
		p1=st.upper_bound(r), Split(*(--p1),r);

		p1=st.lower_bound(l), p2=st.upper_bound(r);
		int now=*p1, t=0;
		for(++p1; p1!=p2; ++p1) tmp[++t]=*p1;//Merge要修改set，所以还是先存下来吧。
		for(int i=1; i<=t; ++i) Merge(now,tmp[i]);
		type[l]=opt; //type[now]=opt; 
	}
	printf("%d\n",Query(read()));

	return 0;
}
