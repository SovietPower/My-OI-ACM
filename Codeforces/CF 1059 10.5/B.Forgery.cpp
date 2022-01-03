#include <cstdio>
#include <cctype>
#define gc() getchar()
using namespace std;
const int N=1005,B=65;
const int dx[9]={-1,-1,-1,0,1,1,1,0};
const int dy[9]={-1,0,1,1,1,0,-1,-1};

int vis[N][N];
char s[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) scanf("%s", s[i] + 1);
	for(int i=2; i<n; ++i)
	{
		for(int j=2; j<m; j++)
		{
			bool flag=0;
			for(int k=0; k<8; k++)
			{
				int xn=i+dx[k], yn=j+dy[k];
				if(s[xn][yn] != '#')
				{
					flag=1;
					break;
				}
			}
			if(flag) continue;
			for(int k=0; k<8; k++)
			{
				int xn=i+dx[k], yn=j+dy[k];
				vis[xn][yn]=1;
			}
		}
	}
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; j++)
		{
			if(s[i][j]=='#' && vis[i][j]!=1)
			{
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
	return 0;
}
