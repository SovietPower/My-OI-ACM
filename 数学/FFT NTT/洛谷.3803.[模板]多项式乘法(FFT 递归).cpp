#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#define gc() getchar()
const int N=2e6+5;
const double PI=acos(-1.0);

int n,m;
struct Complex
{
	double x,y;
	Complex(double xx=0,double yy=0) {x=xx, y=yy;}
	Complex operator + (const Complex &a) {return Complex(x+a.x, y+a.y);}
	Complex operator - (const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator * (const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[N],B[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void Fast_Fourier_Transform(Complex *a,int lim,int type)
{
	if(lim==1) return;
	Complex a1[lim>>1],a2[lim>>1];//±¬Õ» 
	for(int i=0; i<lim; i+=2)
		a1[i>>1]=a[i], a2[i>>1]=a[i+1];
	Fast_Fourier_Transform(a1,lim>>1,type),
	Fast_Fourier_Transform(a2,lim>>1,type);
	Complex Wn(cos(2.0*PI/lim),type*sin(2.0*PI/lim)),w(1,0),t;//Wn:µ¥Î»¸ù w:ÃÝ
	for(int i=0; i<(lim>>1); ++i,w=w*Wn)
		a[i]=a1[i]+(t=w*a2[i]),
		a[i+(lim>>1)]=a1[i]-t;
}

int main()
{
	n=read(),m=read();
	for(int i=0; i<=n; ++i) A[i].x=read();
	for(int i=0; i<=m; ++i) B[i].x=read();
	int lim=1;
	while(lim<=n+m) lim<<=1;
	Fast_Fourier_Transform(A,lim,1);
	Fast_Fourier_Transform(B,lim,1);
	for(int i=0; i<=lim; ++i) A[i]=A[i]*B[i];
	Fast_Fourier_Transform(A,lim,-1);
	for(int i=0; i<=n+m; ++i) printf("%d ",(int)(A[i].x/lim+0.5));

	return 0;
}
