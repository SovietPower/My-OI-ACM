/*
����DP��ע�⵽F(2n,(i+j)%K)=F(n,i)*F(n,j),����ֱ�Ӷ�DP���������(����)���� 
���Ӷ�O(k^2logn) 
*/
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N=1e6+5;

int n,p,K,r;
struct Array{
	LL A[53];
	void Clear(){
		memset(A,0,sizeof A);
	}
}F,tmp;

void Mult(Array &res,Array a,Array b)
{
	res.Clear();
	for(int i=0; i<K; ++i)
		for(int j=0; j<K; ++j)
			(res.A[(i+j)%K]+=a.A[i]*b.A[j]%p)%=p;
}

int main()
{
	scanf("%d%d%d%d",&n,&p,&K,&r);
	F.A[0]=1, ++F.A[1%K], tmp=F;//��ʼ����ֵ(F[0],F[1])��Ҫ���� 
	for(LL k=1ll*n*K-1; k; k>>=1,Mult(tmp,tmp,tmp))
		if(k&1) Mult(F,F,tmp);
	printf("%lld",F.A[r]);

	return 0;
}
