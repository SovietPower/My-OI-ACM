/*
8ms	4608KB
$Description$
有一个长为$L$的环，上面有$n$棵树，坐标分别为$a_i$。初始时在原点。
每次你可以选择顺时针或逆时针走到第一棵没有被烧掉的树，停在这个位置，然后烧掉这棵树。重复这一过程直到所有树都被烧掉。
求走的总路程最多可以是多少。
$n\leq2\times10^5,\ a_i,L\leq10^9$。

$Solution$
真的菜啊QAQ 当时连这个都不会

记顺时针走一次为$L$，逆时针走一次为$R$。
初步想法是$LRLRLR...$这样走。但显然有反例（比如两棵树分别在$1,\ L-1$）。
事实上用$LLLLRLR...$和$RRRLRLR...$，这两种走法就没问题了。（具体证明没有~~大概既然开始来回走了，就比继续往一个方向走更优吧？~~）
前缀和后缀和预处理一下，枚举刚开始~~反复横跳~~进行$LRLR...$的位置就可以了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
LL Solve(const int n,const int L)
{
	static LL pre[N],suf[N];
	for(int i=1; i<=n; ++i) pre[i]=pre[i-1]+A[i];
	for(int i=n; i; --i) suf[i]=suf[i+1]+L-A[i];
	LL ans=A[n];
	for(int i=1,p; i<n; ++i)
		p=i+((n-i)>>1), (n-i)&1 ? ans=std::max(ans,(suf[p+2]+pre[p]-pre[i]+A[i])*2+L-A[p+1]) : ans=std::max(ans,(suf[p+1]+pre[p-1]-pre[i]+A[i])*2+A[p]);
	return ans;
}

int main()
{
	const int L=read(),n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	LL ans=Solve(n,L);
	std::reverse(A+1,A+1+n);
	for(int i=1; i<=n; ++i) A[i]=L-A[i];
	ans=std::max(ans,Solve(n,L));
	printf("%lld\n",ans);

	return 0;
}
