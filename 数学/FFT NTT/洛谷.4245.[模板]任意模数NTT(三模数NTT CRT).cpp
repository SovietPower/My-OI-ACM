/*
3786ms	8.95MB
模数不是$NTT$模数，考虑用多个$NTT$模数分别卷积，最后$CRT$合并（由中国剩余定理，同余方程组在模$M=\prod m_i$的情况下解是唯一的）。
卷积后$a_i$的最大值是$(10^9)^2\times10^5=10^{23}$，所以需要选几个乘积$>10^{23}$的质数，比如$m_1=998244353=2^{23}*119+1,\quad m_2=1004535809=2^{21}*479+1,\quad m_3=469762049=2^{26}*7+1$。它们的原根都是$3$。
最后我们能求出三个同余方程：$$x\equiv c_1\ (\mathbb{mod}\ m_1)\\x\equiv c_2\ (\mathbb{mod}\ m_2)\\x\equiv c_3\ (\mathbb{mod}\ m_3)$$
我们可以用$CRT$合并两个，就有$x\equiv c_4\ (\mathbb{mod}\ m_1m_2)$。
设$x=am_1m_2+c_4\equiv c_3\ (\mathbb{mod}\ m_3)$，就可以算出$a\equiv\frac{c_3-c_4}{m_1m_2}\ (\mathbb{mod}\ m_3)$，有了$a$代回去就算出$x$啦（虽然是模$m_3$意义下求的$a$，但是设$a=km_3+b$，代回到$x$里模$m_1m_2m_3$就把$km_3$那项消掉啦，只剩下$b$）（当然前两个式子也可以这么合并）。
这样一共需要$9$次$DFT$，常数巨大。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define G 3
#define MOD(x,mod) x>=mod&&(x-=mod)
#define ADD(x,v,mod) (x+=v)>=mod&&(x-=mod)
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<18)+3,Mod[]={998244353,469762049,1004535809};

int tA[N],tB[N],A[N],B[N],Ans[3][N],rev[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int FP(int x,int k,const int mod)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
inline LL Mult(LL a,LL b,LL p)
{
	LL t=a*b-(LL)((long double)a/p*b+1e-8)*p;
	return t<0?t+p:t;
}
void NTT(int *a,int lim,int opt,const int mod)
{
	const int invG=FP(G,mod-2,mod);
	for(int i=1; i<lim; ++i) if(i<rev[i]) std::swap(a[i],a[rev[i]]);//&&
	for(int i=2; i<=lim; i<<=1)
	{
		int mid=i>>1,Wn=FP(~opt?G:invG,(mod-1)/i,mod);
		for(int j=0; j<lim; j+=i)
			for(int t,w=1,k=j; k<j+mid; ++k,w=1ll*w*Wn%mod)
				a[k+mid]=a[k]+mod-(t=1ll*a[k+mid]*w%mod), MOD(a[k+mid],mod),
				ADD(a[k],t,mod);
	}
	if(opt==-1) for(int i=0,inv=FP(lim,mod-2,mod); i<lim; ++i) a[i]=1ll*a[i]*inv%mod;
}
void Solve(const int lim,int *ans,const int mod)
{
	memcpy(A,tA,lim<<2), memcpy(B,tB,lim<<2);//不能只赋值到n！（清空后面的）
	NTT(A,lim,1,mod), NTT(B,lim,1,mod);
	for(int i=0; i<lim; ++i) A[i]=1ll*A[i]*B[i]%mod;
	NTT(A,lim,-1,mod);
	for(int i=0; i<lim; ++i) ans[i]=A[i];
}

int main()
{
	const int n=read(),m=read(),P=read();
	for(int i=0; i<=n; ++i) tA[i]=read(),tA[i]>=P&&(tA[i]%=P);
	for(int i=0; i<=m; ++i) tB[i]=read(),tB[i]>=P&&(tB[i]%=P);
	int lim=1,l=-1; while(lim<=n+m) lim<<=1,++l;
	for(int i=1; i<lim; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	for(int i=0; i<3; ++i) Solve(lim,Ans[i],Mod[i]);
	#define m1 998244353ll
	#define m2 469762049ll
	#define m3 1004535809ll
	const LL M12=m1*m2,inv2=FP(m2,m1-2,m1),inv1=FP(m1,m2-2,m2),mul2=m2*inv2%M12,mul1=m1*inv1%M12,
			inv=FP(M12%m3,m3-2,m3),m12=M12%P;
	for(int i=0,t=n+m; i<=t; ++i)
	{
		LL c1=Ans[0][i],c2=Ans[1][i],c3=Ans[2][i],c4=Mult(c1,mul2,M12)+Mult(c2,mul1,M12);
		MOD(c4,M12);
		LL a=((c3-c4)%m3+m3)/*%m3*/*inv%m3;
		printf("%d ",(int)((a*m12+c4)%P));
	}

	return 0;
}
