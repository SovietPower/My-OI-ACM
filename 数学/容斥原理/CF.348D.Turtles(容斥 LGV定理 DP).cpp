/*
498ms	44000KB
$Description$
����$n*m$��������Щ���Ӳ����ߡ����ж����ִ�$(1,1)$�ߵ�$(n,m)$���������ཻ·����
$n,m\leq 3000$��
$Solution$
�ݳ⣬���ܷ�������ȥ·��һ���ཻ�ķ�������
��ô���أ�ע�⵽�����ཻ��·����һ�������Կ�����$(1,2)$��$(n,m-1)$�ʹ�$(2,1)$��$(n-1,m)$������·�����ܷ�����Ҳ���Կ�����$(1,2)$��$(n-1,m)$�ʹ�$(2,1)$��$(n,m-1)$������·����������ཻ���ԶԳƹ�ȥ�õ�����������·������
����$(1,2)$��$(n-1,m)$�ķ�����������$(2,1)$��$(n,m-1)$�ķ���������ȥ��$(1,2)$��$(n-1,m)$�ķ�����������$(2,1)$��$(n-1,m)$�ķ����������Ǵ��ˡ�
��ʵ��Ҳ���Ǹо��е���...

��ʵ��һ������[Lindstr?m�CGessel�CViennot lemma](https://en.wikipedia.org/wiki/Lindstr?m�CGessel�CViennot_lemma)��
�����ճ[attack��](https://www.cnblogs.com/zwfymqz/p/10195838.html)�ˡ�
> ���������˵�㼯$A=\{a1,a2,��an\}$��$B=\{b1,b2,...,bn\}$�Ĳ��ཻ·��������������ʽ$$\begin{bmatrix}e(a_1, b_1) & e(a_1, b_2) & \dots & e(a_1, b_n) \\
e(a_2, b_1) & e(a_2, b_2) & \dots & e(a_2, b_n) \\
\vdots       & \vdots       & \ddots & \vdots       \\
e(a_n, b_1) & e(a_n, b_2) & \dots & e(a_n, b_n) \\
\end{bmatrix}$$��ֵ������$e(x,y)$��ʾ��$x$��$y$��·������
����ı��ʻ����ݳ⡣
���⣬������Ҫ�ҵ��������ཻ��·����ע�⵽�κ�һ�ԺϷ���·��һ�����Ա�ʾΪ��һ����$(1,2)$������$(n?1,m)$����һ����$(2,1)$������$(n,m?1)$��
��ôѡȡ$A=\{(1,2)\ (2,1)\},B=\{(n?1,m)\ (n,m?1)\}$�����뵽������������⡣

��ʵ��ֻ��һ��DP�Ϳ����ˣ�����DP���飬�ֱ��ʾ��$(1,2)$��$(2,1)$������`for`��$(n,m)$�Ϳ����ˣ�����
Ҳ���Լ�`fread`�����ø��ˡ�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
const int N=3005;

bool mp[N][N];

int Calc(int sx,int sy,int tx,int ty)
{
	static int f[N][N];
	memset(f,0,sizeof f);
	f[sx-1][sy]=1;//Init: f[sx][sy]=mp[sx][sy]==1;
	for(int i=sx; i<=tx; ++i)
		for(int j=sy; j<=ty; ++j)
			mp[i][j]?(f[i][j]=f[i-1][j]+f[i][j-1],Mod(f[i][j])):0;
	return f[tx][ty];
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	char s[N];
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s+1);
		for(int j=1; j<=m; ++j) mp[i][j]=s[j]=='.';
	}
	printf("%I64d\n",(1ll*Calc(1,2,n-1,m)*Calc(2,1,n,m-1)%mod+mod-1ll*Calc(1,2,n,m-1)*Calc(2,1,n-1,m)%mod)%mod);

	return 0;
}
