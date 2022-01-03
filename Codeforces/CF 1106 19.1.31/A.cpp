#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define mod 1000000007//998244353
//#define Mod(x) x>=mod&&(x-=mod)
//#define Add(x,v) (X+=v)>=mod&&(X-=mod)
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=505;

char s[N][N];

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
	for(int i=1; i<=n; ++i) scanf("%s",s[i]+1);
	int ans=0;
	for(int i=2; i<n; ++i)
		for(int j=2; j<n; ++j)
			if(s[i][j]=='X'&&s[i-1][j-1]=='X'&&s[i-1][j+1]=='X'&&s[i+1][j-1]=='X'&&s[i+1][j+1]=='X') ++ans;
	printf("%d\n",ans);

	return 0;
}
