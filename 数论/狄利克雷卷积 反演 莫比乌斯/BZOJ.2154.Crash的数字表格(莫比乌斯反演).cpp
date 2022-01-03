/*
54532kb	3584ms
复习一下反演（虽然这题不久前刚看过，但是已经忘了=-=）。
$Description$
给定$n,m$，求$$\sum_{i=1}^n\sum_{j=1}^m\mathbb{lcm}(i,j)$$
$n,m\leq10^7$。

$Solution$
emmm懒得写惹，看[这里](https://blog.csdn.net/litble/article/details/79518721)叭。套路一定要记熟。
$[\gcd(i,j)=1]$这种，那种反演不好做就用$\sum_{d\mid n}\mu(d)=[n=1]$去替换。

再写一下线筛积性函数$F(T)=\sum_{d\mid T}d\mu(d)$的部分：
首先对于一个质数$p$，$F(p)=\mu(p)+p\mu(p)=1-p$。
考虑$a$的最小质因子$p$，若$a,p$互质，则$F(ap)=F(a)F(p)$。
否则因为$F(p^k)$不管$k$是几（正整数），都有$F(p^k)=F(p)=1-p$，所以$F(ap)=F(\frac{a}{p^k})F(p^{k+1})=F(a)$。

单次询问复杂度$O(\sqrt n)$。还有两次数论分块的做法（$O(n)$的）。
还可以杜教筛=-=
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
