/*
1308kb	2148ms
���⼴���$k$����ƽ����������
> ��ƽ��������(Square-Free Number)�����ֽ�֮�������������Ĵ�����Ϊ1����

�����뵽Ī����˹����������$n$�Ǵ𰸣���ô��$$k=n-\sum_{i=1}^n(1-|\mu(i)|)$$
���������ܿ���$x$���Ͻ磬�����$\sum$�϶���$<\frac{n}{2}$�ģ�����$n\leq 2*k$��
����һ��$n$����$[1,n]$���ж��ٸ���ƽ����������
��Ȼ���Ÿ�ƽ���Ͷ������������ݳ⣬����$[1,\sqrt{n}]$�е���������Ϊ$$[1,n]��0������ƽ�������ĸ���-1������ƽ�������ĸ���+2������ƽ�������ĸ���-\ldots$$
����������������ƽ������Ϊ����ż��������Ϊ����������ĳ�������ӵĴ���$>1$����ô�Դ�û��Ӱ��(��$pi^2*pj^2$�ڼ���$pi*pj$ʱͳ���˸���)����Ҳ����Ī����˹�������ص㡣��ô�𰸿���дΪ��$$\sum_{i=1}^{\lfloor\sqrt{n}\rfloor}\mu(i)*\lfloor\frac{n}{i^2}\rfloor$$
$r$�����$2e9$������$l+r$���ܱ�int��
*/
#include <cmath>
#include <cstdio>
const int N=5e4;//50000���У�

int cnt,P[10005],mu[N+3],pw[N+3];
bool Not_P[N+3];

void Init()
{
	mu[1]=1;
	for(int i=2; i<N; ++i)
	{
		if(!Not_P[i]) P[++cnt]=i,mu[i]=-1;
		for(int j=1; j<=cnt&&i*P[j]<N; ++j)
		{
			Not_P[i*P[j]]=1;
			if(i%P[j]) mu[i*P[j]]=-mu[i];
			else {mu[i*P[j]]=0; break;}
		}
	}
	for(int i=1; i<N; ++i) pw[i]=i*i;
}
bool Check(long long n,int K)
{
	int res=0;//res=n
	for(int i=1,lim=sqrt(n); i<=lim; ++i)
		if(mu[i]/*���?*/) res+=mu[i]*(n/pw[i]);
	return res>=K;
}

int main()
{
	Init();
	int T,K; scanf("%d",&T);
	long long l,r,mid;//!
	while(T--)
	{
		scanf("%d",&K), l=1, r=K<<1;
		while(l<r)
			if(Check(mid=(l+r)>>1,K)) r=mid;
			else l=mid+1;
		printf("%lld\n",l);
	}
	return 0;
}
