/*
31ms	0KB
$Description$
求有多少个集合满足对异或封闭，且集合中的最大元素不超过$K$。
$K\leq 10^9$。
$Solution$
这个集合就是对异或封闭的线性空间。
将任一组基化简成 简化的阶梯形矩阵 形式后，基与线性空间一一对应。
所以线性空间的计数可以考虑基的计数（也就是异或空间里的线性基）。

线性空间的最大元素，就是化简后的基中所有元素的异或和（最高位一定取）。
所以求**异或和$\leq K$且满足简化阶梯形矩阵形式**（基中每个元素的第一个非零元素位置处其它元素在该处为$0$）的基的个数即可。

直接数位DP，需要记：当前位$i$、当前基中已含有多少个元素$j$、是否处于上界。
处于上界时：
如果令当前位为$0$，则该位不新建一个元素，且方案数为$2^{j-1}$（保证前$j$个元素在该位异或为$0$）；
如果令当前位为$1$，若该位新建元素，则方案数为$1$；若该位不新建元素，则方案数为$2^{j-1}$（保证前$j$个元素在该位异或为$1$）。

**PS：**要注意和常规记忆化数位DP不同的是，处于上界时的情况并不是只有$1$种（当前位放$1$不只可以通过在该位新建一个元素实现），所以 是否处于上界 这一维必须记忆化。
*/
#include <bits/stdc++.h>
#define pc putchar
#define mod 1000000007
typedef long long LL;
const int N=50;

int A[N],f[N][N][2];
LL pw[N];

int DFS(int bit,int cnt,bool lim)
{
	if(~f[bit][cnt][lim]) return f[bit][cnt][lim];
	if(!bit) return 1;
	LL res=0;
	if(!lim) res=DFS(bit-1,cnt+1,0)+pw[cnt]*DFS(bit-1,cnt,0);
	else
		res=(cnt?pw[cnt-1]:1ll)*DFS(bit-1,cnt,!A[bit])+ //令该位为0 
			(A[bit] ? DFS(bit-1,cnt+1,1)+(cnt?pw[cnt-1]:0ll)*DFS(bit-1,cnt,1) : 0); //令该位为1 
	res%=mod;
	return f[bit][cnt][lim]=res;
}

int main()
{
	int K,bit=0; scanf("%d",&K);
	while(K) A[++bit]=K&1, K>>=1;
	pw[0]=1;
	for(int i=1; i<=bit; ++i) pw[i]=pw[i-1]<<1;

	memset(f,0xff,sizeof f);
	printf("%d\n",DFS(bit,0,1));

	return 0;
}
