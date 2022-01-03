/*
1372ms	300KB
$Description$
给你一个擦去了部分左括号和全部右括号的括号序列，括号有25种，用除x之外的小写字母a~z表示。求有多少种合法的括号序列。答案对4294967296取模。
合法序列不能相交，如()[],([])是合法序列，而([)]是不合法的。
$Solution$
很重要的一点是，如果当前可以放右括号，那么方案是唯一的(不能相交)。
假设只有一种括号。
用f[i][j]表示1~i，还有j个左括号未匹配的方案数。根据当前是什么转移即可。复杂度O(n^2)。
空间可以压成O(n)。考虑优化枚举范围，但是j的下界是0/1，上界是min(i,n/2)，没啥好优化的。
只能尝试换种状态表示，f[i][j]表示1~i，已经填了j个右括号的方案数。
则若i+1 为/可以放 左括号，f[i+1][j] =/+= f[i][j]；若i+1可以放右括号，则f[i+1][j+1] += f[i][j]。
这样只有一种括号的答案是f[n][n/2]。假设原串有m个左括号，则25种括号的答案为$25^{n/2-m}*f[n][n/2]$(右括号确定，只需看左括号方案)。
j的下界是max(1,i-n/2)，上界可以按i/2算。平摊复杂度不知道，但跑得很快。
对4294967296=2^32取模相当于unsigned int自然溢出。
*/
#include <cstdio>
#include <algorithm>
typedef unsigned int uint;
const int N=1e5+5;

char s[N];//用static会慢么 不应该啊。。
uint f[N];

int main()
{
	int n; scanf("%d",&n);
	if(n&1) return putchar('0'),0;
	scanf("%s",s+1);

	f[0]=1; int m=0, n2=n>>1;
	for(int i=1; i<=n; ++i)
		if(s[i]=='?')
			for(int j=i>>1,lim=std::max(1,i-n2); j>=lim; --j)
				f[j]+=f[j-1];
		else ++m;
	if(n2<m) return putchar('0'),0;
	for(int i=n2-m; i--; ) f[n2]*=25;
	printf("%u",f[n2]);

	return 0;
}
