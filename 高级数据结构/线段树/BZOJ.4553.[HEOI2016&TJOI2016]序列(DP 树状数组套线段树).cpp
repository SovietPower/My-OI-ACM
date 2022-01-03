//树状数组套线段树 思路不写了 
//企图二维树状数组 但动态开点的话 中间一段没有的区间会中断y方向的Query..
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
#define now node[rt]
#define lson l,m,node[rt].ls
#define rson m+1,r,node[rt].rs
#define lb(x) ((x)&-(x))
const int N=1e5+5;

int n,m,A[N],minv[N],maxv[N],MaxV,MaxA;
namespace Tree_2D
{
	struct Seg_Tree
	{
		struct Node
		{
			int maxv,ls,rs;
		}node[N<<6];//还要再小点。。不然BZOJ上依旧MLE 
		inline int new_Node()
		{
			static int cnt=0;
			return ++cnt;
		}
		void Insert(int l,int r,int &rt,int p,int v)
		{
			if(!rt) rt = new_Node();
			now.maxv = std::max(now.maxv, v);
			if(l<r)
			{
				int m=l+r>>1;
				if(p<=m) Insert(lson,p,v);
				else Insert(rson,p,v);
			}
		}
		int Query(int l,int r,int rt,int L,int R)
		{
			if(!rt) return 0;
			if(L<=l && r<=R) return now.maxv;
			int m=l+r>>1;
			if(L<=m)
				if(m<R) return std::max(Query(lson,L,R),Query(rson,L,R));
				else return Query(lson,L,R);
			return Query(rson,L,R);
		}
	}t;
	struct Bit
	{
		int root[N];
		void Insert(int p,int y,int v)
		{
			while(p<=MaxV)
				t.Insert(1,MaxA,root[p],y,v), p+=lb(p);
		}
		int Query(int p,int y)
		{
			int res=0;
			while(p)
				res=std::max(res,t.Query(1,MaxA,root[p],1,y)), p-=lb(p);
			return res;
		}
	}t2D;
}
#undef now
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i)
		maxv[i]=minv[i]=A[i]=read(), MaxA=std::max(MaxA,A[i]);
	for(int x,y,i=1; i<=m; ++i)
		x=read(), y=read(), maxv[x]=std::max(maxv[x],y), minv[x]=std::min(minv[x],y);
	for(int i=1; i<=n; ++i) MaxV=std::max(MaxV,maxv[i]);
	int ans=0;
	for(int v,i=1; i<=n; ++i)
	{
		v = Tree_2D::t2D.Query(minv[i],A[i]) + 1;
		Tree_2D::t2D.Insert(A[i],maxv[i],v);
		ans=std::max(ans,v);
	}
	printf("%d",ans);

	return 0;
}
