/*
38224kb	2860ms
记mx为最大的满足1~mx都能组成的数。
考虑当前能构成1~v中的所有数，再加入一个数x，若x>v+1，则mx=v，x不会产生影响；否则x<=v+1，则新的mx=x+v。
对于区间[l,r]的询问，模拟这个过程。假设当前答案为v，查询[l,r]中值在[1,v+1]中的数的和sum，若sum==v，即不存在v+1，break；否则v加上这些v+1的和即v=sum，继续。
用主席树实现。v每次至少增加一倍，所以复杂度$O(nlognloga)$。
为什么跑的比较慢呢。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5;

int A[N],root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Tree
{
	#define S N*31//loga not logn && 31 not 30...
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,sum[S],son[S][2];

	inline void Insert(int x,int &y,int l,int r,int p)
	{
		sum[y=++tot]=sum[x]+p;
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) son[y][1]=rson, Insert(lson,son[y][0],l,m,p);
		else son[y][0]=lson, Insert(rson,son[y][1],m+1,r,p);
	}
	int Query(int x,int y,int l,int r,int R)
	{
		if(r<=R) return sum[y]-sum[x];
		int m=l+r>>1;
		if(m<R) return sum[son[y][0]]-sum[lson]+Query(rson,son[y][1],m+1,r,R);
		else return Query(lson,son[y][0],l,m,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(); int R=1;
	for(int i=1; i<=n; ++i) R+=(A[i]=read());
	for(int i=1; i<=n; ++i) T.Insert(root[i-1],root[i],1,R,A[i]);
	for(int m=read(),l,r,ans,sum; m--; )
	{
		l=read(),r=read(),ans=0;
		while(ans<(sum=T.Query(root[l-1],root[r],1,R,ans+1))) ans=sum;
		printf("%d\n",ans+1);
	}
	return 0;
}
