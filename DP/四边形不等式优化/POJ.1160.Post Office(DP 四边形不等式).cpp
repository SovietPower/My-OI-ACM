/*
$Description$
һ��ֱ������n����ׯ��λ�ø�����ͬ��ѡ��p����ׯ���ʾ֣���ÿ����ׯ������ʾֵľ���֮�͵���Сֵ��
$Solution$
�ȿ�����[l,r]��һ���ʾ֣����Ž�϶��ǽ����м䡣
����mid���߶Գƣ����������С�ģ�������mid-1��(����mid��mid-1���1)��Ȼ���mid-1����ׯdis��-1�ˣ������ұ���mid����ׯdis+1 
������䳤��Ϊż���������м�����λ������һ���������ŵġ� 
��f[i][j]��ʾ��ǰi����ׯ����j���ʾֵ���Сֵ����ô f[i][j] = min{ f[k][j-1]+dis(k+1,i) }
dis(k+1,i)��ʾֻ������[k+1,i]��һ���ʾֵ���Сֵ 
Ԥ����disʱ �����֪dis[i][j-1]����ô����j-1������ż��dis[i][j]������dis[i][j-1]+ j��i~j�е�ľ���(Ҳ�����������) 
����������ߵ�����P[i][j-1]<=P[i][j]<=P[i+1][j]��Ӧ�������ı��β���ʽ�Ż���O(np) 
~~���Ǵ�0ms�Ż�����16ms??~~0ms�� 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=305;

int n,m,A[N],f[N][35],dis[N][N],P[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DP1()//O(n^2m)
{
	for(int i=1; i<=n; ++i)
		for(int j=2; j<=m; ++j)//from 2
			for(int k=j-1; k<i; ++k)
				f[i][j]=std::min(f[i][j],f[k][j-1]+dis[k+1][i]);
}
void DP2()//O(nm)
{
	for(int tmp,j=2; j<=m; ++j)//��ö��j�� (��֪��Ϊʲô��i����==) 
	{
		P[n+1][j]=n-1;//�ϱ߽磡
		for(int i=n; i>=j; --i)
			for(int k=P[i][j-1]; k<=P[i+1][j]; ++k)
				if(f[i][j]>(tmp=f[k][j-1]+dis[k+1][i]))
					f[i][j]=tmp, P[i][j]=k;
	}
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
			dis[i][j]=dis[i][j-1]+A[j]-A[i+j>>1];
	memset(f,0x3f,sizeof f);
	for(int i=1; i<=n; ++i) f[i][1]=dis[1][i] ,P[i][i]=i;//Ԥ����
	DP2();
	printf("%d",f[n][m]);

	return 0;
}
