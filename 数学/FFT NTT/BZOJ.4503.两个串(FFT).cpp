/*
22280kb	3076ms(������...==)
$Description$
���������ַ���S��T����T��S�г����˼��Σ��Լ��ֱ�����Щλ�ó��֡�T�п�����'?'�ַ�������ַ�����ƥ���κ��ַ���
$|S|,|T|\leq 10^5$��
$Solution$
��Ȼ���ǿ���ͬ[CF528D](https://www.cnblogs.com/SovietPower/p/8993572.html)һ��ö��$26$���ַ�Ȼ����$FFT$�����ַ���̫���ˣ����Ӷ���$O(26n\log n)$����$FFT$�ĳ����϶�GG����Ȼ��CF��һ����$n$����$36n\log n$��$FFT$���ܵķǳ����ɣ�����ǲ��ô...��
����û��ͨ���ʱ����ô����������$KMP$����
��ÿ���ַ�$a\sim z$ӳ�䵽$1\sim26$����ô$S_i,T_i$ƥ���˾���$S_i=T_i$������$S,T$�������ÿ��λ����Ҫ��$|T|$��ֵ�������ʾƥ��$T$������������㲻ƥ���������Ҳ���ܱ��$0$��
���Կ���ƽ��������$f(x)=\sum_{i=0}^{|T|-1}(S_{x+i}-T_i)^2=0$����ô$x$λ��ƥ����$T$��
��ƽ���Ͳ𿪣��Ϳ��Եõ������������һ��$\sum_{i=0}^{|T|-1}S_{x+i}T_i$����$T$��ת��Ϳ���$FFT$�ˡ�
�����ͨ����أ��������$T_i$��ͨ�������ô����������Ӱ�죬Ҳ���ǹ�����$0$��
��ô��ͨ���$T_i=0$�������ٳ˸�$T_i$�Ϳ����ˡ���
$$\begin{aligned}f(x)&=\sum_{i=0}^{|T|-1}(S_{x+i}-T_i)^2T_i\\&=\sum_{i=0}^{|T|-1}S_{x+i}^2T_i-2\sum_{i=0}^{|T|-1}S_{x+i}T_i^2+\sum_{i=0}^{|T|-1}T_i^3\end{aligned}$$
���������Ǹ�������ǰ�����ֿ��Էֱ�$FFT$�������
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
	while(lim<=n+m-2) lim<<=1,++l;//n+m-2�Ϳ�����...�е��벻ͨ...
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	FFT(A,lim,1), FFT(B,lim,1), FFT(C,lim,1), FFT(D,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i]-C[i]*D[i];//����ֱ�����������Ȼ��ֻIDFTһ�ΰ����������Ƕ���ʽ��
	FFT(A,lim,-1);

	int ans=0;
	for(int i=0; i<=n-m; ++i) if(!(int)(A[m+i-1].x+0.5+sumT)) pos[++ans]=i;
	printf("%d\n",ans);
	for(int i=1; i<=ans; printf("%d\n",pos[i++]));

	return 0;
}
