/*
如果第1个是i，那么第2个一定也要换成i，依次类推。这样会最优。
用A,A'表示两个配对的。我们从1,2开始，如果A[2]!=A'[1]，那么从后面找到A'[1]把它换过来。这样A[2]和A'[2]间距离不会变大。
如果动A[1]，那么A[1]离A'[1]近了一步，但是A[2]离A'[2]却远了两步。这样一直保证左边分好了就行了。
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
