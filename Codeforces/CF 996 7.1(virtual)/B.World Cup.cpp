//�ҵ����ʹ���Ͽ�0��ʱ�򣬴��ǿ�ʼö�پ����ˡ����Ҳ��O(n)�İ������ҿ����Ǹ�zz��
//����ÿ��λ��ʱ����ȷ���ģ�i+k*n��������ÿ��λ�������С������i+k*n>=A[i]��ֵ�����ˡ�
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=1e5+5;

int n,A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	int mn=1e9;
	for(int i=1; i<=n; ++i) A[i]=read(), (mn>A[i])&&(mn=A[i]);
	int tag=mn, now=mn%n+1;
	while(1)
	{
		if(A[now]<=tag++) break;
		if(++now>n) now=1;
	}
	printf("%d",now);

	return 0;
}
