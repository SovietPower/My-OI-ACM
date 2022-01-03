/*
0MS 1564K
$Description$
有n(n<=10)种硬币，已知每种硬币的数量和它抛一次正面朝上的概率pi。进行如下过程：每次抛一次所有硬币，将正面朝下的硬币去掉。重复该过程直到只剩一种硬币或是没有硬币。
如果结束时还剩下一种硬币，那称它是LuckyCoin。求每种硬币成为LuckyCoin的概率。
$Solution$
我们只需要枚举在第j轮，硬币i死亡(这个词形象233)，其它硬币在第j轮之前死亡的概率。
由给出的概率及六位小数可以看出，枚举到100轮就很够了。于是可以dp计算每种硬币在第j轮死亡的概率，然后前缀和一下，枚举轮数。(据说复杂度有点高？不太懂，不深究了...)
f[i][j]表示在第j轮 硬币i死亡的概率，那么 f[i][j] = (1-p_i^j)^{num_i} (num_i枚硬币都挂掉才死亡；算存活概率的话好像因为有多个很不好算)
g[i][j]表示在第j轮之后 硬币i仍存活的概率，那么 g[i][j] = 1 - f[i][j].
为了不重复统计(在第j+1轮i存活，但却计算在第j轮之前就死亡的所有硬币)，对于每轮我们用i在j轮还存活，j+1轮i全部挂掉的概率，即g[i][j]-g[i][j+1].
Ans[i] = ∑(j=1~100)(g[i][j]-g[i][j+1])*∏(k=1~n,k!=i)f[k][j]

我想问为什么存下g[i][j]=1-f[i][j]，计算用g[][]就对，而不存直接用1-f[][]这个式子答案怎么需要+1。。(精度？)
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=12;

int n,num[N];
double p[N],f[N][103],g[N][103];

inline double FP(double x,int k)//第一次写double快速幂。。
{
	double t=1.0;
	for(; k; k>>=1,x=x*x) if(k&1) t=t*x;
	return t;
}

int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1; i<=n; ++i) scanf("%d%lf",&num[i],&p[i]);
		if(n==1) {puts("1.000000"); continue;}
		for(int i=1; i<=n; ++i)
		{
			double pw=p[i];
			for(int j=1; j<100; ++j,pw*=p[i]) f[i][j]=FP(1.0-pw,num[i]),g[i][j]=1-f[i][j];
		}
		for(int i=1; i<=n; ++i)
		{
			double res=0;
			for(int j=1; j<100; ++j)
			{
				double pro=1.0;
				for(int k=1; k<=n; ++k) if(k!=i) pro*=f[k][j];
				res += (f[i][j+1]-f[i][j])*pro;
//				res += (1-f[i][j]-1+f[i][j+1])*pro;
//				res += (g[i][j]-g[i][j+1])*pro;
			}
			printf("%f%c",res+1,i==n?'\n':' ');
		}
	}
	return 0;
}
