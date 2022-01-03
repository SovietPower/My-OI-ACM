/*
12340kb	1524ms
$Description$
����һ��ֻ��$a,b$���ַ��������������������и�����������ָ�����в�������һ�Σ�����Ҫ���ַ���λ�ö�����ĳ���Գ���Գƣ���
$n\leq10^5$��
$Solution$
�����������ƱȽ��鷳���������������и���������$manacher$��������Կ���ȥ��������������ơ�
���Գ�����$x$���������������߹���$f(x)$�ԶԳƵ��ַ�����ô��$x$Ϊ���ĵķǿջ�������������$2^{f(x)}-1$������Ϊ$x$�ǿ���ȡ$\frac k2$�ģ��ַ�֮���λ�����Գ��ᣩ����$2x$��ʾ�Գ���Ϊ$x$���𰸾���$\sum_{i=2}^{2n}(2^{f(i)}-1)$��
���������$f(x)$��
һ�Թ���$x$�ԳƵ��ַ�����������$s_{x-i}=s_{x+i}$����Ϊ$x$����ȡ$\frac12$���������ֱ�ʾ����$s_{i}=s_{2x-i}$��
��ô$f(x)=\frac{\sum_{i=1}^{2x-1} [s_{i}=s_{2x-i}]+1}{2}$��ÿ�ԶԳ��ַ��������Σ����Լ������Լ��ԳƵ��ַ�����һ�Σ����Լ�$1$�ٳ���$2$�����Ǹ�$\sum$���Ǿ������ʽ��
ö��һ���ַ�$c$����$F_i=[s_i=c]$����ô$f(x)=\frac{\sum_{i=1}^{2x-1}F_i*F_{2x-i}+1}{2}$��
����ö��һ���ַ�$a,b$Ȼ��$FFT$���������Ϳ������$\sum_{i=1}^{2x-1}F_i*F_{2x-i}$�ˡ�
���μ���$\sum$��ʱ���м���Բ�$IDFT$��
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
