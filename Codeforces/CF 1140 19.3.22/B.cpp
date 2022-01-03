#include <map>
#include <set>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=505;

char s[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int A(int n)
{
	for(int i=n; i; --i) if(s[i]=='<') return n-i;
	return n;
}
int B(int n)
{
	for(int i=1; i<=n; ++i) if(s[i]=='>') return i-1;
	return n;
} 

int main()
{
	for(int T=read(); T--; )
	{
		int n=read(); scanf("%s",s+1);
		printf("%d\n",std::min(A(n),B(n)));
//		if(s[1]=='<'&&s[n]=='>') puts("1");
//		else puts("0");
	}
	return 0;
}
