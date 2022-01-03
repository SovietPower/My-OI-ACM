//找到令会使环断开0的时候，从那开始枚举就行了。最差也是O(n)的啊。。我可能是个zz。
//到达每个位置时间是确定的：i+k*n，这样对每个位置算出最小的满足i+k*n>=A[i]的值就行了。
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
