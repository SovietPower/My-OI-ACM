/*
悬线法： 
有效竖线：指除两端点外，不覆盖任何障碍点的竖直线段 
悬线：上端点覆盖了一个障碍点或达到上边界的有效竖线(下端点无要求)
通过枚举所有的悬线，可以枚举出所有的极大子矩形。
悬线都与它底部的点一一对应，所以悬线个数 = (n-1)*m
每个极大子矩形都可以由一个悬线左右平移得到。对于每个确定了底部的悬线，只要知道其顶部、左右最多能移动到的位置，就可以算出面积 
对于以点(i,j)为底部的悬线：
若(i-1,j)为障碍点，则以(i,j)为底的悬线为1，左右均可以移动到矩形的左右边界 
	h[i,j] = 1, l[i,j] = 1, r[i,j] = m 
若(i-1,j)不是障碍点，则以(i,j)为底的悬线就是 以(i-1,j)为底的悬线高度 + (i-1,j)->(i,j)这条线段长度 
	h[i,j] = h[i-1,j]+1
	l[i,j] = max( l[i-1,j] , (i-1,j)左边第一个障碍点的位置 )
	r[i,j] = min( r[i-1,j] , (i-1,j)右边第一个障碍点的位置 )
(这是递推，至于下面这个写法。。)

对于本题，因为是01相间，1.可以将 (i+j)%2=1 的位置的0/1取反，求一遍最大0/1子矩阵/方阵大小。0和1都要求一遍 
2.特判即可 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=2005;

int n,m,l[N][N],r[N][N],h[N][N],Ss,Sm;
bool col[N][N];

inline int read()
{
	int now=0;register char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now;
}

int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			col[i][j]=read();
			if(i==1) h[i][j]=1;
			else if(col[i][j]!=col[i-1][j])
				h[i][j]=h[i-1][j]+1;
			else
				h[i][j]=1;
		}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			l[i][j]=j;
			while(l[i][j]>1 && h[i][l[i][j]-1]>=h[i][j] && col[i][l[i][j]-1]!=col[i][l[i][j]])
				l[i][j]=l[i][l[i][j]-1];
		}
		for(int j=m;j;--j)
		{
			r[i][j]=j;
			while(r[i][j]<m && h[i][r[i][j]+1]>=h[i][j] && col[i][r[i][j]+1]!=col[i][r[i][j]])
				r[i][j]=r[i][r[i][j]+1];
		}
		for(int j=1;j<=m;++j)
		{
			int t=min(r[i][j]-l[i][j]+1,h[i][j]);
			Ss=max(Ss,t*t);
			Sm=max(Sm,(r[i][j]-l[i][j]+1)*h[i][j]);
		}
	}
	printf("%d\n%d",Ss,Sm);

	return 0;
}
