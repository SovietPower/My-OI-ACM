/*
11060kb	11548ms
https://www.cnblogs.com/SovietPower/p/10039339.html
$Description$
求n个点组成的所有简单无向图的所有点的度数k次方之和。
即求
$$n\cdot 2^{\frac{(n-2)(n-1)}{2}}\sum_{i=0}^{n-1}C_{n-1}^ii^k$$

$Solution$
对于单独一个点，我们枚举它的度数（有多少条边）来计算它的贡献：
$$\sum_{i=0}^{n-1}i^kC_{n-1}^i2^{\frac{(n-2)(n-1)}{2}}$$

每个点是一样的，所以
$$Ans=n\cdot 2^{\frac{(n-2)(n-1)}{2}}\sum_{i=0}^{n-1}C_{n-1}^ii^k$$

考虑如何计算$\sum_{i=0}^{n-1}C_{n-1}^ii^k$。
然后...dalao看到$i^k$就想起了第二类斯特林数：
> $S(n,m)$即在$m$个无区别盒子中放$n$个不同小球的方案数（要求盒子非空）。
$S(n,m)$的一个公式为
> $$S(n,m)=\frac{1}{m!}\sum_{k=0}^m(-1)^kC_m^k(m-k)^n$$
> 即利用容斥，枚举空盒子至少有多少个。因为盒子无序所以再除以$m!$。
而利用反演，或者是组合意义可以得到：
> $$m^n=\sum_{k=0}^mC_m^kS(n,k)k!$$
> 斯特林数中的盒子是无序的所以再乘个$k!$。
（$\sum$的上界是$m$是$n$都可以，看需要）

为了方便先令$n=n-1$。
我们把$m^n=\sum_{k=0}^mC_m^kS(n,k)k!$代进$Ans$的$\sum$里：
$$\sum_{i=0}^nC_n^ii^k=\sum_{i=0}^nC_n^i\sum_{j=0}^iC_i^j\cdot S(k,j)\cdot j!$$

然后，还是没法做就把$j$放到前面枚举试试：
$$\sum_{j=0}^nS(k,j)\cdot j!\cdot\sum_{i=j}^nC_n^iC_i^j$$

考虑一下$\sum_{i=j}^nC_n^iC_i^j$的组合意义，即从$n$个物品中选任意多个（至少$j$个），然后从它们中再选出$j$个。也就是从$n$个中选出$j$个后，其余$n-j$个任意选的方案数，即$C_n^j2^{n-j}$。
所以式子还可以化成：
$$\sum_{j=0}^nS(k,j)\cdot j!\cdot C_n^j\cdot 2^{n-j}$$

后面的三项$j!\cdot C_n^j\cdot 2^{n-j}$（$A_n^j\cdot 2^{n-j
}$）都可以直接算，所以我们只要算$S(k,j)$就可以了。同[BZOJ4555](https://www.cnblogs.com/SovietPower/p/9715954.html)，把上面的
$$S(n,m)=\frac{1}{m!}\sum_{k=0}^m(-1)^kC_m^k(m-k)^n$$
展开成
$$S(n,m)=\sum_{k=0}^m\frac{(-1)^k}{k!}\cdot\frac{(m-k)^n}{(m-k)!}$$

是卷积形式，就可以用$NTT$计算了。（$n<k$时$S(n,k)=0$，所以$j$枚举到$\min(n,k)$就好了）
*/
#include <cstdio>
#include <algorithm>
#define G 3
#define invG 332748118
#define inv2 499122177
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define Mul(x,y) (1ll*(x)*(y)%mod)
typedef long long LL;
const int N=(1<<19)+5;

int fac[N],ifac[N],f[N],g[N],rev[N];

inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=Mul(x,x))
		if(k&1) t=Mul(t,x);
	return t;
}
void NTT(int *a,int lim,int opt)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1,Wn=FP(~opt?G:invG,(mod-1)/i);
		for(int j=0; j<lim; j+=i)
			for(int k=j,w=1,t; k<j+mid; ++k,w=Mul(w,Wn))
				a[k+mid]=a[k]-(t=Mul(w,a[k+mid]))+mod, Mod(a[k+mid]),
				a[k]+=t, Mod(a[k]);
	}
	if(opt==-1) for(int i=0,inv=FP(lim,mod-2); i<lim; ++i) a[i]=Mul(a[i],inv);
}

int main()
{
	int n,K; scanf("%d%d",&n,&K); --n;//!
	int m=std::min(n,K);
	fac[0]=fac[1]=1, ifac[0]=ifac[1]=1;
	for(int i=2; i<=m; ++i) fac[i]=Mul(fac[i-1],i);
	ifac[m]=FP(fac[m],mod-2);
	for(int i=m; i; --i) ifac[i-1]=Mul(ifac[i],i);

	for(int i=0; i<=m; ++i) f[i]=i&1?mod-ifac[i]:ifac[i], g[i]=Mul(FP(i,K),ifac[i]);//x^K/x! (n=K)
	int lim=1,l=-1;
	while(lim<=m+m) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	NTT(f,lim,1), NTT(g,lim,1);
	for(int i=0; i<lim; ++i) f[i]=Mul(f[i],g[i]);
	NTT(f,lim,-1);

	LL ans=0; int pw2=FP(2,n),A=1;//2^{n-i} A(n,i)
	for(int i=0; i<=m; ++i) ans+=1ll*f[i]*A%mod*pw2%mod, pw2=Mul(pw2,inv2), A=Mul(A,n-i);
	printf("%lld\n",ans%mod*(n+1)%mod*FP(2,(1ll*n*(n-1)>>1ll)%(mod-1))%mod);

	return 0;
}
