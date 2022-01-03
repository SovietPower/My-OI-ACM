/*
179000kb	3508ms
这个每次修改后缀好像很难搞，但是因为异或可以抵消，求sum[p~n]的最大值可以转化为求sum[1~n] xor sum[1~p-1]的最大值。
p-1∈[l-1,r-1]，用可持久化Trie查区间[l-1,r-1] xor x xor sum[1~n]的最大值即可。
另外可持久化Trie查的是区间某一个数异或另一个数的最大值，所以要插入的是前缀和。
注意对于区间[1,1]的询问是可以用0 xor的，所以要在前面加上这个0，而且不能在root[0]加(除非用root[l-2=-1])。不妨直接向右偏移1，在root[1]插入这个0。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 50000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define BIT 23
const int N=6e5+5;//N+M!

int root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	#define S N*25
	int tot,son[S][2],sz[S];

	void Insert(int x,int y,int v)
	{
		for(int i=BIT; ~i; --i)
		{
			int c=v>>i&1;
			son[x][c]=++tot, son[x][c^1]=son[y][c^1];
			x=tot/*son[x][c]*/, y=son[y][c];
			sz[x]=sz[y]+1;
		}
	}
	int Query(int x,int y,int v)//x~y
	{
		int res=0;
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1;
			if(sz[son[y][c]]-sz[son[x][c]]>0)
				x=son[x][c], y=son[y][c], res|=1<<i;
			else
				c^=1, x=son[x][c], y=son[y][c];
		}
		return res;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline char readc()
{
	register char c=gc();
	for(; c!='A'&&c!='Q'; c=gc());
	return c;
}

int main()
{
	int n=read()+1, Q=read(), sum=0;
	T.Insert(root[1]=++T.tot,0/*root[0]*/,0);
	for(int i=2; i<=n; ++i)
		T.Insert(root[i]=++T.tot,root[i-1],sum^=read());
	for(int l,r; Q--; )
		if(readc()=='A')
			T.Insert(root[n+1]=++T.tot,root[n],sum^=read()), ++n;
		else
			l=read(),r=read(),printf("%d\n",T.Query(root[l-1],root[r],sum^read()));//偏移了就正常了..
//			l=read(),r=read(),printf("%d\n",T.Query(root[std::max(l-2,0)],root[r-1],sum^read()));

	return 0;
}
