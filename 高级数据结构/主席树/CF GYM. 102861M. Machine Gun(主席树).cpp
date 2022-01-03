/*
296ms	19600KB
���׷��֣��Ϸ��ĵ�$(x,y)$������ѯ��$(qx,qy)$����������$2y-x\leq 2qy-qx,\ 2y+x\geq 2qy+qx$������$(x,y)$��Ϊ$(2y-x,2y+x)$������һ����άƫ�� 
ǿ�����ߣ���򵥵İ취�����߶������߶�����TLE on #2�������ǰ�$x$������$y$�Ὠ��ϯ����
����һ�����߷�������������std�������ҵ�TLE on #5/whl������̫���ˣ�����һ�±�ʾ��ʽ������ȼ�������$[2qy+qx,2qy-qx]$�ཻ���������䣬���߶���+����������ʵ�֣���������Ӧ�������˰ɣ����Գ����ܴ󣩡���������[���](https://www.cnblogs.com/SovietPower/p/14399552.html)�����㡣

��һ����ϯ����ϸ�ڣ�������$y_i$��$(n+1)\times y_i+i$���д������ɢ��������һ��û�пɳ־û�Ҫ��$vector$�����⣬������ϯ��$Query$�����Ĵ𰸾��ǰ�����ź���ģ����������򣩡�
Ϊ�˷��������$(y_i<<18)+i$������ĳ��$y$λ�õı�ž���$y\&((1<<18)-1)$���������$2y+x$��Ϊ$y$��$y$�����ʱΪ��������
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
