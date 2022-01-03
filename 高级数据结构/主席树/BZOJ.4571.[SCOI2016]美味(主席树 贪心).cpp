/*
46136kb	13912ms
要求b^(aj+x)最大，应让(aj+x)的最高位尽可能与b相反。带个减法Trie树好像很难做？反正我不会。
从最高位开始，如果这位b是0/1，判断是否存在sum+(1<<l)-x<=aj<sum+(1<<l+1)-x / sum-x<=aj<sum+(1<<l)-x。用主席树判断。
我还在想对于一个询问怎么一次算。。直接O(logn)枚举。
注意要从0开始！
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5,S=N*19,Max=1e5;

int n,m,root[N];
namespace T
{
	int tot,son[S][2],sz[S];
	void Insert(int x,int &y,int l,int r,int p)
	{
		sz[y=++tot]=sz[x]+1;
		if(l<r){
			int m=l+r>>1;
			if(p<=m) son[y][1]=son[x][1], Insert(son[x][0],son[y][0],l,m,p);
			else son[y][0]=son[x][0], Insert(son[x][1],son[y][1],m+1,r,p);
		}
	}
	bool Exist(int x,int y,int l,int r,int L,int R)
	{
		if(L<=l && r<=R) return sz[y]-sz[x];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Exist(son[x][0],son[y][0],l,m,L,R)|Exist(son[x][1],son[y][1],m+1,r,L,R);
			else return Exist(son[x][0],son[y][0],l,m,L,R);
		return Exist(son[x][1],son[y][1],m+1,r,L,R);
	}
	bool Query(int r1,int r2,int l,int r)
	{
		l=std::max(0,l), r=std::min(r,Max);
		return l>r?0:Exist(r1,r2,0,Max,l,r);
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
	int b,x,l,r,sum;
	for(int i=1; i<=n; ++i) T::Insert(root[i-1],root[i],0,Max,read());
	while(m--)
	{
		b=read(),x=read(),l=read(),r=read();
		sum=0;
		for(int i=17,now; i>=0; --i)
		{
			now=sum+((1^((b>>i)&1))<<i);
			if(T::Query(root[l-1],root[r],now-x,now+(1<<i)-1-x)) sum=now;//可以补上这位使得答案最大 
			else sum+=((b>>i)&1)<<i;//不能的话说明这位只能同b一样，加上 
		}
		printf("%d\n",sum^b);//直接记录和，最后^b即可。当然记答案也行。
	}
	return 0;
}
