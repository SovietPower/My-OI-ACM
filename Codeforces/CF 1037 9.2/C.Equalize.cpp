#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e6+5;

int n;
char A[N],B[N];

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
	scanf("%s%s",A+1,B+1);
	int ans=0;
	for(int i=1; i<n; ++i)
		if(A[i]!=B[i])
			if(A[i+1]!=B[i+1]&&A[i]==B[i+1]) std::swap(A[i],A[i+1]), ++ans;
			else ++ans;
	if(A[n]!=B[n]) ++ans;
	printf("%d\n",ans);

	return 0;
}
