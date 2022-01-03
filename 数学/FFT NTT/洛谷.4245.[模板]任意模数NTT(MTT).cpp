/*
1094ms	26.14MB
$FFT$的问题在于精度，我们可以压缩值域。
令$m=\lceil\sqrt p\rceil,\ A_i=a\times m+b,\ B_i=c\times m+d$，那么$h_{i+j}=\sum(a_im+b_i)(c_jm+d_j)=\sum a_ic_jm^2+(a_id_j+b_ic_j)m+b_id_j$，分别求出四项（中间两项放一块算），就只需要$7$次$DFT$。
为了方便可以令$m=2^{15}=32768$。
这样$FFT$后的最大结果是$10^5\times2^{30}=10^{14}$，注意取模。

注意`std::sin`的精度比`sin`高！因为值域依旧很大所以必须要注意这个，还要开`long double`。
还有个挺重要的优化是预处理单位根，预处理$lim$次单位根的$0\sim lim-1$次方，用$\omega_i^k$时就是$\omega_{lim}^{k\times\frac{lim}{i}}$（怎么都预处理的$2lim$次单位根啊...）。
注意预处理的时候不要像$FFT$里那样每次`w=w*Wn`，而是对每个单位根直接用欧拉公式算，这样精度误差会小非常多，就可以把`long double`替换成`double`了...（然后就可以快很多很多）
（嗯...误差问题都出在求单位根上了...）

现在$7$次$DFT$已经挺快了...还可以优化，可以看毛啸的论文。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
typedef long double ld;
//#define double long double
const int N=(1<<18)+3;
const double PI=acos(-1);

int rev[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Complex
{
	double x,y;
	Complex(double x=0,double y=0):x(x),y(y) {}
	inline Complex operator +(const Complex &a)const {return Complex(x+a.x, y+a.y);}
	inline Complex operator -(const Complex &a)const {return Complex(x-a.x, y-a.y);}
	inline Complex operator *(const Complex &a)const {return Complex(x*a.x-y*a.y, y*a.x+x*a.y);}
}A[N],B[N],C[N],D[N],W[N];

inline int read()
{
	int now=0; register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void FFT(Complex *a,const int lim,const int opt)
{
	static Complex w[N];
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		if(~opt) for(int k=0,t=lim/i; k<mid; ++k) w[k]=W[k*t];
		else for(int k=0,t=lim/i; k<mid; ++k) w[k]=Complex(W[k*t].x,-W[k*t].y);
		for(int j=0; j<lim; j+=i)
		{
			Complex t;
			for(int k=j; k<j+mid; ++k)
				a[k+mid]=a[k]-(t=w[k-j]*a[k+mid]), a[k]=a[k]+t;
		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}

int main()
{
	const int n=read(),m=read(),P=read();
	for(int i=0,t; i<=n; ++i) t=read(),A[i].x=t>>15,B[i].x=t&32767;
	for(int i=0,t; i<=m; ++i) t=read(),C[i].x=t>>15,D[i].x=t&32767;

	int lim=1,l=-1; while(lim<=n+m) lim<<=1,++l;
	for(int i=0; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	for(int i=0,t=lim>>1; i<lim; ++i) W[i]=Complex(std::cos(i*PI/t),std::sin(i*PI/t));
//	const Complex Wn(std::cos(2.0*PI/lim),std::sin(2.0*PI/lim)); Complex w(1,0);
//	for(int i=0; i<lim; ++i) W[i]=w, w=w*Wn;//精度巨差 

	FFT(A,lim,1), FFT(B,lim,1), FFT(C,lim,1), FFT(D,lim,1);
	for(int i=0; i<lim; ++i)
	{
		const Complex a=A[i],b=B[i],c=C[i],d=D[i];
		A[i]=a*c, B[i]=a*d+b*c, D[i]=b*d;
	}
	FFT(A,lim,-1), FFT(B,lim,-1), FFT(D,lim,-1);
	for(int i=0,t=n+m; i<=t; ++i)
	{
		LL res=((LL(A[i].x+0.5))%P<<30)+((LL(B[i].x+0.5))%P<<15)+(LL(D[i].x+0.5));
		printf("%d ",(int)(res%P));
	}

	return 0;
}
