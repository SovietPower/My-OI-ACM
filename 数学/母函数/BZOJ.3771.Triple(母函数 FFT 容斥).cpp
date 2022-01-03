//7476kb	852ms
//www.cnblogs.com/SovietPower/p/9161576.html
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=(1<<17)+5;//131072
const double PI=acos(-1);

int n,rev[N];
struct Complex
{
	double x,y;
	Complex() {}
	Complex(double x,double y):x(x),y(y) {}
	Complex operator +(const Complex &a) {return Complex(x+a.x, y+a.y);}//有点纠结这换不换行。。
	Complex operator -(const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator *(const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
	Complex operator *(const double &a) {return Complex(x*a, y*a);}
	Complex operator /(const double &a) {return Complex(x/a, y/a);}
}A[N],B[N],C[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void FFT(Complex *a,int lim,int type)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		Complex Wn(cos(PI/mid),type*sin(PI/mid)),t;//2.0*PI/i
//		W[0]=Complex(1,0);
//		for(int j=1; j<mid; ++j) W[j]=W[j-1]*Wn;//这两行出俩错误→_→ 
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0);//不预处理更快。。是范围小的原因吗。。
			for(int k=0; k<mid; ++k,w=w*Wn)
				a[j+k+mid]=a[j+k]-(t=a[j+k+mid]*w),
				a[j+k]=a[j+k]+t;
		}
	}
	if(type==-1)
		for(int i=0; i<lim; ++i) a[i].x/=lim;
}

int main()
{
	n=read(); int mx=0;
	for(int v,i=1; i<=n; ++i)
		mx=std::max(mx,v=read()), A[v].x=B[2*v].x=C[3*v].x=1.0;
	int lim=1, L=0;
	while(lim<=3*mx) lim<<=1, ++L;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<L-1);

	FFT(A,lim,1), FFT(B,lim,1), FFT(C,lim,1);
	for(int i=0; i<lim; ++i)
		A[i]=A[i]+(A[i]*A[i]-B[i])*0.5+(A[i]*A[i]*A[i]-A[i]*B[i]*3.0+C[i]*2.0)/6.0;
	FFT(A,lim,-1);
	for(int i=0; i<lim; ++i)
		if((int)(A[i].x+0.5)) printf("%d %d\n",i,(int)(A[i].x+0.5));//这题需要longlong。。

	return 0;
}
