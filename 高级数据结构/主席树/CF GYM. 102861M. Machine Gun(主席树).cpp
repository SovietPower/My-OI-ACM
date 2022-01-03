/*
296ms	19600KB
容易发现，合法的点$(x,y)$若满足询问$(qx,qy)$，则需满足$2y-x\leq 2qy-qx,\ 2y+x\geq 2qy+qx$，将点$(x,y)$变为$(2y-x,2y+x)$，就是一个二维偏序。 
强制在线，最简单的办法就是线段树套线段树（TLE on #2），或是按$x$排序后对$y$轴建主席树。
还有一个在线方法是区间树（std，但是我的TLE on #5/whl，是我太菜了）：换一下表示方式，题意等价于求与$[2qy+qx,2qy-qx]$相交的所有区间，用线段树+区间树可以实现（纯区间树应该做不了吧，所以常数很大）。区间树见[这儿](https://www.cnblogs.com/SovietPower/p/14399552.html)，很裸。

记一下主席树的细节：纵坐标$y_i$用$(n+1)\times y_i+i$进行储存和离散化，这样一是没有可持久化要存$vector$的问题，二是主席树$Query$出来的答案就是按标号排好序的（不需再排序）。
为了方便可以用$(y_i<<18)+i$，这样某个$y$位置的编号就是$y\&((1<<18)-1)$。（最好用$2y+x$作为$y$让$y$做编号时为正数？）
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
#define mod 1000000007
typedef long long LL;
const int N=1e5+5,M=(1<<18)-1;

int root[N],cnt,Ans[N];
LL X[N],Y[N],pw[N];
struct Node
{
	LL x,y;
	bool operator <(const Node &a)const
	{
		return x<a.x;
	}
}A[N];
struct President_Tree
{
	#define S N*19
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,son[y][0],l,m
	#define rson rs,son[y][1],m+1,r
	int tot,son[S][2];
	#undef S
	void Insert(int &x,int y,int l,int r,int p)
	{
		x=++tot;
		if(l==r) return;
		int m=l+r>>1;
		p<=m?(rs=son[y][1],Insert(lson,p)):(ls=son[y][0],Insert(rson,p));
	}
	void Query(int x,int l,int r,int p)//p~N
	{
		if(!x) return;
		if(l==r) {Ans[++cnt]=Y[l]&M; return;}
		int m=l+r>>1;
		p<=m && (Query(ls,l,m,p),0);
		Query(rs,m+1,r,p);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int r,LL v)//the first num satisfying >=v
{
	int l=1,mid;
	while(l<r)
		if(Y[mid=l+r>>1]<v) l=mid+1;
		else r=mid;
	return l;
}
int Find2(int r,LL v)//the first num satisfying <=v
{
	if(X[1]>v) return 0;
	int l=1,mid,ans=0;
	while(l<=r)
		if(X[mid=l+r>>1]<=v) l=mid+1,ans=mid;
		else r=mid-1;
	return ans;
}

int main()
{
	int n=read(),Q=read();
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]*5782344%mod;
	for(int i=1; i<=n; ++i)
	{
		LL x=read(),y=read();
		A[i].x=2*y-x, Y[i]=A[i].y=((2*y+x)<<18)+i;
	}

	std::sort(A+1,A+1+n), std::sort(Y+1,Y+1+n);
	for(int i=1; i<=n; ++i) X[i]=A[i].x;
	for(int i=1; i<=n; ++i) T.Insert(root[i],root[i-1],1,n,Find(n,A[i].y));

	for(int p=0; Q--; )
	{
		LL x=-1-((p+read())%mod),y=(p+read())%mod;
		if(2*y+x>Y[n]) {printf("%d\n",p=0); continue;}

		int R1=Find2(n,2*y-x),L2=Find(n,(2*y+x)<<18);
		cnt=0, T.Query(root[R1],1,n,L2);

		LL res=0;
		std::sort(Ans+1,Ans+1+cnt);
		LL *pw_=pw;
		for(int *a=Ans+1,*lim=Ans+cnt+1; a!=lim; ++a,++pw_) res+=(*a)*(*pw_)%mod;
		p=(int)(res%mod), printf("%d\n",p);
	}

	return 0;
}
