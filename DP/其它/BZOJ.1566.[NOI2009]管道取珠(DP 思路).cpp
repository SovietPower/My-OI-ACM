/*
2816kb	1072ms
考虑$a_i^2$有什么意义：两个人分别操作原序列，使得得到的输出序列都为$i$的方案数。$\sum a_i^2$就是两人得到的输出序列相同的方案数。
$f[i][j][k]$表示第一个人上管道取到了第$i$个球，下管道取到了第$j$个球，第二个人上管道取到了第$k$个球，的方案数。转移很简单。
复杂度$O(n^3)$。
*/
#include <cstdio>
#include <algorithm>
#define mod 1024523
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=505;

int main()
{
	static int f[2][N][N];
	static char A[N],B[N];
	int n,m; scanf("%d%d",&n,&m);
	scanf("%s%s",A+1,B+1);
	std::reverse(A+1,A+1+n), std::reverse(B+1,B+1+m);
	A[n+1]='?', B[m+1]='!';
	int p=0; f[p][0][0]=1;
	for(int i=0; i<=n; ++i,p^=1)
		for(int j=0; j<=m; ++j)
			for(int k=0,v; k<=n; ++k)
				if((v=f[p][j][k]))
				{
					if(A[i+1]==A[k+1]) Add(f[p^1][j][k+1],v);
					if(A[i+1]==B[i+j-k+1]) Add(f[p^1][j][k],v);
					if(B[j+1]==A[k+1]) Add(f[p][j+1][k+1],v);//p不变啊（日常制杖）
					if(B[j+1]==B[i+j-k+1]) Add(f[p][j+1][k],v);
					if(i+j==n+m) return printf("%d\n",f[p][m][n]),0;
					f[p][j][k]=0;
				}
	puts("Miaomiaomiao?");

	return 0;
}
