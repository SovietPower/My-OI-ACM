//119964kb	5780ms
//这不就主席树裸题吗。。
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=5e5+5,S=N*20;

int n,m,root[N];
namespace T
{
	#define lson son[rt][0]
	#define rson son[rt][1]

	int tot,sz[S],son[S][2];
	void Insert(int rt,int &y,int l,int r,int p)
	{
		sz[y=++tot]=sz[rt]+1;
		if(l<r){
			int m=l+r>>1;
			if(p<=m) son[y][1]=rson, Insert(lson,son[y][0],l,m,p);
			else son[y][0]=lson, Insert(rson,son[y][1],m+1,r,p);
		}
	}
	int Query(int x,int y,int l,int r,int k)
	{
//		if(sz[y]-sz[x]<=k) return 0;
		if(l==r) return l;//直接只在>时递归，不用判那么多。
		if(sz[son[y][0]]-sz[son[x][0]]>k) return Query(son[x][0],son[y][0],l,l+r>>1,k);
		else if(sz[son[y][1]]-sz[son[x][1]]>k) return Query(son[x][1],son[y][1],(l+r>>1)+1,r,k);
		return 0;
	}
	
}
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
	for(int a,i=1; i<=n; ++i) a=read(),T::Insert(root[i-1],root[i],1,n,a);
	int l,r;
	while(m--)
		l=read(),r=read(),printf("%d\n",T::Query(root[l-1],root[r],1,n,(r-l+1)>>1));
	return 0;
}
