/*
$Solution1$
����һ��ǰ׺���͡�
������˵���$i$����ô����Ҫ��$[i,n]$����һ��$sum_j$ʹ������$sum_{i-1}$�����󡣿��Կɳ־û�Trie��
��$i\in[1,n]$����һ�����ܵõ����������ֵ���ӵ����
ÿ�δӶ����ҳ�ֵ���ģ�������$x$����$sum_{x-1}$���õ����ֵ������$sum_y$����ô֮��Ͳ���ѡ$sum_{x-1}\ \mathbb{xor}\ sum_y$�ˡ�
��$T_i$Ϊ��$i$��$Trie$����Ϊ��ѯ���ֵʱ����������$T_n$��$T_{i-1}$��$size$���Ƿ�$>0$�����ж��ܷ�ȡһ��ֵ��
����������$T_{x-1}$��$sum_y$����·���ϵ�$size+1$���Ϳ���ʵ��ɾ��һ��$sum_y$�ˡ�
�޸�$T_{x-1}$֮������һ����$sum_{x-1}$������ģ���$x$�ӵ����
���$Modify$��$Insert$����һģһ�����������Ҿ�Ȼûע�⵽���=-=����

$Solution2$
$sum_i\ ^{\wedge}sum_j=sum_j\ ^{\wedge}sum_i$�����Կ��԰�$k$���$2k$��������һ��������ܵõ�������$k$���Ƕ��١�
��ÿ������һ�º�������������ĸ����ӵ����
ÿ�δӶ���ȡ��ֵ����һ����$i$������$i$�Ĵ𰸡�Ȼ������Ҫ�ң���$sum_i$���ڶ����ֵ���ĸ�����$Trie$�ϲ鼴�ɡ����ӵ��������һ�ξͲ飬��$sum_i$����$3$���ֵ���ĸ�...
����������һ��$Trie$���ɡ�

$Solution3$
��һ������[[NOI2010]��������]��������
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
