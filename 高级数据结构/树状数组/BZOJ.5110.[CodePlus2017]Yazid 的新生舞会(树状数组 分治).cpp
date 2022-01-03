/*
17424kb	2664ms
$Description$
����һ������$A_i$�����ж��ٸ������䣬����������������ִ����������䳤�ȵ�һ�롣
$n\leq5\times10^5,\ 0\leq A_i\lt n$��
$Solution$
����$x$��Ϊ�����Ϸ�����������Щ����$B_i=\ A_i==x?1:-1$����$B_i$���ǰ׺��$s_i$�������->���㣩����ô����$[l,r]$�Ϸ����ҽ���$s_r-s_{l-1}\gt0$��
��ʵ���Ƕ�$s_i$��˳��Ը���������״�������ֵ���߶�������$O(n\log n)$����ô�ܸ��Ӷ���$O(n^2\log n)$�ģ�ö��$O(n)$��$x$�����������������Թ�$type=1$�ĵ��ˣ�
����ö��$x$��Ϊ����ʱ��$B_i,s_i$��ʲô���ʡ�
$Sol1$
���Ƿ���$B$���л�������$1$�ͺܶ�������$-1$�Ρ�������$-1$�ǿ���һ����ġ�
���߶���ά��$s$��ֵ���У�$[-n,n]$��ÿ��ֵ֮ǰ���ֹ����ٴΡ�
��������һ�μ���$-1$����$[l,r]$��$s_{l-1}=sum$����Ϊ$s_i$�ǵݼ��ģ����׷��ֶ�������䣬����Ҫ��ѯ����$[-n,sum-2],[-n,sum-3],...$��Щ����ĺ͡�Ȼ���������ĸ��¾��Ƕ�$[sum-1,sum-(r-l+1)]$����$+1$��
���ǲ�ѯ��ʱ���������ʲô����$T_i$Ϊ��״����/�߶������±�$i$λ�õ�ֵ��$i$֮ǰ���ֵĴ�������$len=r-l+1$������$T_i$��ͳ�ƵĴ�������$$Ans=\sum_{i=-n}^{sum-1-len}len*T_i+\sum_{i=sum-len}^{sum-2}T_i(sum-1-i)$$

�������߶���ά��$\sum T_i,\ \sum i*T_i$�ͺ��������Ӷ�$O(n\log n)$��
��״����Ҳ����ά��������ӵȲ����У�����Ȼ��û������ôʵ�֣����Կ�[��ƪ����](https://blog.csdn.net/baidu_36797646/article/details/80081085)orz��

$Sol2$
��һ��������[TAү(~~��������ô��~~)������](https://blog.csdn.net/TA201314/article/details/78948477)��
���ǿ����Ż�ö������$x$�����ⷽ����
��Ϊ��������кܶ�$-1$�����ܹ����ֺ�Ϊ��������кϷ����䡣��ô$i$����Ϊĳ�������Ϸ�������Ҷ˵�$r$���ҽ�����$B_l+B_{l+1}+..+B_i=0$����$i$��������ǰ׺�ͷ�������˵�ͬ��
��ô���ء�������$+1$�������ƣ�����$-1$����$+1$�û��$+1$�˾ͽ����������Ὣ���зָ��һ�ζ�С���䣬ÿ��С�����ǺϷ��ġ�����֪����ô˵.jpg��
���ѷ��ֶ�������ö����ЩС������$O(n)$�ġ������������Ǹ�$O(n^2\log n)$���㷨ֱ�ӷֱ�����ЩС����ͺ��ˡ����Ӷ�$O(n\log n)$��
���ǵ��������飬����ֱ����״���顣

$Sol3$
���֣��о��Ƚϱ����ģ�����������
�赱ǰ������$[l,r]$���е�Ϊ$mid$��ע�⵽һ�������ǣ���$x$������$[l,r]$����������ô��������$k\in[l,r)$��$x$����������$[l,k]$������$(k+1,r]$����������ôȡ$k=mid$������������Ϳ���������о���$mid$�������У�������Ϊ������������Щ��ע��һ�����������ֻ��$O(\log n)$����
Ȼ��Ϳ���ö��ÿ������������������������Щ����$mid$��������ɨ���ξͲ���ǡ�
���Ӷ�$O(n\log^2n)$��ʵ��������ͦ����İȡ������ܻ���$Sol2$�ţ���

�ƺ�����$O(n)$�ģ�emm��LOJͳ�ưȡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int beg[N],ed[N],pre[N],nxt[N],A[N],B[N];
bool tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct BIT
{
	int D,n,t[N<<1];
	#define lb(x) (x&-x)
	void Add(int p,int v)
	{
		for(p+=D; p<=n; p+=lb(p)) t[p]+=v;
	}
	int Query(int p)
	{
		int res=0;
		for(p+=D; p; p^=lb(p)) res+=t[p];
		return res;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(); read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) pre[i]=ed[A[i]], ed[A[i]]=i;
	for(int i=n; i; --i) nxt[i]=beg[A[i]], beg[A[i]]=i;
	LL ans=0; T.D=n, T.n=n<<1, T.Add(0,1);
	for(int x=0; x<n; ++x)
	{
		if(!beg[x]) continue;
		for(int i=beg[x]; i; )
		{
			int p=i; B[p]=1;//
			for(int t=1; p<=n&&t>=0; ++p,t+=B[p]=(A[p]==x?1:-1)) tag[p]=1;
			while(i && i<p) i=nxt[i];
		}
		for(int i=ed[x]; i; )
		{
			int p=i; B[p]=1;
			for(int t=1; p&&t>=0; --p,t+=B[p]=(A[p]==x?1:-1)) tag[p]=1;
			while(i>p) i=pre[i];
		}
		for(int i=beg[x]; i; )
		{
			int p=i;
			while(tag[p-1]) --p;
			int tmp=p,t=0;
			while(p<i) T.Add(--t,1), ++p;//�ⲿ����Ȼû��Query�ı�Ҫ��
			while(tag[p]) T.Add(t+=B[p],1), ans+=T.Query(t-1), ++p;
			p=tmp,t=0;
			while(p<i) T.Add(--t,-1), tag[p++]=0;
			while(tag[p]) T.Add(t+=B[p],-1), tag[p++]=0;
			while(i && i<=p) i=nxt[i];//<=
		}
	}
	printf("%lld\n",ans);

	return 0;
}
