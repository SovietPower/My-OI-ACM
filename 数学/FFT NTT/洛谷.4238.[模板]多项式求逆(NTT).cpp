//520ms	6.1MB
//对于len,lim的取值(< or <=)有点迷。。(n是减1后的，且此时n=2^x)main()里的while(len<=n)，如果是len<n，只是输出的n次系数为0这有问题，why？
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define P (998244353)
#define R (3)
#define inv_R (332748118)
#define Mult(a,b) (1ll*a*b%P)
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
//#define Add(x,v) (x)+=(v),(x)>=P?(x)-=P:0
typedef long long LL;
const int N=(1<<18)+5;

int n,F[N],G[N],A[N],B[N],rev[N],W[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1, x=Mult(x,x))
		if(k&1) t=Mult(x,t);
	return t;
}
void NTT(int *a,int type,int len)
{
	int lim=1, L=0;
	while(lim<len) lim<<=1, ++L;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<L-1);
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1, Wn=FP(~type?R:inv_R,(P-1)/i), t;
		W[0]=1;
		for(int j=1; j<mid; ++j) W[j]=Mult(W[j-1],Wn);
		for(int j=0; j<lim; j+=i)
			for(int k=0; k<mid; ++k)
				a[j+k+mid]=(a[j+k]-(t=Mult(a[j+k+mid],W[k]))+P)%P,
				a[j+k]=(a[j+k]+t)%P;
	}
	if(type==-1)
		for(int i=0,inv=FP(lim,P-2); i<lim; ++i) a[i]=Mult(a[i],inv);
}
void Get_inv(int *f,int *g,int len)
{
	if(len==1) {g[0]=FP(f[0],P-2); return;}
	Get_inv(f,g,len>>1);
//	memcpy(A,f,sizeof A), memcpy(B,g,sizeof B);//WA(除非加上下面一行):len~lim部分应为0，interesting~
//	for(int i=len; i<N; ++i) A[i]=B[i]=0;
	for(int i=0; i<len; ++i) A[i]=f[i], B[i]=g[i];
	NTT(A,1,len<<1), NTT(B,1,len<<1);
	for(int i=0; i<(len<<1); ++i) A[i]=Mult(A[i],Mult(B[i],B[i]));
	NTT(A,-1,len<<1);
	for(int i=0; i<len; ++i) g[i]=((g[i]<<1)%P-A[i]+P)%P;
}

int main()
{
	n=read()-1;
	for(int i=0; i<=n; ++i) F[i]=read();
	int len=1;
	while(len<=n) len<<=1;//<?
	Get_inv(F,G,len);
	for(int i=0; i<=n; ++i) printf("%d ",G[i]);
	return 0;
}
