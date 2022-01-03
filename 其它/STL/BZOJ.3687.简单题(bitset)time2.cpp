/*
1484kb	2660ms
$Description$
求$n$个数所有子集算术和的异或和。所有数的和$<=2*10^6$。
$Solution$
假设之前的数算术和为s1,s2,...（异或和为s1^s2^...）。
那么我们加入ai，之前的子集和要么不变要么加上ai，即s1,s2,...,s1^ai,s2^ai,...。那么当前异或和为(s1^s2^...)^((s1+ai)^(s2+ai)^...)。
设f[i]表示和为i的子集的出现次数，那么f[i]+=f[i-ai]。
好吧扯了半天就是个背包。我们算和为i的子集出现多少次。因为只需要判断是奇数次还是偶数次，可以用xor代替加。
f[i]^=f[i-ai]，即 f数组的每个位置异或上f数组左移ai后的每个位置 得到的数组。用bitset就好了。
*/
#include <cstdio>
#include <bitset>
#include <algorithm>
const int N=2e6+3;

std::bitset<N> f;

int main()
{
//	f.reset();
	int n,sum=0; scanf("%d",&n);
	f[0]=1;
	for(int x; n--; scanf("%d",&x), f^=f<<x, sum+=x);
	int ans=0;
	for(int i=1; i<=sum; ++i) if(f[i]) ans^=i;//if快好多...(700ms) 1很多吧?
	//ans^=f[i]?i:0 也比 f[i]&&(ans^=i) 快。异或运算速度很快的原因吧？
	printf("%d\n",ans);

	return 0;
}
