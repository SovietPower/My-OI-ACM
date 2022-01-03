/*
233ms	2600KB
$Description$
������Ϊ$n$������$A_i$��һ������$K$���������ֳ����ɶΣ�����ÿ����ǡ�ó��ֹ�һ�ε����ĸ���$\leq K$���󷽰�����
$K\leq n\leq10^5$��
$Solution$
��$f[i]$��ʾǰ$i$�����Ĵ𰸣�$g[j]$��ʾ$j\sim i$ǡ�ó��ֹ�һ�ε����ĸ�������$$f[i]=\sum_{j\leq i,\ g[j]\leq K}f[j-1]$$

��$las_i$Ϊ$A_i$�ϴγ��ֵ�λ���±ꡣÿ��$i$�ƶ�ʱ��$g[j]$�ı仯���ǣ�$[las_i+1,i]$����$+1$��$[las_{las_i}+1,las_i]$����$-1$��
Ҳ����Ҫ��̬�޸�$g[j]$����$g[j]\leq K$��$f[j-1]$�ĺ͡�

���ݽṹʲô�Ĳ��ø㡣����ֱ�ӷֿ顣
һ����򵥵��뷨�ǣ�����`sort`��ά��ǰ׺�ͣ���ѯ��ʱ����֡����Ӷ�$O(n\sqrt n\log(\sqrt n))$��ע��ȷʵ��$\log(\sqrt n)$����������ȥ��

��$s[i][j]$��ʾ��$i$���У�$g[k]\leq j$��$f[k]$�ĺͣ�$tag[i]$��ʾ��$i$��������޸ı�ǡ�
���������޸ġ���������ֱ�Ӵ��ǡ�������ɢ���֣���Ϊֻ��$+1$�����׷��ֶ��ڵ�$i$�飬ֻ��$s[i][g[j]]$��ֵ�ı��ˣ���ֻ���ٵ���$f[j-1]$��$j$��Ӱ�쵽���±꣬��Ȼ���Ա���ö�٣�����ô���Ա�������$s[i]$��
��������Ĳ�ѯ�������ǵ�$i$�飬��Ҫ����$j+tag[i]\leq k$����$j\leq k-tag[i]$����ô$s[i][k-tag[i]]$���Ǵ��ˡ�
��ô�����Ϳ�������

��ʵ�������Ż���
��ÿ���޸Ĳ��ǰ׺�޸ģ�����$[1,i]$����$+1$��$[1,las_i]$����$-2$��$[1,las_{las_i}]$����$+1$��
������ʲô�ô��ء���$i$���ڵĿ�Ϊ$p$����ô��$p$����ɢ���ֱ����޸ģ���$1\sim p-1$��ͳһ���ϱ��$tag$��
���Է�������$s[i][j]$�ĵڶ�ά��$O(\sqrt n)$����ģ�ֻ��ͬ���ڵĻ�Ӱ����������ֵ����$tag$���ˣ���Ҳ���ǿռ�ֻ��Ҫ$O(n)$�͹��ˡ�
����������ǰ�ѯ��Ҳ���ǰ׺����ʽ����ʵ��������ǰ׺������$tag$��ȫ����Ҫֱ�Ӵ�$1\sim p-1$�ϣ�ֻ��Ҫ��$p$�ϴ�Ϳ����ˡ���ѯ��ʱ��ά��һ��$tag$�ĺ�׺�ͼ��ɡ�
��������СΪ$B$���޸ĸ��ӶȾ�ֻ��$O(B)$����ѯ���ӶȻ���$O(B+\frac nB)$������ĳЩ�޸ıȽ϶��ѯ�Ƚ��ٵ���Ŀ�Ϳ��Ե���$B$�Ĵ�С�������
��Ȼ�����⸴�Ӷ�������$O(n\sqrt n)$�����ǳ�����֪�����㵽������ȥ��

�м���̣�������ѯ��=-=��$s$�ĵڶ�ά�����Ǹ��ģ�������ֵ��$\sqrt n$�ڡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define B 150
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,M=N/B+3;

int bel[N],f[N],g[N],tag[M],s[M][B+3<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Update(int p,int v)
{
	int *s=::s[bel[p]];
	for(int i=B; i<=B<<1; ++i) Add(s[i],v);
}
void Modify(int p,int v)
{
	int bel=::bel[p],*s=::s[bel];
	tag[bel]+=v;
	for(int i=bel*B+1; i<=p; ++i)
	{
		if(v==1) Add(s[g[i]+B],mod-f[i-1]);
		else Add(s[g[i]-1+B],f[i-1]), Add(s[g[i]-2+B],f[i-1]);
		g[i]+=v;
	}
}
int Query(int p,int K)
{
	int bel=::bel[p],sum=tag[bel]; LL res=0;
	for(int i=bel*B+1; i<=p; ++i) g[i]<=K&&(res+=f[i-1]);
	while(bel--)
	{
//		assert(sum>=0);
//		if(sum<=K) res+=s[bel][std::min(B<<1,K-sum+B)];//WA:sum may be >K
		if(std::abs(sum-K)<=B) res+=s[bel][K-sum+B];
		else if(sum<K) res+=s[bel][B<<1];
		sum+=tag[bel];
	}
	return res%mod;
}

int main()
{
	static int las[N],pre[N];
	int n=read(),K=read();
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/B;
	f[0]=1;
	for(int i=1; i<=n; ++i)
	{
		int a=read(); las[i]=pre[a], pre[a]=i;
		Update(i,f[i-1]), Modify(i,1);
		if(las[i])
		{
			Modify(las[i],-2);
			if(las[las[i]]) Modify(las[las[i]],1);
		}
		f[i]=Query(i,K);
	}
	printf("%d\n",f[n]);

	return 0;
}
