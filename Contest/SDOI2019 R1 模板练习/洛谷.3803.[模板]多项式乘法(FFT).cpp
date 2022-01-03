/*
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=(1<<21)+5;
const double PI=acos(-1);

int rev[N];
struct Complex
{
	double x,y;
	Complex(double x=0,double y=0):x(x),y(y) {}
	inline Complex operator +(const Complex &a)const {return Complex(x+a.x, y+a.y);}
	inline Complex operator -(const Complex &a)const {return Complex(x-a.x, y-a.y);}
	inline Complex operator *(const Complex &a)const {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}f[N],g[N],W[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void FFT(Complex *a,int lim,int opt)
{
	static Complex w[N];
	for(int i=0; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		Complex Wn(cos(PI/mid),opt*sin(PI/mid));
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0),t;
			for(int k=j; k<j+mid; ++k,w=w*Wn)
				a[k+mid]=a[k]-(t=w*a[k+mid]), a[k]=a[k]+t;
		}
//		if(~opt) for(int k=0,t=lim/i; k<mid; ++k) w[k]=W[k*t];
//		else for(int k=0,t=lim/i; k<mid; ++k) w[k]=Complex(W[k*t].x,-W[k*t].y);
//		for(int j=0; j<lim; j+=i)
//		{
//			Complex t;
//			for(int k=j; k<j+mid; ++k)
//				a[k+mid]=a[k]-(t=w[k-j]*a[k+mid]), a[k]=a[k]+t;
//		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}

int main()
{
	int n=read()+1,m=read()+1;
	for(int i=0; i<n; ++i) f[i].x=read();
	for(int i=0; i<m; ++i) g[i].x=read();
	int lim=1,bit=-1;
	while(lim<=n+m) lim<<=1,++bit;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<bit);
//	for(int i=0,t=lim>>1; i<lim; ++i) W[i]=Complex(cos(i*PI/t),sin(i*PI/t));

	FFT(f,lim,1), FFT(g,lim,1);
	for(int i=0; i<lim; ++i) f[i]=f[i]*g[i];
	FFT(f,lim,-1);
	for(int i=0,l=n+m-2; i<=l; ++i) printf("%d ",int(f[i].x+0.5));

	return 0;
}
