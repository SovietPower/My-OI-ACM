//15204kb	3140ms
//http://www.cnblogs.com/SovietPower/p/8991435.html
/*
$Descripiton$
　　给出$q[\ ]$，
$$F[j]=\sum_{i<j}\frac{q_iq_j}{(i-j)^2}-\sum_{i>j}\frac{q_iq_j}{(i-j)^2}$$
　　令$E_i=\frac{F_i}{q_i}$，求所有$E[i]$。
$Solution$
　　（下标从0开始，$n=n-1$）可以把$q_j$约去，即
$$E_j=\sum_{i=0}^{j-1}\frac{q_i}{(i-j)^2}-\sum_{i=j+1}^n\frac{q_i}{(i-j)^2}$$
　　令$f[i]=q[i]，g[i]=\frac{1}{i^2}$，规定$g[0]=0$，那么
$$E_j=\sum_{i=0}^{j-1}f[i]*g[j-i]-\sum_{i=j+1}^nf[i]*g[j-i]$$
　　（注意是个平方）
　　左边$\sum_{i=0}^{j-1}f[i]*g[j-i]=\sum_{i=0}^{j}f[i]*g[j-i]$就是卷积的形式，可以直接算。
　　右边
$$  \begin{aligned}
    \sum_{i=j+1}^nf[i]*g[j-i]&=\sum_{i=j}^nf[i]*g[j-i]\\
                             &=\sum_{i=0}^{n-j}f[i+j]*g[i]
    \end{aligned}
$$
　　反转$f[\ ]$，令$h[n-j-i]=f[i+j]$，那么
$$\sum_{i=0}^{n-j}f[i+j]*g[i]=\sum_{i=0}^{n-j}h[n-j-i]*g[i]$$
　　令$X_{n-j}=\sum_{i=0}^{n-j}h[n-j-i]*g[i]$，也用FFT计算就可以了。
　　最后$E_j=\sum_{i=0}^{j-1}f[i]*g[j-i]-X_{n-j}$。
*/
#include <cmath>
#include <cstdio>
#include <algorithm>
const int N=263000;//2^{18}=262144 > 2*1e5
const double PI=acos(-1);

int n;
double q[N];
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
}f[N],g[N],h[N];

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
		Complex Wn(cos(PI/mid),opt*sin(PI/mid)),t;
//		Complex Wn(cos(2.0*PI/i),opt*sin(2.0*PI/i)),t;
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0);
			for(int k=0; k<mid; ++k,w=w*Wn)
				a[j+mid+k]=a[j+k]-(t=w*a[j+mid+k]),
				a[j+k]=a[j+k]+t;
		}
	}
	if(opt==-1)
		for(int i=0; i<lim; ++i) a[i].x/=lim;
}

int main()
{
	scanf("%d",&n), --n;
	int lim=1;
	while(lim <= n<<1) lim<<=1;
	for(int i=0; i<=n; ++i) scanf("%lf",&q[i]);

	for(int i=0; i<=n; ++i) f[i]=Complex(q[i],0);
	for(int i=0; i<=n; ++i) h[i]=Complex(q[n-i],0);
	for(int i=1; i<=n; ++i) g[i]=Complex(1.0/i/i,0);
	g[0]=Complex(0,0);
	FFT(f,lim,1), FFT(g,lim,1), FFT(h,lim,1);
	for(int i=0; i<lim; ++i) f[i]=f[i]*g[i], h[i]=h[i]*g[i];
	FFT(f,lim,-1), FFT(h,lim,-1);
	for(int i=0; i<=n; ++i) printf("%.3lf\n",f[i].x-h[n-i].x);

	return 0;
}
