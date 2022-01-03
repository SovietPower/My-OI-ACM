//13148kb	1544ms
//http://www.cnblogs.com/SovietPower/p/8989392.html
/*
$Descripiton$
　　给定$A[\ ],B[\ ]$，求
$$C[k]=\sum_{i=k}^{n-1}A[i]*B[i-k]\ (0\leq k<n)$$
$Solution$
　　(先令$n=n-1$)首先往卷积上想。。
　　$i$与$i-k$的差值是一定的，但是卷积的形式是
$$C[k]=\sum_{i=1}^k A[i]*B[k-i]$$
　　即$i$与$k-i$的和是一定的。
　　于是考虑把一个数组反转一下，这里把$B[\ ]$反转，那么
$$C[k]=\sum_{i=k}^n A[i]*B[n+k-i]$$
　　这样$i$与$n+k-i$的和就是一定的了，为$n+k$，于是令
$$D[n+k]=\sum_{i=k}^n A[i]*B[n+k-i]$$
　　这样就可以$FFT$求$D[\ ]$了。
$$D[n+k]=\sum_{i=0}^{n+k}A[i]*B[n+k-i]$$
　　$i=0\sim k-1$和$i=n+1\sim n+k$时，要么$A[i]=0$要么$B[i]=0$，没有影响。
　　所以最后的$C[k]=D[n+k]$。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=263000;//2^{18}=262144 > 2*1e5
const double PI=acos(-1);

int n;
struct Complex
{
	double x,y;
	Complex() {}
	Complex(double x,double y):x(x),y(y) {}
	Complex operator + (const Complex &a)const{
		return Complex(x+a.x, y+a.y);
	}
	Complex operator - (const Complex &a)const{
		return Complex(x-a.x, y-a.y);
	}
	Complex operator * (const Complex &a)const{
		return Complex(x*a.x-y*a.y, x*a.y+y*a.x);
	}
}A[N],B[N],D[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void FFT(Complex *a,int lim,int opt)
{
	for(int i=0,j=0; i<lim; ++i)
	{
		if(i>j) std::swap(a[i],a[j]);
		for(int l=lim>>1; (j^=l)<l; l>>=1);
	}
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		Complex Wn(cos(2.0*PI/i),opt*sin(2.0*PI/i)),t;
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0);
			for(int k=0; k<mid; ++k,w=w*Wn)
				a[j+mid+k]=a[j+k]-(t=w*a[j+mid+k]),
				a[j+k]=a[j+k]+t;
		}
	}
}

int main()
{
	n=read()-1;
	for(int i=0; i<=n; ++i) A[i].x=read(),B[n-i].x=read();
	int lim=1;
	while(lim <= n<<1) lim<<=1;
	FFT(A,lim,1), FFT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i];
	FFT(A,lim,-1);
	for(int i=0; i<=n; ++i) printf("%d\n",(int)(A[i+n].x/lim+0.5));

	return 0;
}
