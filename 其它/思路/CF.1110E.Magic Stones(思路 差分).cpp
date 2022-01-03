/*
46ms	900KB
$Description$
给定长为$n$的序列$A_i$和$B_i$。你可以进行任意多次操作，每次操作任选一个$i\in[2,n-1]$，把$A_i$变成$A_{i-1}+A_{i+1}-A_i$。
求能否将序列$A_i$变成$B_i$。
$n\leq10^5$。

$Solution$
$A_i\to A_{i-1}+A_{i+1}-A_i$这个形式很有趣，求出$A_i$的差分序列$d_i$试试看。
令$d_{i-1}=A_i-A_{i-1},\ d_i=A_{i+1}-A_i$。
如果变换$A_i$，那么$d_{i-1}$会变成$A_{i+1}-A_i=d_i$，$d_i$会变成$A_i-A_{i-1}=d_{i-1}$。
也就是我们可以任意交换$A_i$的差分序列$d_i$。
所以再求出$B_i$的差分序列$d_i'$，判断$d_i$能否变成$d_i'$，再判一下$A_1$是否等于$B_1$即可。
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
