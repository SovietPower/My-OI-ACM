/*
����ʤ����������ǰʣ������(����-��Ƭ��)�йأ�������f[i][j][k]��ʾǰi���У�ʤ��j��������Ϊk�ĸ��� 
���ʤ����f[i][j][k] -> f[i+1][j+1][Turn(k+a[i])] (Turn��ʾ��Ӧ��ƫ��)
	ʧ�ܣ�f[i][j][k] -> f[i+1][j][k]
��ˢ����f[i+1][j+1][Turn(k+a[i+1])] += f[i][j][Turn(k)]
		  f[i+1][j][Turn(k)] += f[i][j][Turn(k)]
���ֻ��ͳ�� ��f[n][j][k] (j>=ʤ������ , k>=0)
(k�ܴ�n�Ƚ�С����ʵ��>n�Ĳ���(��������)�ͺ������壬����>nֱ����Ϊn����)
(����-��Ƭ������Ϊ������ΪֻҪ���n�غ��ܴ���ȥ�ͳ������м���зŲ��µ�����ܷ��µ������
���Ը���Ϊ�±��ǿ��еģ�Ҫƫ��)
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
		for(int j=0;j<=i;++j)//ʤ�� 
			for(int k=-i;k<=n;++k)//��ǰ���������п��� 
				f[i+1][j+1][Turn(k+a[i+1])]+=f[i][j][Turn(k)]*p[i+1],
				f[i+1][j][Turn(k)]+=f[i][j][Turn(k)]*(1.0-p[i+1]);
	double res=0.0;
	for(int i=l;i<=n;++i)//ʤ�������� 
		for(int j=0;j<=n;++j)//��������>=0�����ܴ���������Ƭ 
			res+=f[n][i][Turn(j)];
	printf("%.6lf",res);

	return 0;
}
