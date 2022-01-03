/*
1992kb	3908ms
�赱ǰΪ$i$����$j=\lfloor a*i\rfloor$��$1\sim j$ ��Ϊ��$i$�й��׵����ǣ���һ����Ĵ�ӦΪ$$f[i]=M_i*\sum_{k=1}^j\frac{M_k}{i-k}$$
��Ϊ������$5\%$���ɣ������������´𰸵ķ�ΧӦ�÷ǳ������ǿ��Խ�Ҫ�������ֳ�$T$�Σ�ÿһ�εķ�ĸ$i-k$�����ø������е�ķ�ĸ��ʾ����$$f[i]=\sum_{t=1}^T(M_i *\frac{\sum_{k=x}^yM_k}{i-\frac{x+y}{2}})$$
����$x,y$Ϊÿ�����/�յ㡣
���Ӷȴ����$O(a*n^2/T)$��$T$����ȡ$150$�ˡ�
С��$T$�ı������㣬���ڵ���$T$�İ���ʽ���Ƽ��㡣������$T$��ô�һ�㣬����$T$��ֱ��$O(1)$���㡣��
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
		p=int(a*i+1e-8);//һ�������p������ͬ�ģ�Ҳ����������˷��Ż��³�������
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
