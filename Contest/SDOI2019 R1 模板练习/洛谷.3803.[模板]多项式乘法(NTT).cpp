/*
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 998244353
#define G 3
#define invG 332748118
#define Mod(x) x>=mod&&(x-=mod)
#define gc() getchar()
typedef long long LL;
const int N=(1<<21)+5;

int f[N],g[N],rev[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod) k&1&&(t=1ll*t*x%mod);
	return t;
}
void NTT(int *a,int lim,int opt)
{
	for(int i=0; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1; LL Wn=FP(~opt?G:invG,(mod-1)/i);
		for(int j=0; j<lim; j+=i)
			for(int k=j,t,w=1; k<j+mid; ++k,w=w*Wn%mod)
				a[k+mid]=a[k]+mod-(t=1ll*w*a[k+mid]%mod), Mod(a[k+mid]), a[k]+=t, Mod(a[k]);
	}
	if(opt==-1) for(int i=0,inv=FP(lim,mod-2); i<lim; ++i) a[i]=1ll*a[i]*inv%mod;
}

int main()
{
	int n=read()+1,m=read()+1;
	for(int i=0; i<n; ++i) f[i]=read();
	for(int i=0; i<m; ++i) g[i]=read();
	int lim=1,bit=-1;
	while(lim<=n+m) lim<<=1,++bit;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<bit);

	NTT(f,lim,1), NTT(g,lim,1);
	for(int i=0; i<lim; ++i) f[i]=1ll*f[i]*g[i]%mod;
	NTT(f,lim,-1);
	for(int i=0,l=n+m-2; i<=l; ++i) printf("%d ",f[i]);

	return 0;
}
