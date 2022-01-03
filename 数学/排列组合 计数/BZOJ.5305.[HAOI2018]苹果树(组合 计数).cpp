/*
16540kb	196ms
首先，$n=1$时有$2$个位置放叶子，$n=2$时有$3$个... 可知$n$个点的有标号二叉树有$n!$种。（一个二叉树的中序遍历是唯一的，有$n!$种，也可以得到这个结论）

$Sol1$
考虑对每条边两边的点集计算贡献。即设一条边一边有$size$个点，另一边有$n-size$个点，那么它的贡献是$size(n-size)$。
直接把边放到点上，枚举每个点$i$（边就是$i\to fa[i]$），再枚举$size_i$。$size_i$就是$i$子树的大小。
考虑此时的方案数。$i$子树和$i$子树外是独立的。
对于$i$子树，有$size_i!$种树的形态，而标号分配有$C_{n-i}^{size_i-1}$种方案（$i$子树内点的编号要$\geq i$）。所以$i$子树有$size_i!\times C_{n-i}^{size_i-1}$种。
对于$i$子树外部，首先构造出$i$个点的树有$i!$种方案。然后还有$n-i-size_i+1$个点需要放在$i$子树外的任意位置，方案数是$(i+1-2)(i+2-2)...(i+n-i-size_i+1-2)$。两个乘起来，就是$i(i-1)(n-size_i-1)!$。
那么答案就是$$\sum_{i=2}^n\sum_{size_i=1}^{n-i+1}size_i(n-size_i)size_i!\cdot C_{n-i}^{size_i-1}\cdot i(i-1)(n-size_i-1)!$$

$Sol2$
递推。考虑由枚举大小为$L,R$的两棵左右子树来得到$L+R+1$个点的树。那么知道深度就可以算两棵子树间的距离了。
令$f[i]$表示$i$个节点的树，所有$i!$种可能中，所有点深度的和（根节点深度为$1$）。
令$g[i]$表示$i$个节点的树，所有$i!$种可能中，所有点两两之间的距离的和。
转移的时候枚举左右子树的大小$L,R=i-L-1$，有$$\begin{aligned}f[i]&=i*i!+\sum_{L=0}^{i-1}C_{i-1}^L(f[L]*R!+f[R]*L!)\\g[i]&=\sum_{L=0}^{i-1}C_{i-1}^L(g[L]*R!+g[R]*L!+f[L]*R!*(R+1)+f[R]*L!*(L+1))\end{aligned}$$

这样$g[n]$就是答案啦。
*/
#include <cstdio>
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=2005;
const LL LIM=1ll<<61;

int C[N][N],fac[N],g[N];

int main()
{
	int n,mod; scanf("%d%d",&n,&mod);
	C[0][0]=fac[0]=fac[1]=1;
	for(int i=2; i<=n; ++i) fac[i]=1ll*i*fac[i-1]%mod;
	for(int i=1; i<=n; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j], Mod(C[i][j]);
	}
	for(int i=1; i<=n; ++i) g[i]=1ll*i*(n-i)*fac[n-i-1]%mod*fac[i]%mod;
	LL ans=0;
	for(int i=2; i<=n; ++i)
		for(int sz=n-i+1,tmp=i*(i-1); sz; --sz)
			if((ans+=1ll*C[n-i][sz-1]*g[sz]%mod*tmp)>=LIM) ans%=mod;
	printf("%lld\n",ans%mod);

	return 0;
}
