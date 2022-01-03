//https://www.cnblogs.com/SovietPower/p/9575160.html
/*
$Description$
��һ������Limak���Թ������ϵ�ĳ��������Ȼ����������ϵ�ÿ������$\frac{1}{2}$�ĸ�����ʧ������ ��������$x$Ϊ�����������߶�$ht(x)$Ϊ$x$����ʣ���(��x��ͨ)�������ȡ���$q$�β��������֣�
$1\ x$.�½�һ���ڵ㣬�丸�ڵ�Ϊ$x$��
$2\ x$.ѯ����������$x$Ϊ����������$x$�����������߶ȡ�
$q\leq 5\times10^5$��������һ��������
$Solution$
�������ǲ���Ҫ���Ǻܴ�ĸ߶�$h$������$h=100$��ͬʱ����$100$���ߵĸ��ʷǳ�С���ȼ����迼�ǵ����߶�$MAX\_H=60$��
����ѯ�ʣ�ֻҪ$x$��һ�������ĸ߶�Ϊ$h$�����������߶Ȳ�����$h$���Ϳ�����$p*h$���´𰸡�
so��$f[x][h]$��ʾ��$x$Ϊ����$ht(x)\leq h$�ĸ��ʡ����Ϊ$\sum_{h=1}^{MAX\_H}h\times(f[x][h]-f[x][h-1])$��
�����½��ڵ㣬����$fa$һֱ�������$MAX\_H$�Ρ�
$f[x][h]$��Ȼ�Ǵ�$f[son_x][h-1]$ת�ơ�ÿ���ӽڵ�$v$�����������һ�Ǵ��ڱߣ���$f[x][h]$����$\frac{1}{2}\times f[v][h-1]$�����ǲ����ڸñߣ�����Ϊ$\frac{1}{2}$��
����ʱ��Ȼ����$2^n$ö���ӽڵ㡣���ƶ���ʽ����$n$�����һ�𣬼�$$f[x][h]=\prod_{v=son_x}(\frac{1}{2}+\frac{1}{2}f[v][h-1])$$
���Ը��µ�ʱ���ԭ����������ٳ����µ���Ϳ����ˡ�

����$MAX\_H$��ȡֵ������ܻ���Ϊ$30$���㹻�ˣ���Ϊ$\frac{1}{2^{30}}$�Ѿ��㹻С����ʵ�ϣ�����һ���ջ�ͼ���Ӹ��ڵ������$\frac{n}{31}$��·������ÿ��·������Ϊ$31$����ô��$1$Ϊ������Ϊ$31$�ĸ���Ϊ��$$1-(1-\frac{1}{2^{31}})^{\frac{n}{31}}$$
���Ǵ���$10^{-6}$�ġ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define MAX_H 40
const int N=5e5+5;

int n,fa[N];
double f[N][MAX_H];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=1;
	for(int i=0; i<MAX_H; ++i) f[1][i]=1;
	for(int Q=read(),x; Q--; )
	{
		if(read()==1)
		{
			fa[++n]=x=read();
			for(int i=0; i<MAX_H; ++i) f[n][i]=1;
			double tmp1=f[x][0],tmp2;
			f[x][0]*=0.5;//��Ȼ��ǲ�����1�� 
			for(int Fa=fa[x],i=1; Fa&&i<MAX_H; Fa=fa[x=Fa],++i)
			{
				tmp2=f[Fa][i];
				f[Fa][i] /= 0.5 + 0.5*tmp1;
				f[Fa][i] *= 0.5 + 0.5*f[x][i-1];
				tmp1=tmp2;
			}
		}
		else
		{
			x=read(); double ans=0;
			for(int i=1; i<MAX_H; ++i) ans+=(f[x][i]-f[x][i-1])*i;
			printf("%.10lf\n",ans);
		}
	}
	return 0;
}
