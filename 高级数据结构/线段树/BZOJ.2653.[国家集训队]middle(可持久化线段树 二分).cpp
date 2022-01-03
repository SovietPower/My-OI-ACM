/*
12848kb	756ms
求中位数除了$sort$还有什么方法？二分一个数$x$，把$<x$的数全设成$-1$，$\geq x$的数设成$1$，判断序列和是否非负。
对于询问$(a,b,c,d)$，同样也可以二分中位数$x$，然后把原序列对应地改为$+1$或$-1$。
此时区间$[b,c]$中的数是必选的，求一个和$sum$。显然对于区间$[a,b-1]$，我们可以求一个和最大的后缀；对于区间$[c+1,d]$，可以求一个和最大的前缀。然后判断总和是否非负。
这些都可以建出线段树来维护。

显然每次二分不能重新建树。考虑刚开始时对每个$x$建一棵树。
假设序列中的数互不相同，每次二分的数从$x$变成$x+1$时，显然与$x$相比，从$+1$变成$-1$的数只有一个。也就是每次与上一次相比，只会改变一个位置。
如果序列中的数会重复，显然总复杂度也不会受影响。
所以可以对每个$x$建可持久化线段树，维护区间和、最大前缀后缀和即可。

复杂度$O(n\log n+q\log^2n)$。

对于重复的数（假设有$c$个位置满足$A_i=x$），其实不需要去重，建$c$棵不同的线段树即可。无论真正的中位数和$x$的关系如何，一定能二分到正确位置。
如果去重，注意对于每个值我们要保留最开始的那棵树（比如`2 2 2`，一直修改`root[now]`的话会是`-1 -1 1`，实际上可以是`1 1 1` ）。注意线段树范围是`1~n`不是`1~cnt`。。
去重虽然能优化二分边界，但是好像没什么实际效果（更慢了）= =
*/
#include <cstdio>
#include <cctype>
#include <assert.h>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 50000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=20005;

int root[N];
std::pair<int,int> A[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define S N*19//建树还有一个2n空间，但是不要卡着开n(2+logn)= = 
	int tot,Ans,son[S][2],sum[S],pre[S],suf[S];
	#undef S
	inline void Update(int x)
	{
		int l=ls, r=rs;
		sum[x]=sum[l]+sum[r];
		pre[x]=std::max(pre[l],sum[l]+pre[r]);
		suf[x]=std::max(suf[r],sum[r]+suf[l]);
	}
	void Build(int &x,int l,int r)
	{
		x=++tot;
		if(l==r) {sum[x]=pre[x]=suf[x]=1; return;}
		int m=l+r>>1;
		Build(ls,l,m), Build(rs,m+1,r), Update(x);
	}
	void Modify(int &x,int y,int l,int r,int p)
	{
		x=++tot;
		if(l==r) {sum[x]=-1; return;}
		int m=l+r>>1;
		p<=m ? (rs=son[y][1],Modify(ls,son[y][0],l,m,p)) : (ls=son[y][0],Modify(rs,son[y][1],m+1,r,p));
		Update(x);
	}
	int QuerySum(int x,int l,int r,int L,int R)
	{
		if(L<=l && r<=R) return sum[x];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return QuerySum(ls,l,m,L,R)+QuerySum(rs,m+1,r,L,R);
			else return QuerySum(ls,l,m,L,R);
		return QuerySum(rs,m+1,r,L,R);
	}
	void QueryPre(int x,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
		{
			Ans=std::max(pre[x],Ans+sum[x]);
			return;
		}
		int m=l+r>>1;
		if(m<R) QueryPre(rs,m+1,r,L,R);
		if(L<=m) QueryPre(ls,l,m,L,R);//max(QueryPre(lson),QuerySum(lson)+QueryPre(rson)) 这样写的复杂度是啥啊...= = 
	}
	void QuerySuf(int x,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
		{
			Ans=std::max(suf[x],Ans+sum[x]);
			return;
		}
		int m=l+r>>1;
		if(L<=m) QuerySuf(ls,l,m,L,R);
		if(m<R) QuerySuf(rs,m+1,r,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
bool Check(int x,int n,int a,int b,int c,int d)
{
	int s=T.QuerySum(root[x],1,n,b,c);
	if(s>=0) return 1;
	if(a<b)
	{
		T.Ans=0, T.QuerySuf(root[x],1,n,a,b-1);//可以用同一个函数直接Query合并区间的=v= 为了常数算了= = 
		if((s+=T.Ans)>=0) return 1;
	}
	if(c<d)
	{
		T.Ans=0, T.QueryPre(root[x],1,n,c+1,d);
		if((s+=T.Ans)>=0) return 1;
	}
	return 0;
}

int main()
{
	static int ref[N];
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=std::make_pair(read(),i);
	std::sort(A+1,A+1+n); int cnt=1; ref[1]=A[1].first;
	for(int i=2; i<=n; ++i) if(A[i].first!=A[i-1].first) ref[++cnt]=A[i].first;
	T.Build(root[1],1,n), root[2]=root[1];
//	for(int i=2; i<=n; ++i) T.Modify(root[i],root[i-1],1,n,A[i-1].second);
	for(int i=2,now=2; i<=n; ++i)//A[n]不用管.
	{
		T.Modify(root[now],root[now],1,n,A[i-1].second);
		if(A[i].first!=A[i-1].first) ++now, root[now]=root[now-1];//root[++now]=root[now-1] 还是不要写这种语句了=-= 
	}
	for(int Q=read(),ans=0,q[4]; Q--; )
	{
		q[0]=(read()+ans)%n+1, q[1]=(read()+ans)%n+1, q[2]=(read()+ans)%n+1, q[3]=(read()+ans)%n+1;
		std::sort(q,q+4);
		int l=1,r=cnt,mid;
		while(l<=r)
			if(Check(mid=l+r>>1,n,q[0],q[1],q[2],q[3])) ans=mid, l=mid+1;
			else r=mid-1;
		printf("%d\n",ans=ref[ans]);
	}

	return 0;
}
