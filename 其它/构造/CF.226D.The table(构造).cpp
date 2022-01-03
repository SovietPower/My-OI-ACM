/*
62ms	0KB
$Description$
����һ��$n\times m$�ľ���$A_{i,j}$��ÿ�ο��Խ�һ�л�һ��ȡ������һ������ʹ�����ɴβ�����ÿ��ÿ�еĺͶ��Ǹ���
$n,m\leq100,\ Ԫ�ؾ���ֵ|A_{i,j}|\leq100$��

$Solution$
�����뵽ÿ���Һ�Ϊ����һ�л�һ��ȡ������������ȷ�Լ����ӶȻ���ɶ����ô��
ע�⵽ÿ��ȡ�����������ĺ��ǵ��������ģ�����һ�����������ÿ�κ����ٻ�����$2$��$-1\to1$�������������ĺ���С��$-10^6$�������$10^6$������������$10^6$�Σ����Ӷ�$O(10^6n)$��
�Լ�д��д��д�������鷳��������Ҫ`queue`��ÿ��$O(nm)$`for`һ�鷴ת���м��ɡ�
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
typedef long long LL;
const int N=105;

int A[N][N];
bool x[N],y[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Print(bool *a,int n)
{
	int t=0;
	for(int i=1; i<=n; ++i) t+=a[i];
	printf("%d ",t);
	for(int i=1; i<=n; ++i) a[i]&&printf("%d ",i);
	putchar('\n');
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) A[i][j]=read();
	for(; ; )
	{
		bool ok=1;
		for(int i=1; i<=n; ++i)
		{
			int s=0;
			for(int j=1; j<=m; ++j) s+=x[i]^y[j]?-A[i][j]:A[i][j];
			if(s<0) x[i]^=1, ok=0;
		}
		for(int j=1; j<=m; ++j)
		{
			int s=0;
			for(int i=1; i<=n; ++i) s+=x[i]^y[j]?-A[i][j]:A[i][j];
			if(s<0) y[j]^=1, ok=0;
		}
		if(ok) break;
	}
	Print(x,n), Print(y,m);

	return 0;
}
