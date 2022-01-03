/*
答案与胜利场数、当前剩余容量(容量-碎片数)有关，所以设f[i][j][k]表示前i关中，胜了j场，容量为k的概率 
如果胜利，f[i][j][k] -> f[i+1][j+1][Turn(k+a[i])] (Turn表示对应的偏移)
	失败，f[i][j][k] -> f[i+1][j][k]
用刷表法，f[i+1][j+1][Turn(k+a[i+1])] += f[i][j][Turn(k)]
		  f[i+1][j][Turn(k)] += f[i][j][Turn(k)]
最后只需统计 ∑f[n][j][k] (j>=胜利关数 , k>=0)
(k很大，n比较小，但实际>n的部分(容量大了)就毫无意义，所以>n直接设为n即可)
(容量-碎片数可能为负，因为只要最后n关后能带出去就成立，中间会有放不下但最后能放下的情况。
所以负数为下标是可行的，要偏移)
*/
#include<cstdio>
#include<cctype>
using namespace std;
const int N=204;

int n,l,k,a[N];
double f[N][N][N<<1],p[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
inline int Turn(int x)
{
	if(x>n) x=n;
	return x+201;
}

int main()
{
	n=read(),l=read(),k=read();
	for(int i=1;i<=n;++i)
		scanf("%lf",&p[i]),p[i]/=100.0;
	for(int i=1;i<=n;++i)
		a[i]=read();
	f[0][0][Turn(k)]=1.0;
	for(int i=0;i<n;++i)
		for(int j=0;j<=i;++j)//胜场 
			for(int k=-i;k<=n;++k)//当前容量的所有可能 
				f[i+1][j+1][Turn(k+a[i+1])]+=f[i][j][Turn(k)]*p[i+1],
				f[i+1][j][Turn(k)]+=f[i][j][Turn(k)]*(1.0-p[i+1]);
	double res=0.0;
	for(int i=l;i<=n;++i)//胜场数满足 
		for(int j=0;j<=n;++j)//背包容量>=0，即能带走所有碎片 
			res+=f[n][i][Turn(j)];
	printf("%.6lf",res);

	return 0;
}
