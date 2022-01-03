//285ms	3.53MB
//https://www.k-xzy.xyz/archives/7598
/*
$Description$
给定$A_i,B_i$，求$C_i$，其中$C_i=\sum_{j\oplus k=i}A_j\times B_k$。
$\oplus$分别为AND、OR、XOR时输出答案。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define inv2 499122177
#define mod 998244353
#define Add(x,y) (x+y>=mod?x+y-mod:x+y)
#define Sub(x,y) (x<y?x-y+mod:x-y)
typedef long long LL;
const int N=(1<<17)+5;

int A[N],B[N],C[N],tA[N],tB[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void FWT_OR(int *a,int lim,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j; k<j+mid; ++k)
				if(opt==1) a[k+mid]=Add(a[k+mid],a[k]);
				else a[k+mid]=Sub(a[k+mid],a[k]);
}
void FWT_AND(int *a,int lim,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j; k<j+mid; ++k)
				if(opt==1) a[k]=Add(a[k],a[k+mid]);
				else a[k]=Sub(a[k],a[k+mid]);
}
void FWT_XOR(int *a,int lim,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j,x,y; k<j+mid; ++k)
			{
				x=a[k], y=a[k+mid];
				a[k]=Add(x,y), a[k+mid]=Sub(x,y);
				if(opt==-1) a[k]=1ll*a[k]*inv2%mod, a[k+mid]=1ll*a[k+mid]*inv2%mod;
			}
}

int main()
{
	int n=1<<read();
	for(int i=0; i<n; ++i) tA[i]=read();
	for(int i=0; i<n; ++i) tB[i]=read();

	memcpy(A,tA,sizeof A), memcpy(B,tB,sizeof B);
	FWT_OR(A,n,1), FWT_OR(B,n,1);
	for(int i=0; i<n; ++i) C[i]=1ll*A[i]*B[i]%mod;
	FWT_OR(C,n,-1);
	for(int i=0; i<n; ++i) printf("%d ",C[i]);
	putchar('\n'); //FWT_OR(A,n,-1), FWT_OR(B,n,-1);

	memcpy(A,tA,sizeof A), memcpy(B,tB,sizeof B);
	FWT_AND(A,n,1), FWT_AND(B,n,1);
	for(int i=0; i<n; ++i) C[i]=1ll*A[i]*B[i]%mod;
	FWT_AND(C,n,-1);
	for(int i=0; i<n; ++i) printf("%d ",C[i]);
	putchar('\n');

	memcpy(A,tA,sizeof A), memcpy(B,tB,sizeof B);
	FWT_XOR(A,n,1), FWT_XOR(B,n,1);
	for(int i=0; i<n; ++i) C[i]=1ll*A[i]*B[i]%mod;
	FWT_XOR(C,n,-1);
	for(int i=0; i<n; ++i) printf("%d ",C[i]);
	putchar('\n');

	return 0;
}
