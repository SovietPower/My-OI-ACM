#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=132000;//2^{17}=132000 > 60000*2
const double PI=acos(-1);

int n,Ans[N];
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
}A[N],B[N];

inline void read(Complex *a){
	int t=0; char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);a[t++].x=(double)(c-'0'),c=gc());
}
void FFT(Complex *a,int lim,int opt)
{
	for(int j=0,i=0; i<lim; ++i)
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
	scanf("%d",&n);
	read(A), read(B);
	std::reverse(A,A+n), std::reverse(B,B+n);
	n<<=1; int lim=1;
	while(lim <= n) lim<<=1;
	FFT(A,lim,1), FFT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i];
	FFT(A,lim,-1);
	for(int i=0; i<=n; ++i) Ans[i]=(int)(A[i].x/lim+0.5);
	for(int i=0; i<n; ++i) Ans[i+1]+=Ans[i]/10, Ans[i]%=10;
//	for(int i=0; i<lim; ++i) Ans[i]=int(A[i].x/lim+0.5);
//	for(int i=0; i<lim; ++i) Ans[i+1]+=Ans[i]/10, Ans[i]%=10;
//	n=lim;
	while(!Ans[n] && n) --n;
	while(~n) putchar(Ans[n--]+'0');

	return 0;
}
