//670MS	11496K -> 327MS	6904K
//https://www.cnblogs.com/SovietPower/p/9366763.html
/*
$Description$
　　有$n$个长度分别为$1,2,\ldots,n$的珠子串，每个有$a_i$种，每种个数不限。求有多少种方法组成长度为$n$的串。答案对$313$取模。
$Solution$
　　令$f_i$表示组成长度为$i$的串的方案数，可以得到递推式：
$$f_i=\sum_{j=0}^{i-1}a_{i-j}f_j,\ f_0=1$$
或者$f_i=\sum_{j=1}^{i-1}a_{i-j}f_j+a_i$。
　　这样暴力是$O(n^2)$的。
　　因为运算的形式是卷积，可以用$FFT$代替，这样复杂度是$O(n^2\log n)$。再套用CDQ分治就可以$O(n\log^2 n)$了。
　　在分治过程中，先计算出$j\in [l,mid]$的$f_j$，与$a$做卷积，就可以得到区间$[l,mid]$对$f_i,\ i\in[mid+1,r]$的贡献。即
$$f_{i,i\in[mid+1,r]}+=\sum_{j=l}^{mid}a_{i-j}f_j$$
　　$a_{1\sim r-l}$与$f_{l\sim mid}$卷积后得到的多项式的第$mid+i-l$项（下标的话要-1），就是对$f_{mid+i}$的贡献。
　　（$a_{1,r-l}*f_{l,m}$的下标$0$项为$l+1$，那$mid+i$的下标就是$mid+i-l-1$）

　　因为只更新到$a_r$，它是由$f_{r-l-1}$转移来的，所以每次FFT的$lim$只需大于$r-l$即可。优化明显（670MS 11496K -> 327MS 6904K）。

　　注：这个项是从$0$编号的，如果把$a_0=0$这一项一起卷积，原第$mid-l+i$项的下标就是$mid-l+i$了（没什么用吧，但是网上的都这么写，理解了半天为啥要加上$a_0$，写完代码才明白。。）
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
//	Calc(a,r-l+1,f+l,mid-l+1);//算上a_0=0这一项 A[]的下标就不用-1了。。
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
