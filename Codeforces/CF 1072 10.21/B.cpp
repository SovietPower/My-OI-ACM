#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int n,A[N][2],B[N][2],ans[N][2];

void Check()
{
	for(int i=n-1; i; --i)
		for(int j=0; j<2; ++j)
		{
			if(A[i][j]&&B[i][j])
			{
				if(!ans[i+1][j]) return;
				ans[i][j]=1;
			}
			else if(!A[i][j]&&!B[i][j])
			{
				if(ans[i+1][j]) return;
				ans[i][j]=0;
			}
			else if(!A[i][j]&&B[i][j]) return;
			else if(A[i][j]&&!B[i][j])
			{
				if(ans[i+1][j]) ans[i][j]=0;
				else ans[i][j]=1;
			}
		}
	for(int i=1; i<n; ++i)
		for(int j=0; j<2; ++j)
			if((A[i][j]!=(ans[i][j]|ans[i+1][j]))||(B[i][j]!=(ans[i][j]&ans[i+1][j])))
				return;
	puts("YES");
	for(int i=1; i<=n; ++i) printf("%d ",ans[i][1]*2+ans[i][0]);
	exit(0);
}

int main()
{
	n=read();
	for(int i=1,ai; i<n; ++i)
		ai=read(), A[i][0]=ai&1, A[i][1]=ai>>1&1;
	for(int i=1,bi; i<n; ++i)
		bi=read(), B[i][0]=bi&1, B[i][1]=bi>>1&1;

	ans[n][0]=0, ans[n][1]=0, Check();
	ans[n][0]=0, ans[n][1]=1, Check();
	ans[n][0]=1, ans[n][1]=0, Check();
	ans[n][0]=1, ans[n][1]=1, Check();

	puts("NO");

	return 0;
}
