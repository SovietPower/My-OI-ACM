/*
31ms	3700KB
����ͨ�����������Զ��ֳ����ֵ��
Ȼ��ʣ��$30$�β���һ�ܸ�ʲô�ء���ֻ�ܰ�����ȷ������������ĳЩ�����������ĺ���������ȷ��$30$������
�Ȳ�����������������������Եõ�$x\cdot d$����ȷ����������������Ȼ��Բ���$\gcd$�����п��ܵõ�������$d$�ġ�
��ȷ�����Ƕ����أ��о�ͦ�ߵġ���Ȼ�������ֵ�й���������ˡ�
[�ٷ����](https://codeforces.com/blog/entry/65136)�ж���ȷ������֤������Լ��$1.86185\times10^{-9}$��

�����ʱ��������ֻ��������������Ĳ�͹��ˣ�������Ҫ����������֮�����
*/
#include <ctime>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Flush() fflush(stdout)
typedef long long LL;
const int N=1e6+5;

int id[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Rd()
{
	return rand()<<15|rand();
}
inline int Query1(int n)
{
	int p=Rd()%n+1;
	printf("? %d\n",id[p]), Flush();
	std::swap(id[p],id[n]);//����ôдҲ�� ��𲻴� ����ν�� 
	return read();
}
inline int Query2(int x)
{
	printf("> %d\n",x), Flush();
	return read();
}

int main()
{
	static int A[66];
	srand(time(0));
	int n=read();
	int l=0,r=1e9,mid,mx=0,rest=60;
	while(l<=r)
		if(--rest,Query2(mid=l+r>>1)) mx=l=mid+1;
		else r=mid-1;

	for(int i=1; i<=n; ++i) id[i]=i;
	int t=0; rest=std::min(rest,n);
	for(int now=n; rest; --rest) A[++t]=Query1(now--);

	std::sort(A+1,A+1+t), A[++t]=mx;
	int d=A[2]-A[1];
	for(int i=3; i<=t; ++i) if(A[i]!=A[i-1]) d=std::__gcd(d,A[i]-A[i-1]);
	printf("! %d %d\n",mx-(n-1)*d,d), Flush();

	return 0;
}
