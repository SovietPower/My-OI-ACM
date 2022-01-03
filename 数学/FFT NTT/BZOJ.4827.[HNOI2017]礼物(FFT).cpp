/*
12380kb	1120ms��Ϊɶ�ҵ�FFT��ô����QAQ��
$Description$
�����������������$n$����$x_1,...,x_n,y_1,...,y_n$������Խ�һ������ת����Ƕȣ��Լ���һ���������е�����������Ǹ�����$c$��
��ת���޸ĺ󣬽���������ĳ��λ�����α��$1,2,...,n$����$\sum_{i=1}^n(x_i-y_i)^2$����Сֵ��
$n\leq 50000,\ x_i,y_i\leq 100$��
$Solution$
���Ȳ���ö����ת���ٴ�$k$��Ȼ����Ŀ����Ҫ��$\sum_{i=1}^{n}(x_{i+k}-y_i+c)^2$����Сֵ������$k\in[0,n)$��$c\in[-m,m]$����Ȼ$c$ö�ٵ�$m$���㹻�ˣ�����һ�������ӿ��Կ�����������٣�����$x_{i+n}=x_i$���Ǹ���������
��ʽ�Ӳ𿪣�
$$\sum_{i=1}^{n}(x_{i+k}-y_i+c)^2=\sum_{i=1}^{n}\left[x_{i+k}^2+y_i^2-2x_{i+k}y_i+c^2+2c(x_{i+k}-y_i)\right]$$
�ٰ�$\sum$���ˣ�
$$\sum_{i=1}^nx_{i+k}^2+\sum_{i=1}^n y_i^2-2\sum_{i=1}^n x_{i+k}y_i+nc^2+2c\left(\sum_{i=1}^n x_i-\sum_{i=1}^n y_i\right)$$
���Ƿ���ǰ������$\sum_{i=1}^nx_{i+k}^2+\sum_{i=1}^n y_i^2$�ǲ���ģ���������$nc^2+2c\left(\sum_{i=1}^n x_i-\sum_{i=1}^n y_i\right)$�������Ѿ�ȷ���������ֻ��$c$�йأ�ö��$c$�����Сֵ�Ϳ����ˡ�
Ȼ��������Ҫ��$\sum_{i=1}^n x_{i+k}y_i$�����ֵ����ֻ��$k$�йء�
�ⲻ�ͺ�[ĳЩFFT����](https://www.cnblogs.com/SovietPower/p/8991435.html)һ��ô����ת$x$��$y$���飬��Ϊ��$\sum_{i=1}^n x_{i+k}y_{n-i+1}$�����Ǿ���ˡ�$Ans_k$���Ƕ���ʽ��˺�ĵ�$n+k+1$�
ö��$k$ȡһ��$\max\{Ans_k\}$�Ϳ����ˡ�
���������д���˵���20min==
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<18)+5;//3n!
const double PI=acos(-1);

int X[N],Y[N],rev[N];
char IN[MAXIN],*SS=IN,*TT=IN;
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
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
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
				a[k+mid]=a[k]-(t=w*a[k+mid]), a[k]=a[k]+t;
		}
//		for(int j=0; j<mid; ++j) W[j]=w, w=w*Wn;//Ԥ�����Ȼ�������...
//		for(int j=0; j<lim; j+=i)
//			for(int k=0; k<mid; ++k)
//				a[j+k+mid]=a[j+k]-(t=W[k]*a[j+k+mid]), a[j+k]=a[j+k]+t;
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}
int Calc(int n)
{
	for(int i=1; i<=n; ++i) A[i+n]=A[i]=Complex(X[i],0);
	for(int i=1; i<=n; ++i) B[i]=Complex(Y[n-i+1],0);
	int lim=1,l=-1;
	while(lim<=3*n) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	FFT(A,lim,1), FFT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i];
	FFT(A,lim,-1);
	int ans=0;
	for(int k=0; k<n; ++k) ans=std::max(ans,(int)(A[n+k+1].x+0.5));
	return ans;
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) X[i]=read();
	for(int i=1; i<=n; ++i) Y[i]=read();
	int ans=0,s=0;
	for(int i=1; i<=n; ++i) ans+=X[i]*X[i]+Y[i]*Y[i], s+=X[i]-Y[i];
	int mn=2e9;
	for(int c=-m; c<=m; ++c) mn=std::min(mn,n*c*c+2*c*s);
	ans+=mn-2*Calc(n);
	printf("%d\n",ans);

	return 0;
}
