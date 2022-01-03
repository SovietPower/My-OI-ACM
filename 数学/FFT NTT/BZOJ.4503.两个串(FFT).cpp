/*
22280kb	3076ms(这慢的...==)
$Description$
给定两个字符串S和T，求T在S中出现了几次，以及分别在哪些位置出现。T中可能有'?'字符，这个字符可以匹配任何字符。
$|S|,|T|\leq 10^5$。
$Solution$
显然我们可以同[CF528D](https://www.cnblogs.com/SovietPower/p/8993572.html)一样枚举$26$个字符然后跑$FFT$。但字符集太大了，复杂度是$O(26n\log n)$，以$FFT$的常数肯定GG。（然而CF上一道题$n$更大但$36n\log n$的$FFT$还跑的非常轻松，这就是差距么...）
考虑没有通配符时能怎么做（不考虑$KMP$）。
把每个字符$a\sim z$映射到$1\sim26$，那么$S_i,T_i$匹配了就是$S_i=T_i$。考虑$S,T$做差。但是每个位置需要有$|T|$个值求和来表示匹配$T$串的情况，就算不匹配正负相加也可能变成$0$。
所以考虑平方，即若$f(x)=\sum_{i=0}^{|T|-1}(S_{x+i}-T_i)^2=0$，那么$x$位置匹配了$T$。
把平方和拆开，就可以得到两个常数项和一个$\sum_{i=0}^{|T|-1}S_{x+i}T_i$，把$T$反转后就可以$FFT$了。
如果有通配符呢？考虑如果$T_i$是通配符，怎么让它不产生影响，也就是贡献是$0$。
那么令通配符$T_i=0$，外面再乘个$T_i$就可以了。即
$$\begin{aligned}f(x)&=\sum_{i=0}^{|T|-1}(S_{x+i}-T_i)^2T_i\\&=\sum_{i=0}^{|T|-1}S_{x+i}^2T_i-2\sum_{i=0}^{|T|-1}S_{x+i}T_i^2+\sum_{i=0}^{|T|-1}T_i^3\end{aligned}$$
第三部分是个常数，前两部分可以分别$FFT$求出来。
*/
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<18)+5;
const double PI=acos(-1);

int S[N],T[N],rev[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Complex
{
	double x,y;
	Complex(double x=0,double y=0):x(x),y(y) {}
	Complex operator +(const Complex &a) {return Complex(x+a.x, y+a.y);}
	Complex operator -(const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator *(const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[N],B[N],C[N],D[N];

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
	static int pos[N];

	register char c;
	int n=0; while(isalpha(c=gc())) S[n++]=c-96;
	int m=0; while(isalpha(c=gc())||c=='?') T[m++]=c=='?'?0:c-96;
	std::reverse(T,T+m);//!
	for(int i=0; i<n; ++i) A[i]=Complex(S[i]*S[i],0),C[i]=Complex(S[i]<<1,0);
	int sumT=0;
	for(int i=0,t; i<m; ++i) B[i]=Complex(t=T[i],0),D[i]=Complex(t*t,0),sumT+=t*t*t;

	int lim=1,l=-1;
	while(lim<=n+m-2) lim<<=1,++l;//n+m-2就可以了...有点想不通...
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	FFT(A,lim,1), FFT(B,lim,1), FFT(C,lim,1), FFT(D,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i]-C[i]*D[i];//可以直接在这里计算然后只IDFT一次啊（反正都是多项式）
	FFT(A,lim,-1);

	int ans=0;
	for(int i=0; i<=n-m; ++i) if(!(int)(A[m+i-1].x+0.5+sumT)) pos[++ans]=i;
	printf("%d\n",ans);
	for(int i=1; i<=ans; printf("%d\n",pos[i++]));

	return 0;
}
