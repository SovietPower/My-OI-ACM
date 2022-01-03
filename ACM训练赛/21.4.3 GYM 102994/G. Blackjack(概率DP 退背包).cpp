/*
358ms	4000KB
$Description$
����$a,b,n$��$n$��������$n$����������ȡһ������ֱ����ǰȡ�����ĺ�$sum\gt a$������ʱ$sum>b$���䣬����Ӯ����$n$����������е������Ӯ�ĸ��ʡ�
$n,a,b\leq 500$��
$Solution$
����������α�ʾ����һ�����У��о��Ǹ���·��
$f[i][j][k]$��ʾǰ$i$������ѡ������$j$����ѡ�����ĺ�Ϊ$k$�ĸ��ʡ���ǰ�����к�ǰ$i$������$j$���������ԣ�
$$f[i][j][k]=f[i-1][j][k]+f[i-1][j-1][k-A[i]]*\frac{j}{n-(j-1)}$$

ע��Ҫ��$j$����Ϊ����$j$���ǰ�˳��ȡ�ģ�����ʾ�������У���$j$���������г���$j!$����ʾȡ��$j$�������������е������

ע�����Ǹ��ӷ��ı��������Կ���[�˱���](https://www.cnblogs.com/SovietPower/p/9826829.html#b-%E9%80%89%E6%8B%A9%E9%A2%98dp-%E6%9C%9F%E6%9C%9B-%E9%80%80%E8%83%8C%E5%8C%85)������
$$f[i-1][j][k]=f[i][j][k]-f[i-1][j-1][k-A[i]]*\frac{j}{n-(j-1)}$$

ö�ٵ�$i$������������Ϊ���ѡ�е�����Ȼ���˱���ʹ���Ĺ��״�$f[n]$��ɾȥ��
��ô$A_i$��Ϊ���ѡ�е����ҺϷ��������Ϊ��
$$\sum_{j=0}^{n-1}\sum_{k,k<a\&k+A_i\in(a,b]}\frac{f'[j][k]}{n-j}$$

ע��Ҫ����$n-j$������ǰ��ѡ��$j$���޶�$i$Ϊ���һ���ĸ��ʡ�
ϵ����ϸ��Ҳ̫����©�ˡ�

���Ӷ�$O(n^3)$��

**PS��**CF�ϳ�����ͦ���... ����Ҫ��$\frac1i$�������ɳ˷���
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=505;

int A[N];
double f[N][N],g[N][N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read(),a=read(),b=read();
	for(int i=1; i<=n; ++i) A[i]=read();

	f[0][0]=1;
	for(int i=1,sum=0; i<=n; ++i)
	{
		sum=std::min(sum+A[i],b);
		for(int j=i,t=A[i]; j; --j)
			for(int k=sum; k>=t; --k)
				f[j][k]+=f[j-1][k-t]*j/(n-j+1);
	}
	double ans=0;
	for(int i=1; i<=n; ++i)
	{
		memcpy(g,f,sizeof f);
		for(int j=1,t=A[i]; j<n; ++j)
			for(int k=t; k<=b; ++k)
				g[j][k]-=g[j-1][k-t]*j/(n-j+1);
		for(int j=0,t=A[i]; j<n; ++j)
			for(int k=0; k<=a && k+t<=b; ++k)
				if(k+t>a) ans+=g[j][k]/(n-j);
	}
	printf("%.10f\n",ans);

	return 0;
}
