/*
54532kb	3584ms
��ϰһ�·��ݣ���Ȼ���ⲻ��ǰ�տ����������Ѿ�����=-=����
$Description$
����$n,m$����$$\sum_{i=1}^n\sum_{j=1}^m\mathbb{lcm}(i,j)$$
$n,m\leq10^7$��

$Solution$
emmm����д�ǣ���[����](https://blog.csdn.net/litble/article/details/79518721)�ȡ���·һ��Ҫ���졣
$[\gcd(i,j)=1]$���֣����ַ��ݲ���������$\sum_{d\mid n}\mu(d)=[n=1]$ȥ�滻��

��дһ����ɸ���Ժ���$F(T)=\sum_{d\mid T}d\mu(d)$�Ĳ��֣�
���ȶ���һ������$p$��$F(p)=\mu(p)+p\mu(p)=1-p$��
����$a$����С������$p$����$a,p$���ʣ���$F(ap)=F(a)F(p)$��
������Ϊ$F(p^k)$����$k$�Ǽ�����������������$F(p^k)=F(p)=1-p$������$F(ap)=F(\frac{a}{p^k})F(p^{k+1})=F(a)$��

����ѯ�ʸ��Ӷ�$O(\sqrt n)$�������������۷ֿ��������$O(n)$�ģ���
�����ԶŽ�ɸ=-=
*/
#include <cstdio>
#include <algorithm>
#define mod 20101009
#define Mod x>=mod&&(x-=mod)
#define Add (x+=v)>=mod&&(x-=mod)
#define S(x) ((1ll*(x)*(x+1)>>1)%mod)
typedef long long LL;
const int N=1e7+5;

int P[N>>3],F[N];
bool notP[N];

void Init(const int n)
{
	F[1]=1;
	for(int i=2,cnt=0; i<=n; ++i)
	{
		if(!notP[i]) P[++cnt]=i, F[i]=mod+1-i;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<=n; ++j)
		{
			notP[v]=1;
			if(i%P[j]) F[v]=1ll*F[i]*F[P[j]]%mod;
			else {F[v]=F[i]; break;}
		}
	}
	for(int i=1; i<=n; ++i) F[i]=(F[i-1]+1ll*F[i]*i)%mod;
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	if(n>m) std::swap(n,m);
	Init(n);
	LL ans=0;
	for(int i=1,nxt,t1,t2; i<=n; i=nxt+1)
	{
		t1=n/i, t2=m/i, nxt=std::min(n/t1,m/t2);
		ans+=1ll*S(t1)*S(t2)%mod*(F[nxt]-F[i-1]+mod)%mod;
	}
	printf("%lld\n",ans%mod);

	return 0;
}
