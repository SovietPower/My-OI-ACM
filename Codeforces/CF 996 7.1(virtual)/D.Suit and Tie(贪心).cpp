/*
�����1����i����ô��2��һ��ҲҪ����i���������ơ����������š�
��A,A'��ʾ������Եġ����Ǵ�1,2��ʼ�����A[2]!=A'[1]����ô�Ӻ����ҵ�A'[1]����������������A[2]��A'[2]����벻����
�����A[1]����ôA[1]��A'[1]����һ��������A[2]��A'[2]ȴԶ������������һֱ��֤��߷ֺ��˾����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=205;//2n!!!

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
	n=read()<<1;
	for(int i=1; i<=n; ++i) A[i]=read();
	int res=0;
	for(int i=2; i<=n; i+=2)
		if(A[i]!=A[i-1])
		{
			int pos;
			for(pos=i+1; pos<=n; ++pos)
				if(A[pos]==A[i-1]) break;
			for(int j=pos; j>i; --j)
				std::swap(A[j],A[j-1]), ++res;
		}
	printf("%d",res);

	return 0;
}
