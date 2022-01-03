/*
374ms	147200KB
$Description$
����һ��n��͹�����(��֤û�����㹲��)��ѡ��һ������ÿ�������һ�εĲ����ཻ��·����ʹ���䳤��������������ȡ�
$Solution$
�·��Ӧ���Ǿ����ܶ��ߵ㡣��Ϊ·�����ཻ�������ǰ��x���´�Ӧ����x+1��x-1���ߣ�����Ҳ����ˣ�����ǰ����һ���������ġ�
����ͼ���Է��֣�ÿ��״̬Ӧ������߿����������߻��ұ߿����������ߡ�
��ô��f[i][j][0/1]��ʾ��[i,j]ʱ���/�ұ߿�����������ʱ���·�����ȡ�
i->j�ڻ���������·�����ⶼҪ���ǡ�����i>jʱ��ʾ��j��ʱ���ߵ�i����·��(i˳ʱ�뵽j)��
ת�ƿ��Դ�С����ÿ�γ���+1���Ƶ���ģ�����ֻ��O(n^2)��
f[i][j][0] = max(f[i+1][j][0]+dis(i,i+1), f[i+1][j][1]+dis(i,j)) (f[i][j-1][0/1]��Ȼ�����԰�)
f[i][j][1] = max(f[i][j-1][0]+dis(i,j), f[i][j-1][1]+dis(j,j-1))
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Turn(x) ((x+n-1)%n+1)
#define Calc(x,x2,y,y2) (sqrt(1.0*(x-x2)*(x-x2)+1.0*(y-y2)*(y-y2)))
const int N=2505;

int n,x[N],y[N];
double dis[N][N],f[N][N][2];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) x[i]=read(),y[i]=read();
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
			dis[j][i]=dis[i][j]=Calc(x[i],x[j],y[i],y[j]);
	double ans=0;
	for(int len=1; len<n; ++len)
		for(int i=1,j; i<=n; ++i)
		{
			j=Turn(i+len);
			f[i][j][0] = std::max(f[Turn(i+1)][j][0]+dis[i][Turn(i+1)], f[Turn(i+1)][j][1]+dis[i][j]);
			f[i][j][1] = std::max(f[i][Turn(j-1)][0]+dis[i][j], f[i][Turn(j-1)][1]+dis[j][Turn(j-1)]);
			ans=std::max(ans,std::max(f[i][j][0],f[i][j][1]));//��һ����n����...��?
		}
	printf("%.10lf\n",ans);

	return 0;
}
