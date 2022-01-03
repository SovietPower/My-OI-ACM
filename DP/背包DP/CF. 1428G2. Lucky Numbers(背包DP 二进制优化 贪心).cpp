/*
295ms	7800KB
$Description$
数$x$的价值定义为：$x$十进制表示中第$i$位为$3$则该位价值为$F_i$，该位为$6$价值为$2F_i$，为$9$价值为$3F_i$，否则为$0$，然后所有位上价值相加。
给定$K$。$Q$次询问，每次询问给定$n$，求满足$K$个数的和为$n$情况下，这$K$个数的最大价值和。
$n,K\leq 999999,q\leq 10^5$。
$Solution$
假如$K$个数的所有位上只有$0,3,6,9$，那么每一位都可以看作 总数为$3K$、体积为$3\times10^i$、价值为$F_i$的物品，就是$6$个物品、容量为$n$的多重背包。
那么考虑怎么让尽可能多的数位上是$0,3,6,9$。
求和时每位是独立的，对于某一位，如果有两个数该位分别是$a,b$而不是$0,3,6,9$，则若$a+b\leq 9$，那么可以将$a,b$换成$0,a+b$；否则$a+b>9$则可以将$a,b$换成$9,a+b-9$。
所以对于每一位，可以满足最优情况下只有一个数该位不为$0,3,6,9$。将这些不为$0,3,6,9$的位放到一个数上，就满足$K-1$个数的所有位上为$0,3,6,9$，剩下一个数任意。
像最上面一样，对每位$3(K-1)$个物品做二进制优化多重背包，然后加上剩下的一个数就ok。
复杂度$O(6m\log K)$。
细节：预处理一下，先把单独的那个数价值求出来，再做背包。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e6+5,INF=1e6;
const LL V[]={0,0,0,1,0,0,2,0,0,3};

int F[10];
LL f[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void Upd(int v,LL val)
{
	for(int i=INF-1; i>=v; --i) f[i]=std::max(f[i],f[i-v]+val);
}
void Update(int num,int v,int val)
{
	num=std::min(num,INF/v);
	for(int x=1; x<num; x<<=1) Upd(x*v,1ll*x*val), num-=x;
	Upd(num*v,1ll*num*val);
}

int main()
{
	int K=read();
	for(int i=0; i<=5; ++i) F[i]=read();
	for(int i=1,pw=1,las=1,bit=-1; i<INF; ++i)
		i==pw&&(las=pw,pw*=10,++bit), f[i]=f[i%las]+V[i/las]*F[bit];
	for(int i=0,pw=3; i<=5; ++i,pw*=10) Update(3*(K-1),pw,F[i]);

	for(int Q=read(); Q--; printf("%lld\n",f[read()]));

	return 0;
}
