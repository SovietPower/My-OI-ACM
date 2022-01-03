/*
46ms	900KB
$Description$
������Ϊ$n$������$A_i$��$B_i$������Խ��������β�����ÿ�β�����ѡһ��$i\in[2,n-1]$����$A_i$���$A_{i-1}+A_{i+1}-A_i$��
���ܷ�����$A_i$���$B_i$��
$n\leq10^5$��

$Solution$
$A_i\to A_{i-1}+A_{i+1}-A_i$�����ʽ����Ȥ�����$A_i$�Ĳ������$d_i$���Կ���
��$d_{i-1}=A_i-A_{i-1},\ d_i=A_{i+1}-A_i$��
����任$A_i$����ô$d_{i-1}$����$A_{i+1}-A_i=d_i$��$d_i$����$A_i-A_{i-1}=d_{i-1}$��
Ҳ�������ǿ������⽻��$A_i$�Ĳ������$d_i$��
���������$B_i$�Ĳ������$d_i'$���ж�$d_i$�ܷ���$d_i'$������һ��$A_1$�Ƿ����$B_1$���ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int d1[N],d2[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline bool Check(const int n)
{
	for(int i=1; i<n; ++i) if(d1[i]!=d2[i]) return 0;
	return 1;
}

int main()
{
	const int n=read();
	int A1=read();
	for(int i=1,pre=A1,now; i<n; ++i) d1[i]=(now=read())-pre, pre=now;
	int B1=read();
	for(int i=1,pre=B1,now; i<n; ++i) d2[i]=(now=read())-pre, pre=now;
	std::sort(d1+1,d1+n), std::sort(d2+1,d2+n);
	puts(A1==B1&&Check(n)?"Yes":"No");

	return 0;
}
