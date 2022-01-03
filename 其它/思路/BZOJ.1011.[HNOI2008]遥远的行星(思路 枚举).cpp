/*
1992kb	3908ms
设当前为$i$，令$j=\lfloor a*i\rfloor$，$1\sim j$ 即为对$i$有贡献的行星，这一区间的答案应为$$f[i]=M_i*\sum_{k=1}^j\frac{M_k}{i-k}$$
因为误差不超过$5\%$即可，在这种条件下答案的范围应该非常宽。于是可以将要求的区间分成$T$段，每一段的分母$i-k$近似用该区间中点的分母表示。即$$f[i]=\sum_{t=1}^T(M_i *\frac{\sum_{k=x}^yM_k}{i-\frac{x+y}{2}})$$
其中$x,y$为每段起点/终点。
复杂度大概是$O(a*n^2/T)$？$T$这里取$150$了。
小于$T$的暴力计算，大于等于$T$的按上式近似计算。（或者$T$设得大一点，大于$T$的直接$O(1)$计算。）
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5,T=150;

int n,M[N];
LL sum[N];
double a;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),scanf("%lf",&a);
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+(M[i]=read());
	double res,mid;
	for(int p,i=1; i<=n; ++i)
	{
		p=int(a*i+1e-8);//一段区间的p会是相同的，也许可以少做乘法优化下常数。。
		res=0;
		if(p<=T){
			for(int j=1; j<=p; ++j)
				res+=1.0*M[j]/(i-j);
		}
		else{
			int lim=p/T*T;
			for(int j=1; j<lim; j+=T)
				res+=1.0*(sum[j+T]-sum[j-1])/(1.0*i-0.5*(j+j+T));
			for(int j=lim+1; j<=p; ++j)
				res+=1.0*M[j]/(i-j);
		}
		printf("%.6lf\n",res*M[i]);
	}

	return 0;
}
