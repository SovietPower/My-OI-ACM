/*
���߷��� 
��Ч���ߣ�ָ�����˵��⣬�������κ��ϰ������ֱ�߶� 
���ߣ��϶˵㸲����һ���ϰ����ﵽ�ϱ߽����Ч����(�¶˵���Ҫ��)
ͨ��ö�����е����ߣ�����ö�ٳ����еļ����Ӿ��Ρ�
���߶������ײ��ĵ�һһ��Ӧ���������߸��� = (n-1)*m
ÿ�������Ӿ��ζ�������һ����������ƽ�Ƶõ�������ÿ��ȷ���˵ײ������ߣ�ֻҪ֪���䶥��������������ƶ�����λ�ã��Ϳ��������� 
�����Ե�(i,j)Ϊ�ײ������ߣ�
��(i-1,j)Ϊ�ϰ��㣬����(i,j)Ϊ�׵�����Ϊ1�����Ҿ������ƶ������ε����ұ߽� 
	h[i,j] = 1, l[i,j] = 1, r[i,j] = m 
��(i-1,j)�����ϰ��㣬����(i,j)Ϊ�׵����߾��� ��(i-1,j)Ϊ�׵����߸߶� + (i-1,j)->(i,j)�����߶γ��� 
	h[i,j] = h[i-1,j]+1
	l[i,j] = max( l[i-1,j] , (i-1,j)��ߵ�һ���ϰ����λ�� )
	r[i,j] = min( r[i-1,j] , (i-1,j)�ұߵ�һ���ϰ����λ�� )
(���ǵ��ƣ������������д������)

���ڱ��⣬��Ϊ��01��䣬1.���Խ� (i+j)%2=1 ��λ�õ�0/1ȡ������һ�����0/1�Ӿ���/�����С��0��1��Ҫ��һ�� 
2.���м��� 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=2005;

int n,m,l[N][N],r[N][N],h[N][N],Ss,Sm;
bool col[N][N];

inline int read()
{
	int now=0;register char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now;
}

int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			col[i][j]=read();
			if(i==1) h[i][j]=1;
			else if(col[i][j]!=col[i-1][j])
				h[i][j]=h[i-1][j]+1;
			else
				h[i][j]=1;
		}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			l[i][j]=j;
			while(l[i][j]>1 && h[i][l[i][j]-1]>=h[i][j] && col[i][l[i][j]-1]!=col[i][l[i][j]])
				l[i][j]=l[i][l[i][j]-1];
		}
		for(int j=m;j;--j)
		{
			r[i][j]=j;
			while(r[i][j]<m && h[i][r[i][j]+1]>=h[i][j] && col[i][r[i][j]+1]!=col[i][r[i][j]])
				r[i][j]=r[i][r[i][j]+1];
		}
		for(int j=1;j<=m;++j)
		{
			int t=min(r[i][j]-l[i][j]+1,h[i][j]);
			Ss=max(Ss,t*t);
			Sm=max(Sm,(r[i][j]-l[i][j]+1)*h[i][j]);
		}
	}
	printf("%d\n%d",Ss,Sm);

	return 0;
}
