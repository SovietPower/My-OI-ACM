//TLE。暴力卷积或是分治NTT可过。
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define P (998244353)
#define G (3)
#define inv_G (332748118)
typedef long long LL;
const int N=(1<<22)+5;

int n,m,K,rev[N],inv[N];
LL A[N],B[N],inv_lim;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL FP(LL x,LL k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%P)
		if(k&1) t=t*x%P;
	return t;
}
void NTT(LL *a,int lim,int type)
{
	for(int i=0; i<lim; ++i)
		if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1;
		LL Wn=FP(~type?G:inv_G,(P-1)/i),t,w;
		for(int j=0; j<lim; j+=i)
		{
			LL w=1;
			for(int k=0; k<mid; ++k, w=w*Wn%P)
				a[j+k+mid]=(a[j+k]-(t=w*a[j+k+mid]%P)+P)%P,
				a[j+k]=(a[j+k]+t)%P;
		}
	}
	if(type==-1) for(int i=0; i<lim; ++i) a[i]=a[i]*inv_lim%P;
}
inline void Mult(LL *a,LL *b,int n,int m)
{
//	for(int i=1; i<=n; ++i) printf("A[%d]:%I64d\n",i,A[i]);
//	for(int i=1; i<=m; ++i) printf("B[%d]:%I64d\n",i,B[i]);
	int lim=1,len=0;
	while(lim<=n+m) lim<<=1,++len;
	inv_lim=FP(lim,P-2);
	for(int i=1; i<lim; ++i)
		rev[i] = (rev[i>>1]>>1) | ((i&1)<<len-1);
	NTT(A,lim,1), NTT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i]%P;
	NTT(A,lim,-1);
//	for(int i=1; i<lim; ++i) printf("A[%d]:%I64d\n",i,A[i]);
	for(int i=n+m+1; i<lim; ++i) A[i]=0;
	for(int i=0; i<lim; ++i) B[i]=0;
}
//void CDQ(int l,int r)
//{
//	if(l>=r) return;
//	int m=l+r>>1;
//	CDQ(l,m), Mult(), CDQ(m+1,r);
//}

int main()
{
	n=read(),m=read(),K=read();
	inv[1]=1;
	for(int i=2; i<=n; ++i)
		inv[i]=1ll*(P-P/i)*inv[P%i]%P;

	int sum=read(),C=1;
	for(int i=1; i<=sum; ++i) A[i]=C=1ll*C*(sum-i+1)%P*inv[i]%P;
	for(int i=2; i<=m; ++i)
	{
		int s=read(),C=1;
		for(int j=1; j<=s; ++j)
			B[j]=C=1ll*C*(s-j+1)%P*inv[j]%P;
		Mult(A,B,sum,s), sum+=s;
	}
	printf("%lld\n",A[K]);

	return 0;
}
