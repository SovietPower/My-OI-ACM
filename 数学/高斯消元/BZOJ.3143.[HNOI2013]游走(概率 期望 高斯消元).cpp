/*
12784kb	740ms
$Description$
����������ͨͼ����$1$��ʼ������ߣ�����$n$������ÿ�߹�һ���߻������Ŷ�Ӧ�ķ��������ظ���ã�������ÿ���ߵı�ţ�ʹ�÷ֵ�����ֵ��С�������Сֵ��
$n\leq 500$��
$Solution$
��������ÿ���ߵĸ��ʳ��Ϸ���ı�ž��������������������ǿ϶��ǰѴ�ı�ŷ�����ߵĸ�����͵ıߡ�
��������ֻҪ������������е�ĸ��ʣ��Ϳ��Եó�����һ����($u->v$)�ĸ���$P_{ei}$����$dgr[i]$��ʾ��$i$�Ķ�������ô
$$P_{ei}=\frac{P_u}{dgr[u]}+\frac{P_v}{dgr[v]}$$
����ÿ����ĸ�����ô���أ�����
$$P_i=\sum_{(i,j)\in G}\frac{P_j}{dgr[j]}$$
������$a[i][j]$Ϊ�ӵ�$j$�ߵ���$i$�ĸ��ʣ���
$$a[i][j]=\frac{1}{dgr[j]}$$
������ôÿ����ĸ���
$$P_i=\sum_{(i,j)\in G} a[i][j]\times P[j]$$
����ע���ߵ�$n$�Ͳ��������ˣ����Ը�˹��Ԫ��������$n$�йصĶ�����
����$a[i][i]=1$��Ȼ���ÿ������$P_i$����һ�������������г�$n-1$����$n-1$��δ֪���ķ���
$$a[i][i]\times P_i-a[i][j]\times P_j-a[i][k]\times P_k-\ldots = 0$$
����ÿ��$a[i][i]$��Ӧ�ı�������$P_i$�ˡ�

������Ϊһ��ʼ����$1$�ŵ㣬���Ե�һ�����̵Ľ��Ӧ��Ϊ$1$����$P_1=1+\sum\frac{P_j}{dgr[j]}$��
������˹��Ԫ�����Ӷ�$O(n^3)$��������$\frac{1}{6}$�ĳ�����
ע�������û˵����n^2����ģ�
����(eps)Ҫ�ߣ�
md��˹д����
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
#define gc() getchar()
#define eps 1e-12
const int N=505,M=N*N*2;

int n,m,Enum,H[N],fr[M],to[M],nxt[M],dgr[N];
double A[N][N],Ans[N],pe[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	++dgr[u], to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[v], to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum;
}
inline bool cmp(const double &a,const double &b){
	return std::fabs(a)>std::fabs(b);
}
void Gauss()
{
	for(int j=1; j<n; ++j)
	{
		int mxrow=j;
		for(int i=j+1; i<n; ++i)
			if(cmp(A[i][j],A[mxrow][j])) mxrow=i;
		if(mxrow!=j) std::swap(A[mxrow],A[j]);//����һ��Ҳ��� 
//		if(mxrow!=j) for(int i=1; i<=n; ++i) std::swap(A[mxrow][i],A[j][i]);
		for(int i=j+1; i<n; ++i)
			if(fabs(A[i][j])>eps)//��һ����Ȼ��(��?) ��Ҫע�⾫�� 
//			if(A[i][j])
			{
				double t=A[i][j]/A[j][j];
				for(int k=j; k<=n; ++k)
					A[i][k]-=A[j][k]*t;
			}
	}
	for(int i=n-1; i; --i)
	{
		for(int j=i+1; j<n; ++j) A[i][n]-=A[i][j]*Ans[j];
		Ans[i]=A[i][n]/A[i][i];
	}
}

int main()
{
	n=read(),m=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);

	for(int x=1; x<n; A[x][x]=1.0,++x)
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=n) A[x][to[i]]=-1.0/dgr[to[i]];
	A[1][n]=1.0;
	Gauss();

	for(int i=1; i<=m; ++i) pe[i]=Ans[fr[i<<1]]/dgr[fr[i<<1]]+Ans[to[i<<1]]/dgr[to[i<<1]];
	std::sort(pe+1,pe+1+m,std::greater<double>());
	double res=0;
	for(int i=1; i<=m; ++i) res+=1.0*i*pe[i];
	printf("%.3lf",res);

	return 0;
}
