/*
$Description$
һ��$n\times n$�ķǸ���������$A$����֤$A_{i,i}=0$��������Ҫ��ÿ��$i$��$\min_{j\neq i}A_{i,j}$(ÿһ�г�$A_{i,i}$����Сֵ)������Խ��в�����$20$��ѯ�ʣ�ÿ��ѯ��������±꼯��$\{w_1,w_2,\ldots,w_k\}$����������ÿ��$i$����$\min_{j=1}^kA_{i,w_j}$(ÿһ�и����е���Сֵ)��
$n\leq 1000$��
$Solution$
����˼·��$i\neq j$��$i,j$������һλ��ͬ��
��ÿһλö��$0/1$���������±��λΪ$0/1$����Сֵ������ÿ��$i$������ĳλ��ͬ����ȫ��ȡ$\min$���ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1005;

int n,A[N][13][2],tag[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Query(int s,int bit)
{
	int t=0;
	for(int i=1; i<=n; ++i) if(tag[i]==s) ++t;
	printf("%d\n",t);
	for(int i=1; i<=n; ++i) if(tag[i]==s) printf("%d ",i);
	putchar('\n'); fflush(stdout);
	for(int i=1; i<=n; ++i) A[i][bit][s]=read();
}

int main()
{
	n=read();
	for(int i=0; 1<<i<=n; ++i)//��0����_��
	{
		for(int j=1; j<=n; ++j) if(j>>i&1) tag[j]=1;
		Query(0,i), Query(1,i);
		for(int j=1; j<=n; ++j) tag[j]=0;
	}
	puts("-1");//����ʽ��_����-1�������һ�� 
	for(int i=1; i<=n; ++i)
	{
		int ans=1e9;
		for(int bit=0; 1<<bit<=n; ++bit)
			ans=std::min(ans,A[i][bit][(i>>bit&1)^1]);
		printf("%d ",ans);
	}
	fflush(stdout);

	return 0;
}
