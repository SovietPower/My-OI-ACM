/*
O(nk)����ֱ�ӵ���60�֣�����Ҫ��������ƣ�
��Ŀ������Ȼ������������Ķ�������������nk����Ʒ��ѡģk����r����Ʒ�ķ����������Ǽ�ΪF(nk,r)��
��ô�������������C(n,m)=C(n-1,m-1)+C(n-1,m)��F(n,m)=F(n-1,(m-1+k)%k)+F(n-1,m).
���ǾͿ�����DP O(nk)����ע�⵽���Ǹ����Ե���ʽ�������þ���������Ż���
����: ��k�������С��Ԫ��F(i)����һ��k�еľ���Ҫ���� F(i-1)*A[]=F(i)�����ѵó���f[i-1][j]��ת��f[i][k]ʱ��A[j][k]=1 
��������ױ�longlong,ֱ�ӿ�longlong�� 
K=1ʱӦ��++A[K-1][0]������A[0][0]=1ֱ�Ӹ�ֵ����
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
