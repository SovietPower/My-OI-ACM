#include <cstdio>
#include <cctype>
#include <algorithm>
#define P (998244353)
#define G (3)
#define inv_G (332748118)
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<21)+5;//2 097 152 //2e6+5;

int n,m,rev[N];
LL A[N],B[N],inv_lim;//全换成int好像大概略快吧 
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	register char c=gc();
	for(;!isdigit(c);c=gc());
	return c-'0';//233
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

int main()
{
	scanf("%d%d",&n,&m);//sb了拿那个read读n,m。。
	for(int i=0; i<=n; ++i) A[i]=read();//(read()%P+P)%P
	for(int i=0; i<=m; ++i) B[i]=read();
	int lim=1,len=0;
	while(lim<=n+m) lim<<=1,++len;
	inv_lim=FP(lim,P-2);
	for(int i=1; i<lim; ++i)
		rev[i] = (rev[i>>1]>>1) | ((i&1)<<len-1);
	NTT(A,lim,1), NTT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]=A[i]*B[i]%P;
	NTT(A,lim,-1);
	for(int i=0; i<=n+m; ++i) printf("%lld ",A[i]);

	return 0;
}
