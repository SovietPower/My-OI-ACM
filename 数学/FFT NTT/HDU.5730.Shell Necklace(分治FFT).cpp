//670MS	11496K -> 327MS	6904K
//https://www.cnblogs.com/SovietPower/p/9366763.html
/*
$Description$
������$n$�����ȷֱ�Ϊ$1,2,\ldots,n$�����Ӵ���ÿ����$a_i$�֣�ÿ�ָ������ޡ����ж����ַ�����ɳ���Ϊ$n$�Ĵ����𰸶�$313$ȡģ��
$Solution$
������$f_i$��ʾ��ɳ���Ϊ$i$�Ĵ��ķ����������Եõ�����ʽ��
$$f_i=\sum_{j=0}^{i-1}a_{i-j}f_j,\ f_0=1$$
����$f_i=\sum_{j=1}^{i-1}a_{i-j}f_j+a_i$��
��������������$O(n^2)$�ġ�
������Ϊ�������ʽ�Ǿ����������$FFT$���棬�������Ӷ���$O(n^2\log n)$��������CDQ���ξͿ���$O(n\log^2 n)$�ˡ�
�����ڷ��ι����У��ȼ����$j\in [l,mid]$��$f_j$����$a$��������Ϳ��Եõ�����$[l,mid]$��$f_i,\ i\in[mid+1,r]$�Ĺ��ס���
$$f_{i,i\in[mid+1,r]}+=\sum_{j=l}^{mid}a_{i-j}f_j$$
����$a_{1\sim r-l}$��$f_{l\sim mid}$�����õ��Ķ���ʽ�ĵ�$mid+i-l$��±�Ļ�Ҫ-1�������Ƕ�$f_{mid+i}$�Ĺ��ס�
������$a_{1,r-l}*f_{l,m}$���±�$0$��Ϊ$l+1$����$mid+i$���±����$mid+i-l-1$��

������Ϊֻ���µ�$a_r$��������$f_{r-l-1}$ת�����ģ�����ÿ��FFT��$lim$ֻ�����$r-l$���ɡ��Ż����ԣ�670MS 11496K -> 327MS 6904K����

����ע��������Ǵ�$0$��ŵģ������$a_0=0$��һ��һ������ԭ��$mid-l+i$����±����$mid-l+i$�ˣ�ûʲô�ðɣ��������ϵĶ���ôд������˰���ΪɶҪ����$a_0$��д���������ס�����
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mod (313)
const double PI=acos(-1);
const int N=1e5+5,M=(1<<18)+1;//262144

int n,a[N],rev[M],f[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Complex
{
	double x,y;
	Complex() {}
	Complex(double x,double y):x(x),y(y) {}
	Complex operator +(const Complex &a) {return Complex(x+a.x, y+a.y);}
	Complex operator -(const Complex &a) {return Complex(x-a.x, y-a.y);}
	Complex operator *(const Complex &a) {return Complex(x*a.x-y*a.y, x*a.y+y*a.x);}
}A[M],B[M];

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
		int mid=i>>1;
		Complex Wn(cos(PI/mid),opt*sin(PI/mid)),t;//Wn(cos(2.0*PI/i),opt*sin(2.0*PI/i)),t;
		for(int j=0; j<lim; j+=i)
		{
			Complex w(1,0);
			for(int k=0; k<mid; ++k,w=w*Wn)
				a[j+mid+k]=a[j+k]-(t=a[j+mid+k]*w),
				a[j+k]=a[j+k]+t;
		}
	}
	if(opt==-1) for(int i=0; i<lim; ++i) a[i].x/=lim;
}
void Calc(int *a,int len1,int *b,int len2)
{
	int lim=1, L=-1;
	while(lim<=len1) lim<<=1, ++L; 
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<L);

	for(int i=0; i<len1; ++i) A[i]=Complex(a[i],0);
	for(int i=len1; i<lim; ++i) A[i]=Complex(0,0);
	for(int i=0; i<len2; ++i) B[i]=Complex(b[i],0);
	for(int i=len2; i<lim; ++i) B[i]=Complex(0,0);
	FFT(A,lim,1), FFT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i];
	FFT(A,lim,-1);
}
void CDQ(int l,int r)
{
	if(l==r) return;
	int mid=l+r>>1;
	CDQ(l,mid);

	Calc(a+1,r-l,f+l,mid-l+1);
	for(int i=mid+1; i<=r; ++i) (f[i]+=((long long)(A[i-l-1].x+0.5)%mod))%=mod;//mid+1-l -> mid+1
//	Calc(a,r-l+1,f+l,mid-l+1);//����a_0=0��һ�� A[]���±�Ͳ���-1�ˡ���
//	for(int i=mid+1; i<=r; ++i) (f[i]+=((long long)(A[i-l].x+0.5)%mod))%=mod;//mid+1-l -> mid+1
//	for(int i=mid-l+1; i<=r-l; ++i) (f[l+i]+=((long long)(A[i].x+0.5)%mod))%=mod;//longlong!
//	mid+i <= r  ->  i <= mid-l+r-mid = r-l ?

	CDQ(mid+1,r);
}

int main()
{
	while(n=read())
	{
		memset(f,0,sizeof f);
		for(int i=1; i<=n; ++i) a[i]=read()%mod;
		f[0]=1, CDQ(0,n), printf("%d\n",f[n]);
	}
	return 0;
}
