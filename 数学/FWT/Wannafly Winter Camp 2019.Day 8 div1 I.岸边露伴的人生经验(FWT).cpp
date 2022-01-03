/*
167ms	6MB
$Description$
给定$n$个十维向量$\overrightarrow{V_i}=x_1,x_2,...,x_{10}$。定义$\overrightarrow{V}=x_1,x_2,...,x_{10}$的模长$|\overrightarrow{V}|=\sqrt{x_1^2+x_2^2+...+x_{10}^2}$。求有多少个四元组$1\leq i,j,k,l\leq n$满足$|\overrightarrow{V_i}-\overrightarrow{V_j}|=|\overrightarrow{V_k}-\overrightarrow{V_l}|$。
$n\leq10^5,\ 0\leq x_i\leq2$。

$Solution$
考虑$x\in[0,2]$的话如何转化$(x_i-x_j)^2$。将每个向量用一个$20$位二进制数$a$表示，即$x_i=0$，则$a$的第$2i-1$和$2i$位为$00$；$x_i=1$，第$2i-1$和$2i$位为$01$；$x_i=2$，第$2i-1$和$2i$位为$10$。
这样当$x_i-x_j$不同时，对应唯一的$a_i\ \mathbb{xor}\ a_j$的结果。所以我们计算$a_i\ \mathbb{xor}\ a_j$就能知道差的模长$|\overrightarrow{V_i}-\overrightarrow{V_j}|$了。
用$FWT$计算$a_i\ \mathbb{xor}\ a_j=b$的$(i,j)$有多少个，再把$b$转为模长，就行了。模长最大值是$40$。
复杂度$O(20\times2^{20})$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 998244353
#define inv2 499122177
#define Add(x,y) x+y>=mod?x+y-mod:x+y
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<20)+5,lim=1<<20,ref[]={0,1,4,1};

int A[N],B[50];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void FWT(int *a,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j; k<j+mid; ++k)
			{
				int x=a[k],y=a[k+mid];
				a[k]=Add(x,y), a[k+mid]=Add(x,mod-y);
				if(opt==-1) a[k]=1ll*a[k]*inv2%mod, a[k+mid]=1ll*a[k+mid]*inv2%mod;
			}
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i)
	{
		int a=0;
		for(int j=0; j<10; ++j)
			switch(read())
			{
				case 0: a<<=2; break;
				case 1: a<<=2, a|=1; break;//先左移再或。。
				case 2: a<<=2, a|=2; break;
			}
		++A[a];
	}
	FWT(A,1);
	for(int i=0; i<lim; ++i) A[i]=1ll*A[i]*A[i]%mod;
	FWT(A,-1);
	for(int i=0; i<lim; ++i)
	{
		if(!A[i]) continue;
		int res=0;
		for(int x=i; x; x>>=2) res+=ref[x&3];
		B[res]=Add(B[res],A[i]);
	}
	LL ans=0;
	for(int i=0; i<=40; ++i) ans+=1ll*B[i]*B[i]%mod;
	printf("%lld\n",ans%mod);

	return 0;
}
