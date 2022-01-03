/*
3476kb	11948ms
显然我们要求出$C(n,m)$为奇数的所有$(n,m)$。
有一个结论: $C(n,m)$是奇数时，有$n\&m==m$。
设$f[i]$为从$A[i]$开始能构成的序列数，那么有$f[i]=\sum f[j]$，其中$j$为在$i$后面且满足$A[i]\&A[j]==A[j]$的数。
(当然$f[i]$也可以表示以$A[i]$结尾构成的序列数，这样可以直接正序枚举，好像更好些。。)
$j$显然是$i$的二进制1的子集，可以。。反正以可行的复杂度枚举，只需要记录每个数的位置就可以得到答案。
因为是枚举子集，而且最大值为233333，所以复杂度为$O(3^{\log A})=O(3^{18})$。
结论的证明: 因为是$\mod 2$，所以考虑Lucas定理。
在$\mod 2$的情况下$C(n,m)$最后只会化成4种情况: $C(0,1),C(0,0),C(1,0),C(1,1)$,后三种情况都是1，$C(0,1)$不存在(0)，所以如果$C(n,m)\mod 2$为偶数，那么一定在Lucas的过程中出现了$C(0,1)$。
$\mod 2$的过程容易想到位运算。由$C(n,m)\mod 2=C(n%2,m%2)*C(n/2,m/2)=C(n&1,m&1)*C(n>>1,m>>1)$ 可知，若$C(n,m)$为奇数，那么$m$一定是$n$二进制1的子集。
很多人写的太神奇了。。不看了。
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
#define mod (1000000007)
const int N=220005,S=240000;

int n,A[N],f[N],pos[S];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int main()
{
	n=read();
	for(int i=1; i<=n; ++i) pos[A[i]=read()]=i;
//	for(int i=1; i<=n; ++i) f[i]=1;//先赋值为1，最后需要都减掉1，即长度为1的。
	long long res=0;
	for(int i=n; i; --i){
		long long tmp=1;//赋值为1.
		for(int j=(A[i]-1)&A[i]; j; j=(j-1)&A[i])//每次只减1然后取与。
			if(pos[j]>i) tmp+=f[pos[j]];//少取模优化效果比较明显吧。
		f[i]=(tmp%mod), res+=f[i]-1;
	}
	printf("%d",int(res%mod));

	return 0;
}
