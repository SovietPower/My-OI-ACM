/*
$Solution1$
先求一遍前缀异或和。
假设左端点是$i$，那么我们要在$[i,n]$中找一个$sum_j$使得它和$sum_{i-1}$异或最大。可以可持久化Trie。
对$i\in[1,n]$都求一遍它能得到的最大的异或值，扔到堆里。
每次从堆里找出值最大的，假设是$x$，与$sum_{x-1}$异或得到最大值的数是$sum_y$，那么之后就不能选$sum_{x-1}\ \mathbb{xor}\ sum_y$了。
记$T_i$为第$i$棵$Trie$。因为查询最大值时，我们是用$T_n$与$T_{i-1}$的$size$差是否$>0$，来判断能否取一个值。
所以现在令$T_{x-1}$在$sum_y$这条路径上的$size+1$，就可以实现删掉一个$sum_y$了。
修改$T_{x-1}$之后再找一个和$sum_{x-1}$异或最大的，把$x$扔到堆里。
这个$Modify$和$Insert$函数一模一样（考场上我竟然没注意到这个=-=）。

$Solution2$
$sum_i\ ^{\wedge}sum_j=sum_j\ ^{\wedge}sum_i$，所以可以把$k$变成$2k$，求任意一对数异或，能得到的最大的$k$对是多少。
对每个数求一下和它异或最大的是哪个，扔到堆里。
每次从堆里取出值最大的一个数$i$，加上$i$的答案。然后我们要找，和$sum_i$异或第二大的值是哪个。在$Trie$上查即可。再扔到堆里。再下一次就查，和$sum_i$异或第$3$大的值是哪个...
对所有数建一棵$Trie$即可。

$Solution3$
有一种类似[[NOI2010]超级钢琴]的做法。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#include <unordered_map>
#define mp std::make_pair
#define pr std::pair<uint,int>
#define BIT 31
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef unsigned int uint;
typedef long long LL;
typedef unsigned long long ull;
const int N=5e5+5;

int root[N];
uint A[N],sum[N];
std::priority_queue<pr> q;
//std::mt19937 Rand(1002330);
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	#define S N*(BIT+2)*2
	int tot,son[S][2],sz[S];
	void Insert(int &rt,int y,uint v)
	{
		int x=rt=++tot;
		for(int i=BIT; ~i; --i)
		{
			int c=v>>i&1;
			son[x][c^1]=son[y][c^1];
			x=son[x][c]=++tot, y=son[y][c], sz[x]=sz[y]+1;
		}
	}
	uint Query(int x,int y,uint v)//y-x
	{
		uint res=0;
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1;
			if(sz[son[y][c]]-sz[son[x][c]]>0) res|=1u<<i;
			else c^=1;
			x=son[x][c], y=son[y][c];
		}
		return res;
	}
	void Modify(int &rt,int X,uint v)
	{
		int x=rt=++tot;
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1);
			son[x][c^1]=son[X][c^1];
			x=son[x][c]=++tot, X=son[X][c], sz[x]=sz[X]+1;
		}
	}
}T;

inline uint read()
{
	uint now=0; register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
namespace Subtask1
{
	uint q[4000005];
	void Main(int n,int K)
	{
		int t=0;
		for(int i=1; i<=n; ++i)
		{
			uint now=0;
			for(int j=i; j<=n; ++j)
				now^=A[j], q[++t]=now;
		}
		std::sort(q+1,q+1+t,std::greater<uint>());
		LL ans=0;
		for(int i=1; i<=t&&i<=K; ++i) ans+=q[i];
		printf("%I64d\n",ans);
	}
}

int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);

	int n=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=read(),sum[i]=A[i]^sum[i-1];
//	if(n<=2000) return Subtask1::Main(n,K),0;
	for(int i=1; i<=n; ++i) T.Insert(root[i],root[i-1],sum[i]);
	for(int i=1; i<=n; ++i) q.push(mp(T.Query(root[i-1],root[n],sum[i-1]),i));
	LL ans=0;
	while(K--&&!q.empty())
	{
		uint tmp=q.top().first; ans+=tmp;
		int x=q.top().second; q.pop();
		T.Modify(root[x-1],root[x-1],tmp^sum[x-1]);
		q.push(mp(T.Query(root[x-1],root[n],sum[x-1]),x));
	}
	printf("%I64d\n",ans);

	return 0;
}
