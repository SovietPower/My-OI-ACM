//7988kb	2340ms
//https://www.cnblogs.com/SovietPower/p/9715954.html
/*
$Description$
求
$$\sum_{i=0}^n\sum_{j=0}^iS(i,j)\times 2^j\times j!\mod 998244353$$

其中$S(i,j)$为第二类斯特林数（$S(n,m)$即在$m$个无区别盒子中放$n$个不同小球的方案数）。
$Solution$
注意到$i<j$时，$S(i,j)=0$，所以$j$的上界可以到$n$。
$$\begin{aligned}\sum_{i=0}^n\sum_{j=0}^iS(i,j)\times 2^j\times j!&=\sum_{i=0}^n\sum_{j=0}^nS(i,j)\times 2^j\times j!\\&=\sum_{j=0}^n2^j\cdot j!\cdot\sum_{i=0}^nS(i,j)\tag !\end{aligned}$$

$S(n,m)$的一个公式为
$$S(n,m)=\frac{1}{m!}\sum_{k=0}^m(-1)^kC(m,k)(m-k)^n$$

即利用容斥，枚举强制为空的盒子有多少个（空盒子至少有多少个）。因为盒子无序所以再除以$m!$。然后可以化简。
$$\begin{aligned}S(n,m)&=\frac{1}{m!}\sum_{k=0}^m(-1)^kC(m,k)(m-k)^n\\&=\sum_{k=0}^m(-1)^k\frac{1}{k!(m-k)!}(m-k)^n\\&=\sum_{k=1}^m\frac{(-1)^k}{k!}\cdot\frac{(m-k)^n}{(m-k)!}\end{aligned}$$

注意到这是个卷积形式，所以我们可以$O(n\log n)$计算出$S(n,i)$。
当然本题还是把上式代回去。
$$\begin{aligned}\sum_{j=0}^n2^j\cdot j!\cdot\sum_{i=0}^nS(i,j)&=\sum_{j=0}^n2^j\cdot j!\cdot\sum_{i=0}^n\sum_{k=0}^j\frac{(-1)^k}{k!}\cdot\frac{(j-k)^i}{(j-k)!}\\&=\sum_{j=0}^n2^j\cdot j!\cdot\sum_{k=0}^j\frac{(-1)^k}{k!}\cdot\frac{\sum_{i=0}^n(j-k)^i}{(j-k)!}\tag !\end{aligned}$$

注意到后面还是个卷积形式，令$f(x)=\frac{(-1)^x}{x!},g(x)=\frac{\sum_{i=0}^nx^i}{x!}$。
设$S_n=\sum_{i=0}^nx^i$，则$xS_n=\sum_{i=1}^{n+1}x^i$，得$S_n=\frac{x^{n+1}-1}{x-1}$，即$g(x)=\frac{x^{n+1}-1}{(x-1)x!}\tag !$。特殊的，令$g(0)=1,g(1)=n+1$。
这样$f,g$都可以递推。
然后
$$Ans=\sum_{j=0}^n2^j\cdot j!\cdot(f*g)(j)$$

NTT就行了。
*/
#include <cstdio>
#include <algorithm>
#define mod 998244353
#define G 3
#define invG 332748118
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=(1<<18)+5;

int pw[N],fac[N],ifac[N],inv[N],rev[N],f[N],g[N];

inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
void NTT(int *a,int lim,int type)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		int Wn=FP(~type?G:invG,(mod-1)/i);
		for(int j=0; j<lim; j+=i)
		{
			int w=1,t;
			for(int k=0; k<mid; ++k,w=1ll*w*Wn%mod)
				a[j+k+mid]=(a[j+k]-(t=1ll*a[j+k+mid]*w%mod)+mod), Mod(a[j+k+mid]),
				a[j+k]+=t, Mod(a[j+k]);
		}
	}
	if(type==-1) for(int i=0,inv=FP(lim,mod-2); i<lim; ++i) a[i]=1ll*a[i]*inv%mod;
}

int main()
{
	int n; scanf("%d",&n);

	pw[0]=fac[0]=1;
	for(int i=1; i<=n; ++i)
		pw[i]=pw[i-1]<<1, Mod(pw[i]), fac[i]=1ll*fac[i-1]*i%mod;

	ifac[n]=FP(fac[n],mod-2);
	for(int i=n-1; ~i; --i) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;

	inv[1]=1;
	for(int i=2; i<=n; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;

	f[0]=g[0]=1, f[1]=mod-1/*not -1...*/, g[1]=n+1;
	for(int i=2; i<=n; ++i)
		f[i]=i&1?(mod-ifac[i]):ifac[i],
		g[i]=1ll*(FP(i,n+1)-1)*inv[i-1]%mod*ifac[i]%mod;//FP(..,..)!=0

	int len=-1,lim=1; while(lim<=n<<1) lim<<=1,++len;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<len);
	NTT(f,lim,1), NTT(g,lim,1);
	for(int i=0; i<lim; ++i) f[i]=1ll*f[i]*g[i]%mod;
	NTT(f,lim,-1);

	LL ans=0;
	for(int i=0; i<=n; ++i) ans+=1ll*pw[i]*fac[i]%mod*f[i]%mod;
	printf("%lld\n",ans%mod);

	return 0;
}
