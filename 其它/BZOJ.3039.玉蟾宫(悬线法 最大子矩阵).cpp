#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1005;

int n,m,h[N][N],l[N][N],r[N][N];
bool Map[N][N];

int main()
{
	scanf("%d%d",&n,&m);
	char s[6];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			scanf("%s",s);
			if(s[0]=='F') Map[i][j]=1;
			if(Map[i][j]) h[i][j]=h[i-1][j]+1;
			else h[i][j]=0;//不为1，边界不能选择 
		}
	int Max=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			l[i][j]=j;
			while(l[i][j]>1 && h[i][l[i][j]-1]>=h[i][j] && Map[i][l[i][j]-1])
				l[i][j]=l[i][l[i][j]-1];
		}
		for(int j=m;j;--j)
		{
			r[i][j]=j;
			while(r[i][j]<m && h[i][r[i][j]+1]>=h[i][j] && Map[i][r[i][j]+1])
				r[i][j]=r[i][r[i][j]+1];
		}
		for(int j=1;j<=m;++j)
			Max=max(Max,(r[i][j]-l[i][j]+1)*h[i][j]);
	}
	printf("%d",3*Max);

	return 0;
}/*
5 6
R F F F F F
F F F F F F
R R R F F F
F F F F F F
F F F F F F
*/
