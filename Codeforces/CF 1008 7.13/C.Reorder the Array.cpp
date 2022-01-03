#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

int n,A[N];
std::priority_queue<int> q;

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
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	for(int i=n; i; --i) q.push(A[i]);
	int ans=0;
	for(int i=n; i; --i)
	{
		while(!q.empty() && q.top()>=A[i]) q.pop();
		if(q.empty()) break; else ++ans, q.pop();
	}
	printf("%d",ans);

	return 0;
}
