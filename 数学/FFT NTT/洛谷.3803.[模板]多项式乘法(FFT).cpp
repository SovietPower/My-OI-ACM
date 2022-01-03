#include <cmath>
#include <cctype>
#include <cstdio>
#include <algorithm>
#define gc() getchar()
const int N=1e6+5;
const double PI=acos(-1);

int n,m;
struct Complex
{
	double x,y;
	Complex(double xx=0,double yy=0) {x=xx, y=yy;}
	Complex operator + (const Complex &a) {return Complex(x+a.x, y+a.y);}
	Complex operator - (const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator * (const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[N*3],B[N*3];//size!

void Fast_Fourier_Transform(Complex *a,int lim,int opt)
{
	for(int j=0,i=0; i<lim; ++i)
	{
		if(i>j) std::swap(a[i],a[j]);
		for(int l=lim>>1; (j^=l)<l; l>>=1);
	}
	for(int i=2; i<=lim; i<<=1)//最后等于lim即整个序列的合并 
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
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(),m=read();
	for(int i=0; i<=n; ++i) A[i].x=(double)read();//scanf("%lf",&A[i].x);
	for(int i=0; i<=m; ++i) B[i].x=(double)read();//scanf("%lf",&B[i].x);
	int lim=1;
	while(lim<=n+m) lim<<=1;
	Fast_Fourier_Transform(A,lim,1);
	Fast_Fourier_Transform(B,lim,1);
	for(int i=0; i<=lim; ++i) A[i]=A[i]*B[i];//size!
	Fast_Fourier_Transform(A,lim,-1);
	for(int i=0; i<=n+m; ++i) printf("%d ",(int)(A[i].x/lim+0.5));
	
	return 0;
}
