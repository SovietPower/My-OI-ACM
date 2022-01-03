/*
124ms	16900KB
$Description$
给定一个$n\times m$的$01$矩阵，你可以选择一些行和一些列并将其中所有的$01$反转。求操作后最少剩下多少个$1$。
$n\leq20,m\leq10^5$。
$Solution$
$n$这么小，要想到一是可以状压状态，二是可以枚举选了哪些行。
发现在确定了选哪些行之后，每一列的选择是确定的（取变与不变后得到的状态中$1$较少的那个）。
那么假设$y$为这一列的最终状态（可以状压表示出来）,则这一列的答案为$B[y]=\min(y中0的个数,y中1的个数)$（$B[y]$可以预处理得到）。而使列的状态由$x$变为$y$，所需要反转的行为$x\ \mathbb{xor}\ y$。
状态相同的列显然可以合并。不妨令$A[x]$表示状态为$x$的列的个数。
那么假设最终选择反转的行为$s$，则$ans_s=\sum_{x\ \mathbb{xor}\ y=s}A[x]\times B[y]$。
异或卷积，$FWT$就行了。
复杂度$O(2^n\log 2^n)=O(2^nn)$。
~~另外运算时显然不会爆int。~~$FWT$时会爆int，但是开longlong就行了不需要取模。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 50000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<20)+5;

int col[100005];
LL A[N],B[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void FWT(LL *a,int lim,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j; k<j+mid; ++k)
			{
				LL x=a[k], y=a[k+mid];//LL!
				a[k]=x+y, a[k+mid]=x-y;
				if(opt==-1) a[k]>>=1, a[k+mid]>>=1;//这个还可以最后ans>>n。。
			}
}

int main()
{
	int n=read(),m=read(),lim=1<<n;
	for(int i=0; i<n; ++i)
	{
		register char c=gc(); while(!isdigit(c)) c=gc();
		col[0]|=c-'0'<<i;
		for(int j=1; j<m; ++j) col[j]|=gc()-'0'<<i;
	}
	for(int i=0; i<m; ++i) ++A[col[i]];//cnt
	for(int i=1; i<lim; ++i) B[i]=B[i>>1]+(i&1);//bitcount
	for(int i=1; i<lim; ++i) B[i]=std::min(B[i],n-B[i]);
	FWT(A,lim,1), FWT(B,lim,1);
	for(int i=0; i<lim; ++i) A[i]*=B[i];
	FWT(A,lim,-1);
	int ans=n*m;
	for(int i=0; i<lim; ++i) ans=std::min(ans,(int)A[i]);
	printf("%d\n",ans);

	return 0;
}
