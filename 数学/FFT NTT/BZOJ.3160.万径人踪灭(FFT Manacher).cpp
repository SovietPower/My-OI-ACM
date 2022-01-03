/*
12340kb	1524ms
$Description$
给定一个只含$a,b$的字符串，求不连续回文子序列个数（不连续指子序列不是连续一段，回文要求字符和位置都关于某条对称轴对称）。
$n\leq10^5$。
$Solution$
不连续的限制比较麻烦。连续回文子序列个数可以用$manacher$求出，所以可以去掉不连续这个限制。
若对称轴在$x$处，假设它的两边共有$f(x)$对对称的字符，那么以$x$为中心的非空回文子序列数有$2^{f(x)}-1$个。因为$x$是可以取$\frac k2$的（字符之间的位置做对称轴），用$2x$表示对称轴为$x$，答案就是$\sum_{i=2}^{2n}(2^{f(i)}-1)$。
考虑如何求$f(x)$。
一对关于$x$对称的字符，就是满足$s_{x-i}=s_{x+i}$。因为$x$可以取$\frac12$，不妨换种表示，即$s_{i}=s_{2x-i}$。
那么$f(x)=\frac{\sum_{i=1}^{2x-1} [s_{i}=s_{2x-i}]+1}{2}$（每对对称字符算了两次，而自己关于自己对称的字符算了一次，所以加$1$再除以$2$）。那个$\sum$就是卷积的形式。
枚举一种字符$c$，令$F_i=[s_i=c]$，那么$f(x)=\frac{\sum_{i=1}^{2x-1}F_i*F_{2x-i}+1}{2}$。
所以枚举一下字符$a,b$然后$FFT$，加起来就可以求出$\sum_{i=1}^{2x-1}F_i*F_{2x-i}$了。
两次计算$\sum$的时候中间可以不$IDFT$。
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=(1<<18)+7;
const double PI=acos(-1);

int pw[N],rev[N];
char s[N];
struct Complex
{
	double x,y;
	Complex(double x=0,double y=0):x(x),y(y) {}
	Complex operator +(const Complex &a)const {return Complex(x+a.x, y+a.y);}
	Complex operator -(const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator *(const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[N],f[N];

void FFT(Complex *a,int lim,int opt)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1; Complex Wn(cos(PI/mid),opt*sin(PI/mid));
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0),t;
			for(int k=j; k<j+mid; ++k,w=w*Wn)
				a[k+mid]=a[k]-(t=a[k+mid]*w), a[k]=a[k]+t;
		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}
void Solve(const char c,int n,int m,int lim)
{
	for(int i=0; i<lim; ++i) A[i]=Complex(0,0);
	for(int i=1; i<=n; ++i) A[i]=Complex(s[i]==c,0);
	FFT(A,lim,1);
	for(int i=0; i<lim; ++i) f[i]=f[i]+A[i]*A[i];//0~lim!
//	for(int i=0; i<lim; ++i) A[i]=A[i]*A[i];
//	FFT(A,lim,-1);
//	for(int i=1; i<=m; ++i) f[i]+=(int)(A[i].x+0.5);
}
int Manacher(int n)
{
	static int ext[N];
	s[0]='$', s[n+n+1]='#', s[n+n+2]='%';
	for(int i=n; i; --i) s[i<<1]=s[i], s[(i<<1)-1]='#';
	n<<=1;
	for(int i=1,mx=0,p; i<=n; ++i)
	{
		ext[i]=mx>i?std::min(mx-i,ext[2*p-i]):1;
		while(s[i-ext[i]]==s[i+ext[i]]) ++ext[i];
		if(i+ext[i]>mx) mx=i+ext[i], p=i;
	}
	LL ans=0;
	for(int i=1; i<=n; ++i) ans+=ext[i]>>1;
	return ans%mod;
}

int main()
{
	scanf("%s",s+1); int n=strlen(s+1),m=n<<1,lim=1,l=-1;
	while(lim<=m) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	Solve('a',n,m,lim), Solve('b',n,m,lim);
	FFT(f,lim,-1);
	LL ans=0; pw[0]=1;
	for(int i=1; i<=m; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);
	for(int i=1; i<=m; ++i) ans+=pw[(int)(f[i].x+1.5)>>1]-1;
//	for(int i=1; i<=m; ++i) f[i]=f[i]+1>>1, ans+=pw[f[i]]-1;
	printf("%lld\n",(ans%mod-Manacher(n)+mod)%mod);

	return 0;
}
