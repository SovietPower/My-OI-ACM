/*
0MS 1564K
$Description$
��n(n<=10)��Ӳ�ң���֪ÿ��Ӳ�ҵ�����������һ�����泯�ϵĸ���pi���������¹��̣�ÿ����һ������Ӳ�ң������泯�µ�Ӳ��ȥ�����ظ��ù���ֱ��ֻʣһ��Ӳ�һ���û��Ӳ�ҡ�
�������ʱ��ʣ��һ��Ӳ�ң��ǳ�����LuckyCoin����ÿ��Ӳ�ҳ�ΪLuckyCoin�ĸ��ʡ�
$Solution$
����ֻ��Ҫö���ڵ�j�֣�Ӳ��i����(���������233)������Ӳ���ڵ�j��֮ǰ�����ĸ��ʡ�
�ɸ����ĸ��ʼ���λС�����Կ�����ö�ٵ�100�־ͺܹ��ˡ����ǿ���dp����ÿ��Ӳ���ڵ�j�������ĸ��ʣ�Ȼ��ǰ׺��һ�£�ö��������(��˵���Ӷ��е�ߣ���̫���������...)
f[i][j]��ʾ�ڵ�j�� Ӳ��i�����ĸ��ʣ���ô f[i][j] = (1-p_i^j)^{num_i} (num_iöӲ�Ҷ��ҵ���������������ʵĻ�������Ϊ�ж���ܲ�����)
g[i][j]��ʾ�ڵ�j��֮�� Ӳ��i�Դ��ĸ��ʣ���ô g[i][j] = 1 - f[i][j].
Ϊ�˲��ظ�ͳ��(�ڵ�j+1��i����ȴ�����ڵ�j��֮ǰ������������Ӳ��)������ÿ��������i��j�ֻ���j+1��iȫ���ҵ��ĸ��ʣ���g[i][j]-g[i][j+1].
Ans[i] = ��(j=1~100)(g[i][j]-g[i][j+1])*��(k=1~n,k!=i)f[k][j]

������Ϊʲô����g[i][j]=1-f[i][j]��������g[][]�Ͷԣ�������ֱ����1-f[][]���ʽ�Ӵ���ô��Ҫ+1����(���ȣ�)
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=12;

int n,num[N];
double p[N],f[N][103],g[N][103];

inline double FP(double x,int k)//��һ��дdouble�����ݡ���
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
