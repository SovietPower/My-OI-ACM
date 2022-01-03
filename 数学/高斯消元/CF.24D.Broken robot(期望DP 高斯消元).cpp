/*
62ms	7700KB
$Description$
有一个$n\times m$的网格，初始在$(x,y)$，每一步等概率不动或向上下左右走（如走了越界则不动）。求走到最后一行结束的期望步数。
$n,m\leq 1000$。
$Solution$
令$f[i][j]$表示从$(i,j)$到达最后一行的期望步数。那么有$f[n][j]=0$。
若$m=1$，答案是$2(n-x)$。
否则，显然有
$$f[i][1]=\frac13(f[i+1][1]+f[i][1]+f[i][2])+1\\ f[i][j]=\frac14(f[i+1][j]+f[i][j]+f[i][j-1]+f[i][j+1])+1,\ 1<j<m\\ f[i][m]=\frac13(f[i+1][m]+f[i][m]+f[i][m-1])+1$$

~~别忘了+1→_→~~
写成矩阵的形式，
$$2f[i][1]-f[i][2]=f[i+1][1]+3\\ -f[i][j-1]+3f[i][j]-f[i][j+1]=f[i+1][j]+4\\ -f[i][m-1]+2f[i][m]=f[i+1][m]+3$$

然后就可以一行一行高斯消元了。
注意到矩阵是个三对角矩阵，我们可以$O(n)$完成消元。
具体就是用第$i$行的两个变量消掉第$i+1$行的第$i$个变量，最后到第$m$行可以直接算出$f[i][m]$，代回去。
第一行有$2f[1]-f[2]=g[1]$，消掉第二行的$f[1]$变成$2.5f[2]-f[3]=g[2]+0.5g[1]$，系数改成$2$即$2f[2]-0.8f[3]=0.8(g[2]+0.5g[1])$，重复$m-2$次即可。最后会得到$m-1$个$2f[i]+a_if[i+1]=b_i$，用第$m$行求出$f[m]$，迭代回去。
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=1005;

double A[N],B[N],f[N][N];

int main()
{
	int n,m,x,y; scanf("%d%d%d%d",&n,&m,&x,&y);
	if(m==1) return printf("%.5f\n",2.0*(n-x)),0;
	for(int i=n-1; i>=x; --i)
	{
		A[1]=-1, B[1]=f[i+1][1]+3;
		for(int j=2; j<m; ++j)
		{
			A[j]=-1, B[j]=4+f[i+1][j]+0.5*B[j-1];
			double t=2/(3+0.5*A[j-1]); A[j]*=t, B[j]*=t;
		}
		B[m]=f[i+1][m]+3+0.5*B[m-1], f[i][m]=B[m]/(2+0.5*A[m-1]);
		for(int j=m-1; j; --j) f[i][j]=(B[j]-f[i][j+1]*A[j])*0.5;
	}
	printf("%.5f\n",f[x][y]);

	return 0;
}
