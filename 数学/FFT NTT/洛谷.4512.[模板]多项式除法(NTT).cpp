//640ms	7.55MB
//https://www.cnblogs.com/SovietPower/p/9160446.html
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define P (998244353)
#define Rt (3)
#define i_Rt (332748118)
#define Mul(a,b) (1ll*a*b%P)
#define Sub(a,b) (a<b ? a-b+P : a-b)
#define Clear() memset(A,0,sizeof A),memset(B,0,sizeof B)
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=(1<<18)+5;

int n,m,F[N],D[N],invD[N],Q[N],A[N],B[N],tmp[N],rev[N],W[N];//F = divisor * quotient + remainder
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
	for(; k; k>>=1, x=Mul(x,x))
		if(k&1) t=Mul(x,t);
	return t;
}
inline int Get_len(int x)
{
	int len=1; while(len<=x) len<<=1;
	return len;
}
void NTT(int *a,int len,int type)//polynomial
{
	int lim=1, L=0;
	while(lim<len) lim<<=1, ++L;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<L-1);
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1, Wn=FP(~type?Rt:i_Rt,(P-1)/i), t;//次数:(P-1)/i!
		W[0]=1;
		for(int j=1; j<mid; ++j) W[j]=Mul(W[j-1],Wn);
		for(int j=0; j<lim; j+=i)
			for(int k=0; k<mid; ++k)
				a[j+k+mid]=(a[j+k]-(t=Mul(a[j+k+mid],W[k]))+P)%P,
				a[j+k]=(a[j+k]+t)%P;
	}
	if(type==-1)
		for(int i=0,inv=FP(lim,P-2); i<lim; ++i) a[i]=Mul(a[i],inv);
}
void P_Inv(int *f,int *g,int len)//len:要求逆元的长度 
{
	if(len==1) {g[0]=FP(f[0],P-2); return;}
	P_Inv(f,g,len>>1);
	for(int i=0; i<len; ++i) A[i]=f[i], B[i]=g[i];
	NTT(A,len<<1,1), NTT(B,len<<1,1);
	for(int i=0; i<len<<1; ++i) A[i]=Mul(A[i],Mul(B[i],B[i]));
	NTT(A,len<<1,-1);
	for(int i=0; i<len; ++i) g[i]=((g[i]<<1)%P-A[i]+P)%P;
}
void P_Mul(int *a,int *b,int *res,int l1,int l2)
{
	int len=Get_len(l1+l2);
	Clear();
	for(int i=0; i<=l1; ++i) A[i]=a[i];
	for(int i=0; i<=l2; ++i) B[i]=b[i];
	NTT(A,len,1), NTT(B,len,1);
	for(int i=0; i<len; ++i) res[i]=Mul(A[i],B[i]);
	NTT(res,len,-1);
}

int main()
{
	n=read(),m=read();
	for(int i=0; i<=n; ++i) F[i]=read();
	for(int i=0; i<=m; ++i) D[i]=read();
	std::reverse(F,F+n+1), std::reverse(D,D+m+1);
	P_Inv(D,invD,Get_len(n-m));
	P_Mul(F,invD,Q,n-m,n-m);//次数都是n-m (mod x^{n-m+1}) 
	std::reverse(Q,Q+n-m+1);
	for(int i=0; i<=n-m; ++i) printf("%d ",Q[i]); putchar('\n');

	std::reverse(F,F+n+1), std::reverse(D,D+m+1);
	P_Mul(D,Q,tmp,m,n-m);
	for(int i=0; i<m; ++i) printf("%d ",Sub(F[i],tmp[i]));

	return 0;
}
