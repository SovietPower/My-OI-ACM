/*
31ms	0KB
`sort`一下从中间往左右依次分配。没证，但感觉就是对的。
*/
#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e3+5;

int A[N],B[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	std::sort(A+1,A+1+n);
	int mid=n+1>>1; B[mid]=A[1];
	for(int i=3,t=mid-1; i<=n; i+=2) B[t--]=A[i];
	for(int i=2,t=mid+1; i<=n; i+=2) B[t++]=A[i];
	for(int i=1; i<=n; ++i) printf("%d ",B[i]);

	return 0;
}
