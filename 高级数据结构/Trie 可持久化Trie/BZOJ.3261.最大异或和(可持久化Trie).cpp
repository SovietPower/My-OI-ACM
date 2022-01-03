/*
179000kb	3508ms
���ÿ���޸ĺ�׺������Ѹ㣬������Ϊ�����Ե�������sum[p~n]�����ֵ����ת��Ϊ��sum[1~n] xor sum[1~p-1]�����ֵ��
p-1��[l-1,r-1]���ÿɳ־û�Trie������[l-1,r-1] xor x xor sum[1~n]�����ֵ���ɡ�
����ɳ־û�Trie���������ĳһ���������һ���������ֵ������Ҫ�������ǰ׺�͡�
ע���������[1,1]��ѯ���ǿ�����0 xor�ģ�����Ҫ��ǰ��������0�����Ҳ�����root[0]��(������root[l-2=-1])������ֱ������ƫ��1����root[1]�������0��
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
			l=read(),r=read(),printf("%d\n",T.Query(root[l-1],root[r],sum^read()));//ƫ���˾�������..
//			l=read(),r=read(),printf("%d\n",T.Query(root[std::max(l-2,0)],root[r-1],sum^read()));

	return 0;
}
