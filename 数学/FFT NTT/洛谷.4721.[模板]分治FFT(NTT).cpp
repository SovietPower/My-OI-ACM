//693ms	4.91MB
//https://www.cnblogs.com/SovietPower/p/9650088.html
/*
$Description$
给定$g_1,...,g_{n-1}$，求$f_0,...,f_{n-1}$。其中$f_i=\sum_{j=1}^if_{i-j}g_j$，$f_0=1$。对998244353取模。
$n\leq 10^5$。
$Solution$
换一下形式：$$f_i=\sum_{j=0}^{i-1}f_jg_{i-j}$$
然后就是分治FFT模板了
$$f_{i,i\in[mid+1,r]}=\sum_{j=l}^{mid}f_jg_{i-j}+\sum_{j=mid+1}^rf_jg_{i-j}$$
复杂度$O(n\log^2n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define G 3
#define inv_G 332748118
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=(1<<18)+5;

int rev[N],A[N],B[N],f[N],g[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}
void NTT(int *a,int lim,int type)
{
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		LL Wn=FP(~type?G:inv_G,(mod-1)/i);
		for(int j=0; j<lim; j+=i)
		{
			LL w=1,t;
			for(int k=0; k<mid; ++k,w=w*Wn%mod)
				a[j+k+mid]=(a[j+k]-(t=w*a[j+k+mid]%mod)+mod), Mod(a[j+k+mid]),
				Add(a[j+k],t);
		}
	}
	if(type==-1) for(int i=0,inv=FP(lim,mod-2); i<lim; ++i) a[i]=1ll*a[i]*inv%mod;
}
void Calc(int *a,int l1,int *b,int l2)
{
	int lim=1,l=-1;
	while(lim<=l1/*!*/) ++l,lim<<=1;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);

	for(int i=0; i<l1; ++i) A[i]=a[i];
	for(int i=l1; i<lim; ++i) A[i]=0;
	for(int i=0; i<l2; ++i) B[i]=b[i];
	for(int i=l2; i<lim; ++i) B[i]=0;
	NTT(A,lim,1), NTT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=1ll*A[i]*B[i]%mod;//not a,b
	NTT(A,lim,-1);
}
void CDQ(int l,int r)
{
	if(l==r) return;
	int mid=l+r>>1; CDQ(l,mid);

	Calc(g+1,r-l,f+l,mid-l+1);
	for(int i=mid+1; i<=r; ++i) Add(f[i],A[i-l-1]);

	CDQ(mid+1,r);
}

int main()
{
	int n=read();
	for(int i=1; i<n; ++i) g[i]=read();
	f[0]=1, CDQ(0,n-1);
	for(int i=0; i<n; ++i) printf("%d ",f[i]);

	return 0;
}
