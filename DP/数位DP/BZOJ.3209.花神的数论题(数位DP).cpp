/*
852kb	84ms
$Description$
设$sum_i$表示$i$的二进制表示中$1$的个数，求$\prod_{i=1}^nsum_imod\ 10000007$。$n\leq 10^{18}$。
$Solution$
因为$n$的二进制有$logn$位，所以我们考虑枚举x，求满足$sum_i=x$的$i$的个数，然后就可以快速幂解决了。
求个数用数位DP。
*/
#include <cstdio>
#include <cstring>
#define mod (10000007)
typedef long long LL;
const int N=60;

LL n,A[N],f[N][N];
bool vis[N][N];

LL FP(LL x,LL k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}
LL DFS(int pos,int cnt,bool lim)
{
	if(cnt<0||pos<cnt) return 0;
	if(!pos) return !cnt;
	if(!lim && vis[pos][cnt]) return f[pos][cnt];
	int up=lim?A[pos]:1; LL res=0;
	for(int i=0; i<=up; ++i)
		res+=DFS(pos-1,cnt-i,i==up&&lim);
	if(!lim) vis[pos][cnt]=1,f[pos][cnt]=res;
	return res;
}

int main()
{
	scanf("%lld",&n);
	for(A[0]=0; n; n>>=1) A[++A[0]]=n&1;
	LL res=1ll;
	for(int i=1; i<=A[0]; ++i)
		(res*=FP(i,DFS(A[0],i,1)))%=mod;
	printf("%lld",res);

	return 0;
}
