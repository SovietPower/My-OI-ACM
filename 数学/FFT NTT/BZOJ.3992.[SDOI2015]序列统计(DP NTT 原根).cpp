/*
1876kb	3684ms(怎么这么慢啊...)
$Description$
给定$n,m,x$和集合$S$。求$\prod_{i=1}^na_i\equiv x\ (mod\ m)$的方案数。其中$a_i\in S$。
$n\leq10^9，3\leq m\leq 8000且m是质数，1\leq x\leq m-1$。
$Solution$
令$f_{i,j}$表示当前选了$i$个数，乘积模$m$为$j$的方案数，$g_i=[i\in S]$。
转移就是，
$$f_{i,a*b\%m}=\sum f_{i-1,a}*g_b$$
每次转移是一样的，所以可以快速幂计算，即$f_{2i,a*b\%m}=\sum f_{i,a}*f_{i,b}$。
虽然把$n$优化到了$\log n$，但这样转移复杂度还是$O(m^2)$的。
我们发现，只要能把$a*b\%m$写成$(a+b)\%m$，就是一个循环卷积的形式了。
把乘法变成加法可以想到取对数，同样在模意义下可以用[离散对数](https://www.cnblogs.com/SovietPower/p/10044472.html)。
取$m$的一个原根$g$，$g,g^2,...,g^{m-1}$在模$m$意义下互不相同。所以我们可以用满足$g^A\equiv a\ (mod\ m)$的正整数$A$来替换掉$a$（即$a$模$m$的指标$I(a)$），它是唯一的。
那么$a*b\equiv g^A*g^B\equiv g^{A+B}\equiv g^{(A+B)\%\varphi(m)}\ (mod\ m)$。
所以转移就成了：
$$f_{i,(A+B)\%(m-1)}=\sum f_{i-1,A}*g_B$$
令$g_{A+B}=\sum f_{i-1,A}*g_B$，那么$f_{i,j\%(m-1)}=g_j+g_{j+m-1}$。
可以用$NTT$优化。
同样，每一次的转移还是一样的，依旧可以用多项式快速幂。
复杂度$O(m\log m\log n)$。
当然取$g^0,g^1,...,g^{m-2}$也行，因为多项式下标以$0$开始方便些。
这样如果集合里有$0$要特判忽略掉它。
因为是循环卷积所以每次快速幂乘的时候都需要把$f$求出来，也就是一定要再$NTT$回系数表示，不能一直用点值表示做。（是这样吧？）
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define G 3
#define invG 334845270
#define mod 1004535809
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define Mul(x,y) (1ll*x*y%mod)
typedef long long LL;
const int N=32500;

int inv,I[N],x[N],t[N],rev[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k,int p)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%p)
		if(k&1) t=1ll*t*x%p;
	return t;
}
int Get_root(int P)
{
	static int p[10005];
	int cnt=0,t=P-1;
	for(int i=2; i*i<=t; ++i)
		if(!(t%i))
		{
			p[++cnt]=i;
			while(!(t%i)) t/=i;
		}
	if(t>1) p[++cnt]=t;
	for(int x=2; ; ++x)
	{
		bool ok=1;
		for(int i=1; i<=cnt; ++i) if(FP(x,(P-1)/p[i],P)==1) {ok=0; break;}
		if(ok) return x;
	}
	return 1;
}
void Pre(int m)
{
	int g=Get_root(m);
	for(int i=0,pw=1; i<m-1; ++i) I[pw]=i, pw=1ll*pw*g%m;//g^i=pw -> I(pw)=i
}
void NTT(int *a,int lim,int opt)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1,Wn=FP(~opt?G:invG,(mod-1)/i,mod);
		for(int j=0; j<lim; j+=i)
			for(int k=j,w=1,t; k<j+mid; ++k,w=1ll*w*Wn%mod)
				a[k+mid]=a[k]-(t=1ll*a[k+mid]*w%mod)+mod, Mod(a[k+mid]),
				a[k]+=t, Mod(a[k]);
	}
	if(opt==-1) for(int i=0,inv=::inv; i<lim; ++i) a[i]=1ll*a[i]*inv%mod;
}
void Mult1(int *f,int n,int lim)//x*x可以少一次NTT啊 
{
	NTT(f,lim,1);
	for(int i=0; i<lim; ++i) f[i]=1ll*f[i]*f[i]%mod;
	NTT(f,lim,-1);
	for(int i=0; i<n; ++i) f[i]=f[i]+f[i+n], Mod(f[i]);//f[i+m-1]
	for(int i=n; i<lim; ++i) f[i]=0;//!
}
void Mult2(int *a,int *b,int *res,int n,int lim)
{
	static int f[N],g[N];
	memset(f,0,sizeof f), memset(g,0,sizeof g);
	memcpy(f,a,n<<2), memcpy(g,b,n<<2);
	NTT(f,lim,1), NTT(g,lim,1);
	for(int i=0; i<lim; ++i) f[i]=1ll*f[i]*g[i]%mod;
	NTT(f,lim,-1);
	for(int i=0; i<n; ++i) res[i]=f[i]+f[i+n], Mod(res[i]);//f[i+m-1] //要保证res的n项以外为0 
}

int main()
{
	static int x[N],res[N];
	int n=read(),m=read(),X=read(),S=read();
	Pre(m), --m;//0~m-1

	int lim=1,l=-1;
	while(lim<=m+m-2) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	inv=FP(lim,mod-2,mod);

	for(int i=1,s; i<=S; ++i) s=read(), s&&(++x[I[s]]);//++f[1][s]
	res[I[1]]=1;//f[0][1]=1
	for(int k=n; k; k>>=1,Mult1(x,m,lim))
		if(k&1) Mult2(res,x,res,m,lim);
	printf("%d\n",res[I[X]]);

	return 0;
}
