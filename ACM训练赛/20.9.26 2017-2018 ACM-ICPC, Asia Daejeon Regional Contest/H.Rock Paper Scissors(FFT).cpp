/*
202ms	10600KB
就是求字符串匹配的最大长度。
FFT，类似[这道题](https://www.cnblogs.com/SovietPower/p/10041397.html)，不过更简单。
分别枚举三个字符，每次将该字符在S和T中的位置设为1，两个多项式相乘即可得到这个字符在任意位置的匹配个数。
*/
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=(1<<18)+5;
const double PI=acos(-1);

int rev[N],ans[N];
char S[N],T[N];
struct Complex
{
	double x,y;
	Complex(double x=0,double y=0):x(x),y(y) {}
	Complex operator +(const Complex &a) {return Complex(x+a.x, y+a.y);}
	Complex operator -(const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator *(const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[N],B[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now*f;
}
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

int main()
{
	int n=read(),m=read();
	scanf("%s",S), scanf("%s",T);
	for(int i=0; i<m; ++i) T[i]=(T[i]=='R')?'S':T[i]=='P'?'R':'P';
	std::reverse(T,T+m);
	for(int i=m; i<n; ++i) T[i]='A';

	int lim=1,l=-1;
	while(lim<=n+m-2) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);

	for(int i=0; i<n; ++i) A[i]=Complex(S[i]=='P'?1:0,0),B[i]=Complex(T[i]=='P'?1:0,0);
	for(int i=n; i<lim; ++i) A[i]=Complex(0,0),B[i]=Complex(0,0);
	FFT(A,lim,1), FFT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i];
	FFT(A,lim,-1);
	for(int i=0; i<n; ++i) ans[i]+=int(A[m+i-1].x+0.5);

	for(int i=0; i<n; ++i) A[i]=Complex(S[i]=='R'?1:0,0),B[i]=Complex(T[i]=='R'?1:0,0);
	for(int i=n; i<lim; ++i) A[i]=Complex(0,0),B[i]=Complex(0,0);
	FFT(A,lim,1), FFT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i];
	FFT(A,lim,-1);
	for(int i=0; i<n; ++i) ans[i]+=int(A[m+i-1].x+0.5);

	for(int i=0; i<n; ++i) A[i]=Complex(S[i]=='S'?1:0,0),B[i]=Complex(T[i]=='S'?1:0,0);
	for(int i=n; i<lim; ++i) A[i]=Complex(0,0),B[i]=Complex(0,0);
	FFT(A,lim,1), FFT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i];
	FFT(A,lim,-1);
	for(int i=0; i<n; ++i) ans[i]+=int(A[m+i-1].x+0.5);

	int res=0;
	for(int i=0; i<n; ++i) res=std::max(res,ans[i]);
	printf("%d\n",res);

	return 0;
}
