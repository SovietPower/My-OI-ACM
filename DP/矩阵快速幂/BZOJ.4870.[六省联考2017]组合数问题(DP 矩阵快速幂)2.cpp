/*
O(nk)可以直接递推60分，但不要被这个限制！
题目所求仍然可以用组合数的定义描述，即在nk个物品中选模k等于r个物品的方案数，我们记为F(nk,r)。
那么类似于组合数的C(n,m)=C(n-1,m-1)+C(n-1,m)，F(n,m)=F(n-1,(m-1+k)%k)+F(n-1,m).
于是就可以用DP O(nk)做。注意到这是个线性递推式，可以用矩阵快速幂优化。
具体: 把k做矩阵大小，元素F(i)看做一行k列的矩阵，要满足 F(i-1)*A[]=F(i)，不难得出当f[i-1][j]可转到f[i][k]时，A[j][k]=1 
另外很容易爆longlong,直接开longlong吧 
K=1时应是++A[K-1][0]而不是A[0][0]=1直接赋值。。
*/
#include <cstdio>
typedef long long LL;
const int N=1e6+5;

int n,p,K,r;
struct Matrix
{
	LL A[53][53];
	Matrix operator *(const Matrix a)const
	{
		Matrix res;
		for(int i=0; i<K; ++i)
			for(int j=0; j<K; ++j)
			{
				res.A[i][j]=0ll;
				for(int k=0; k<K; ++k)
					(res.A[i][j]+=A[i][k]*a.A[k][j]%p)%=p;
			}
		return res;
	}
//	void Print()
//	{
//		for(int i=0; i<K; ++i,putchar('\n'))
//			for(int j=0; j<K; ++j) printf("%d ",A[i][j]);
//	}
}mat,res;
Matrix FP(Matrix x,LL k)
{
	Matrix t=x; --k;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}

int main()
{
	scanf("%d%d%d%d",&n,&p,&K,&r);
	for(int i=0; i<K; ++i) mat.A[i][i]=1ll;
	for(int i=1; i<K; ++i) mat.A[i-1][i]=1ll;
	++mat.A[K-1][0];//!
	res.A[0][0]=1ll;
	res=res*FP(mat,1ll*n*K);
	printf("%lld",res.A[0][r]);

	return 0;
}
