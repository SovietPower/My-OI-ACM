//11072kb	6148ms
//https://www.cnblogs.com/SovietPower/p/9641460.html
/*
$Description$
�׳�$Y$��������$0,...,X-1$�����ӣ�������ܺ���$[A,B]$�ĸ��ʡ�
$X\leq 20,\ Y\leq 2\times 10^5$��
$Solution$
### ��̬�ֲ�
[��̬�ֲ�](https://baike.baidu.com/item/%E6%AD%A3%E6%80%81%E5%88%86%E5%B8%83/829892?fr=aladdin#3)���������$X$��һ�ָ��ʷֲ���ʽ������һ������$\mu$�ͷ���$\sigma^2$�Ϳ�����������Ϊ$N(\mu,\sigma^2)$��
���������$X$����һ����ѧ����Ϊ$\mu$������Ϊ$\sigma^2$����̬�ֲ�������$X\sim N(\mu,\sigma^2)$������$X$����$N(\mu,\sigma^2)$��
��$\mu=0,\sigma=1$ʱ����̬�ֲ���Ϊ��׼��̬�ֲ���

### �����ܶȺ���
[�����ܶȺ���](https://baike.baidu.com/item/%E6%A6%82%E7%8E%87%E5%AF%86%E5%BA%A6%E5%87%BD%E6%95%B0)����������������������ķֲ���������������ȡֵ����ĳ�������ڵĸ��ʣ�Ϊ�����ܶȺ����ڸ�����Ļ��֡������߾���$f(x)$�ڸ���������$x$��Χ�ɵ�ͼ�������
���������$X\sim N(\mu,\sigma^2)$����������ܶȺ���Ϊ
$$f(x)=\frac{1}{\sqrt{2\pi}\sigma}e^{-\frac{(x-\mu)^2}{2\sigma}}$$
$e^x$����ʹ��$exp()$�������㡣ֻҪ֤����һ������������̬�ֲ����Ϳ���ֱ�ӶԸ����ܶȺ�������һ������л����ˡ�

### ���ļ��޶���
[���ļ��޶���](https://baike.baidu.com/item/%E4%B8%AD%E5%BF%83%E6%9E%81%E9%99%90%E5%AE%9A%E7%90%86/829451?fr=aladdin)����������$n$�����������ʱ��$n$�����������ľ�ֵ��Ƶ����������̬�ֲ�������������ʲô�ֲ�����
�ö���˵�������������$X_1,X_2,\ldots,X_n$����ͬ�ֲ������ǵ�����Ϊ$\mu$������Ϊ$\sigma^2$����$n$�㹻��ʱ��OI:���㾫ȷ������ʱ�����������
$$Y_n=\frac{\sum_{i=1}^nX_i-n\mu}{\sqrt n\sigma}$$
���Ƶط��ӱ�׼��̬�ֲ�$N(0,1)$��

$Y_n$������̬�ֲ�������䷶Χ��Ϳ���ֱ�Ӷ���̬�ֲ��ĸ����ܶȺ���������ˡ�
���ڱ�����
$$\mu=\frac{n-1}{2}��\sigma^2=\frac{\sum_{i=1}^n(i-\mu)^2}{n}=\frac{n^2-1}{12}\\ \sum_{i=1}^nX_i\in[A,B]\\ Y_n\in[\frac{A-n\mu}{\sqrt n\sigma},\frac{B-n\mu}{\sqrt n\sigma}$$
Ȼ���$Y_n$��ֵ������ɭ���֣�$\int_l^rf(x)d_x=\frac{(r-l)(f(l)+f(r)+4f(mid))}{6}$����

���ǵ�$n=1$ʱҲ������Ϊ$n$�㹻�����Ե����ݽ�СʱҪ����һ���������Ƚ���Ȼ���ǹ������ɺ�����Ȼ������$Y$���ݡ�
���ﹹ������ɺ�������FFT������ʽת��Ϊ��ֵ��ʾ������ֱ�ӶԵ�ֵ�����ݣ���FFT��ȥ��

����Ҫ��$[0,r]-[0,l]$�ģ�ֱ����$[l,r]$ֻ��80�֡�����������
����ʱ��$l,r$��С��ϵ����Ӱ�졣
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define eps 1e-7
const int N=(1<<19)+5;
const double PI=acos(-1),K=1.0/sqrt(2*PI);

int rev[N];
struct Com//plex
{
	double x,y;
	Com() {}
	Com(double x,double y):x(x),y(y) {}
	Com operator +(const Com &a) {return Com(x+a.x, y+a.y);}
	Com operator -(const Com &a) {return Com(x-a.x, y-a.y);}
	Com operator *(const Com &a) {return Com(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
Com FP(Com x,int k)//����ֱ�ӵ�ֵ������ 
{
	Com t(1,0);
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}
void FFT(Com *a,int lim,int opt)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		Com Wn(cos(PI/mid),opt*sin(PI/mid)),t;
		for(int j=0; j<lim; j+=i)
		{
			Com w(1,0);
			for(int k=0; k<mid; ++k,w=w*Wn)
				a[j+k+mid]=a[j+k]-(t=a[j+k+mid]*w),
				a[j+k]=a[j+k]+t;
		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}
inline double F(double x)
{
	return K*exp(-x*x*0.5);
}
inline double Simpson(double l,double r)
{
	return (r-l)*(F(l)+F(r)+4*F((l+r)*0.5))/6.0;
}
double Int(double l,double r,double Eps,double ans)
{
	double m=(l+r)*0.5,lans=Simpson(l,m),rans=Simpson(m,r);
	if(fabs(lans+rans-ans)<Eps) return lans+rans;
	return Int(l,m,Eps*0.5,lans)+Int(m,r,Eps*0.5,rans);
}

int main()
{
	for(int T=read(),X,Y,lim; T--; )
	{
		X=read(),Y=read(),lim=X*Y;
		int len=0;
		while(1<<len<=lim) ++len; lim=1<<len;
		if(lim<N)
		{
			--len;
			for(int i=0; i<lim; ++i) A[i]=Com(0,0),rev[i]=(rev[i>>1]>>1)|((i&1)<<len);
			double xx=1.0/X,ans;
			for(int i=0; i<X; ++i) A[i].x=xx;
			FFT(A,lim,1);
			for(int i=0; i<lim; ++i) A[i]=FP(A[i],Y);
			FFT(A,lim,-1);
			for(int i=1,l,r; i<=10; ++i)
			{
				l=read(),r=read(),ans=0;
				for(int j=l; j<=r; ++j) ans+=A[j].x;
				printf("%.7lf\n",ans);
			}
		}
		else
		{
			double l,r,mu=1.0*(X-1)/2,sigma=1.0*(X*X-1)/12/*\sigma^2*/,a=mu*Y,b=sqrt(sigma*Y);
			for(int i=1; i<=10; ++i)
				l=1.0*(read()-a)/b, r=1.0*(read()-a)/b,
				printf("%.7lf\n",Int(0,r,eps,Simpson(0,r))-Int(0,l,eps,Simpson(0,l)));
//				printf("%.7lf\n",Int(l,r,eps,Simpson(l,r)));//WA
		}
	}
	return 0;
}
