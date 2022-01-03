/*
3272ms	68628K / 69284kb	8496ms
首先询问都是求，向左走的最短路。
$f[i][j]$表示从$i$走到$j$最少需要多少步。表示这样只会$O(n^2\log n)$的= =~~但是感觉能卡过$70$分。~~

注意到从$i$出发，走$j$步能到达的点都是一段一段的。所以不妨令$f[i][j]$表示，从$i$出发，走$j$步能到达的最左边的是什么。那么$f[i][j+1]=\min\limits_{k=f[i][j]}^{i-1}L[k]$。
但是我们还没有考虑向右走的情况。可以发现一条路径最多只会向右走一次。
那么判一下就好惹。这样就可以$O(n^2)$啦。

注意到这一过程实际可以倍增：$f[i][j]$表示，从$i$出发，走$2^j$步最左可以到哪。但是还要考虑第一步向右走的情况，所以不妨直接令它表示，$i\sim n$这些点走$2^j$步最左可以到哪。
记$Calc(i,p)$表示，从$i$分别走到$p\sim i$所有点总共需要走多远。把询问$[l,r]$拆成$Calc(i,l)-Calc(i,r+1)$。
那么再维护一个$sum[i][j]$表示，从$i$出发，分别走到$f[i][j]\sim i$总共需要走多远。那么$sum[i][j]=sum[i][j-1]+sum[f[i][j-1]][j-1]+(f[i][j]-f[i][j-1])\times2^{j-1}$。

具体$Calc$的时候，关于向右走一步的处理，不妨直接让$i$先向左走一步走到$L[i]$。这样$L[i]$左边的部分都有可能需要$i$向右走，但是这正好符合$f$的定义，同时我们已经跳了一步也可以看作向右跳了一步。
注意维护一个变量$tot$表示之前一共跳过了多少距离。

还有[主席树的做法]，我不写惹qwq ~~懒~~。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BIT 18
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int L[N],f[BIT+1][N];
LL sum[BIT+1][N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Gcd(int a,int b)
{
	return b?Gcd(b,a%b):a;
}
LL Calc(int l,int p,const int bit)
{
	if(L[p]<=l) return p-l;
	LL ans=p-L[p],tot=1; p=L[p];
	for(int i=bit; ~i; --i)
		if(f[i][p]>=l) ans+=sum[i][p]+(p-f[i][p])*tot, tot+=1<<i, p=f[i][p];
	return ans+(p-l)*(tot+1);//(r-l)*tot+r-l
}

int main()
{
	const int n=read(); int bit=23;
	while(1<<bit>n) --bit;
	for(int i=2; i<=n; ++i) L[i]=read();
	f[0][n]=L[n];
	for(int i=n-1; i; --i) f[0][i]=std::min(f[0][i+1],L[i]), sum[0][i]=i-f[0][i];
	for(int j=1; j<=bit; ++j)
	{
		LL t=1ll<<j-1;
		for(int i=1; i<=n; ++i)
			f[j][i]=f[j-1][f[j-1][i]], sum[j][i]=sum[j-1][i]+sum[j-1][f[j-1][i]]+(f[j-1][i]-f[j][i])*t;
	}
	for(int Q=read(); Q--; )
	{
		int l=read(),r=read(),x=read(),b=r-l+1;
		LL a=Calc(l,x,bit)-Calc(r+1,x,bit); int g=Gcd(b,a%b);
		printf("%lld/%d\n",a/g,b/g);
	}

	return 0;
}
