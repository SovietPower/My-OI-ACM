//将乘数拆成 a_0*10^n + a_1*10^(n-1) + ... + a_n-1的形式 
//可以发现多项式乘法就模拟了竖式乘法 所以用FFT即可 注意处理进位 
//n位*n位最多就只有2n位了 
//论putchar的速度。。还是快的 
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=6e4+5;
const double PI=acos(-1);

int n,ans[N<<1];
struct Complex
{
	double x,y;
	Complex(double xx=0,double yy=0) {x=xx, y=yy;}
	Complex operator + (const Complex &a) {return Complex(x+a.x, y+a.y);}
	Complex operator - (const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator * (const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[N*3],B[N*3];

inline void read(Complex *a)
{
	int cnt=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);a[cnt++].x=(double)(c-'0'),c=gc());
}
void Fast_Fourier_Transform(Complex *a,int lim,int opt)
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
	int lim=1;
	while(lim <= n<<1) lim<<=1;
	Fast_Fourier_Transform(A,lim,1);
	Fast_Fourier_Transform(B,lim,1);
	for(int i=0; i<=lim; ++i) A[i]=A[i]*B[i];
	Fast_Fourier_Transform(A,lim,-1);
	int t=n<<1;
	for(int i=0; i<=t; ++i) ans[i]=(int)(A[i].x/lim+0.5);
	for(int i=0; i<t; ++i) ans[i+1]+=ans[i]/10, ans[i]%=10;
	while(!ans[t] && t) --t;
	while(~t) putchar(ans[t--]+'0');

	return 0;
}
