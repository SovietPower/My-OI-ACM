/*
53ms	4992KB
$Description$
����$n$��Ҫ����һ��$n\times n$�ľ��󣬾����ڵ�Ԫ��������ͬ�����������ڵ�����Ԫ��$x,y$������$\max(x,y)\ \mathbb{mod}\ \min(x,y)$����һ�����㳣����
$n\leq500,\ 1\leq �����е�Ԫ��\leq10^{15}$��

$Solution$
����û��Ԫ�ػ�����ͬ�����ƣ���ô��ֱ����$x,x+1,x,x+1...$�����Ծ���ڰ�Ⱦɫ���ڸ�����$x$���׸�����$x+1$��
��������ƣ����ɿ����Ⱥڰ�Ⱦɫ��Ȼ����׸��ӱ���Χ�ĸ��ڸ��Ӷ��󡣾���$\max(x,y)\ \mathbb{mod}\ \min(x,y)=1$���ˣ������׸��ӵ�Ȩֵ������Χ�ĸ��ڸ��ӵ�$LCM+1$��
��������ֱ�������ڸ��Ӹ�Ȩֵ��Ԫ���ǻᳬ��$10^{15}$�ġ�
��Ϊ����$LCM$��������ڸ��Ӹ��ݶԽ�������������ĳ˻���������������-���º�����-������$2n$���Խ��ߣ�ֻ���Ǻڸ��ӣ����ֱ����һ��������һ���ڸ��ӵ������ڵ������Խ����ϵ����ĳ˻���
Ҫ��֤����Ԫ�ػ�����ͬ�����Կ��ǰ���$2n$�������$2n$��������
��ô�������İ׸��ӣ�Ȩֵ��$��499������\times��500������\times��999������\times��1000������<8\times10^{14}$����ô��OK����

$n=2$ʱ���ԣ�Ҫ���С�
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=505,M=8100;

int P[1005];
LL A[N][N];

void Init()
{
	static bool notP[M];
	for(int cnt=0,i=2; cnt<1000; ++i)
	{
		if(!notP[i]) P[++cnt]=i;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<M; ++j)
		{
			notP[v]=1;
			if(!(i%P[j])) break;
		}
	}
}
inline LL LCM(LL x,LL y)//longlong
{
	return x/std::__gcd(x,y)*y;
}

int main()
{
	Init();
	int n; scanf("%d",&n);
	if(n==2) return printf("4 7\n23 10\n"),0;
	for(int i=0; i<=n+1; ++i) A[0][i]=1, A[n+1][i]=1, A[i][n+1]=A[i][0]=1;
	for(int i=1; i<=n; ++i)
		for(int j=i&1?1:2; j<=n; j+=2)
			/*if(!(i+j&1))*/ A[i][j]=P[i+j>>1]*P[(i-j+n+1)/2+n];
	for(int i=1; i<=n; ++i)
		for(int j=i&1?2:1; j<=n; j+=2)
			/*if(i+j&1)*/ A[i][j]=LCM(LCM(A[i-1][j],A[i][j-1]),LCM(A[i+1][j],A[i][j+1]))+1;
	for(int i=1; i<=n; ++i,putchar('\n'))
		for(int j=1; j<=n; ++j) printf("%lld ",A[i][j]);

	return 0;
}
