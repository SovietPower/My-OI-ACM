/*
820kb	0ms
���������Ҫʤ������ô�ں��ֵ�һ��ȡ��ʯ�Ӻ� ����ʹʯ��������Ϊ0��������������Ϊ0�����Ի���ɶ���أ���֪������
��ǰ�룬���ֿ���ȡ��ĳЩʯ��ʹ��ʣ��ʯ������Ϊ0���ǲ����Ǵ�������Ϊ0���Ӽ��𡣡�
so����Ҫʹ����ȡ��󲻴�������Ϊ0���Ӽ����Ӵ�С���γ��Բ������Ի����ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Bit 30
const int N=105;

int n,A[N],base[36];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Insert(int v)
{
	for(int i=Bit,x=v; ~i; --i)
		if(x>>i & 1)
			if(base[i]) x^=base[i];
			else {base[i]=x; return 0;}
	return v;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	long long ans=0;
	for(int i=n; i; --i) ans+=Insert(A[i]);
	printf("%lld\n",ans);

	return 0;
}
