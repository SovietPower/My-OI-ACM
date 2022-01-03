/*
$Description$
每天晚上玩纸牌，每局获胜的可能性为$p$，如果当晚玩到某一局获胜局数比例大于$p$则停止游戏睡觉去第二天再玩，否则继续玩。每晚最多玩$n$局，如果$n$局玩完获胜比例仍然达不到$p$，则去睡觉以后再也不玩。问晚上玩牌的期望天数。
$Solution$
首先每一天之间是独立的。
所以设$f[i][j]$为前$i$天赢了$j$局的概率，要满足当前获胜比例始终≤$p$。容易得出转移方程。
所以玩完$n$局之后获胜比例仍不超过$p$的概率为$Q=\sum_{i=0}^{\frac in\leq p}f[n][i]$。
设$E$为期望玩牌天数。有两种情况：
1.$Q$的概率不再玩了，期望为$Q\times1$；
2.$1-Q$的概率第二天接着玩，期望为$(1-Q)\times(E+1)$。
所以$E=Q+(1-Q)\times(E+1)$，解得$E=\frac 1Q$。
有点迷，但好像也确实是这样。。
*/
#include <cstdio>
#include <algorithm>
const int N=105;

double f[N][N];

void Work(int T)
{
	int a,b,n;
	scanf("%d/%d%d",&a,&b,&n);
	double p=1.0*a/b;
	f[0][0]=1;
	for(int i=1; i<=n; ++i)
	{
		f[i][0]=f[i-1][0]*(1-p);
		for(int j=1; j<=i; ++j) f[i][j]=0;//!
		for(int j=1; j*b<=i*a; ++j)
			f[i][j]=f[i-1][j]*(1-p)+f[i-1][j-1]*p;
	}
	double q=0;
	for(int i=0; i*b<=n*a; ++i) q+=f[n][i];
	printf("Case #%d: %d\n",T,(int)(1.0/q));//直接.0lf是四舍五入...
}

int main()
{
	int T; scanf("%d",&T);
	for(int i=1; i<=T; Work(i++));
	return 0;
}
