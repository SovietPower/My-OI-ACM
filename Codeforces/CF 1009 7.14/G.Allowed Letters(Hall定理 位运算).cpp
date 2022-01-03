/*
62ms	400KB
$Description$
给定长为n、由小写字母a~f组成的字符串s。有m个限制，限制在$pos_i$处只能由某些字母组成($pos$两两不同)。
你可以任意交换原串两个字母的位置，问是否能得到满足限制的字符串，若能，输出满足限制的最小字典序的字符串。
$Solution$
有n个字符，每个字符可以放在某些位置，要求这些字符全部放置->完备匹配。
可以跑网络流，检查最大流是否等于n，连边比较好想。然后假设想要让i位置放字符c，如果原最大流不需要c->i这条边，那么可以；否则让这条边退流，容量-1，再检查最大流是否等于n。
如果决定了位置i放字符c，那么要使c->i这条边的容量-1.
没写，万一调不出来有点。。Tutorial里说复杂度$O(n*2^A*A^2)$(A为字符集大小)，不知道$2^A$是为什么。。

可以考虑Hall定理。对于任意一个字符的子集，其中字符个数要<=能够匹配其中字符的位置个数。
这样的话对于同一种字符，显然只需要检验包含它最多的子集（位置数不会变）。所以我们要检查的子集只有$2^A=64$个(A为字符集大小)。
任意子集包含字符的个数sum可以$O(A*2^A)$或$O(2^A)$算。对于(只要)能够匹配某子集s中任意字符 的位置数我们可以去算：位置总数-只能匹配除s中字符外的位置数。
除s中字符外的子集可以表示为2^A-1-s，预处理其包含的所有子集的位置数即可，记为f[]。
如果现在要确定i位置放什么，那要先减掉i对f的贡献，即枚举所有包括 位置i可放字符子集 的子集，依次-1。要放某字符首先要能放，然后数量-1，再Check就行了。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define lb(i) (i&-i)
const int N=1e5+7;

int n,num[7],can[N],sum[69],f[69],bit[69];
char s[N],tmp[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool Check()
{
	for(int i=1; i<64; ++i)
	{
		sum[i]=sum[i^lb(i)]+num[bit[lb(i)]];
		if(sum[i]>f[63]/*not n，or n也-1*/-f[63-i]) return 0;
	}
	return 1;
}

int main()
{
	scanf("%s",s+1), n=strlen(s+1);
	for(int i=1; i<=n; ++i) can[i]=63, ++num[s[i]-'a'];
	for(int m=read(),p; m--; )
	{
		can[p=read()]=0, scanf("%s",tmp+1);
		for(int j=1,l=strlen(tmp+1); j<=l; ++j)
			can[p]|=1<<tmp[j]-'a';
	}
	for(int i=1; i<=n; ++i) ++f[can[i]];
	for(int i=0; i<6; ++i)//求其包含的所有子集 先枚举i！
		for(int j=1; j<64; ++j)
			if(j>>i & 1)
				f[j]+=f[j^(1<<i)];
	for(int i=0; i<6; ++i) bit[1<<i]=i;
	if(!Check()) return puts("Impossible"),0;
	for(int i=1; i<=n; ++i)
	{
		for(int s=can[i]; s<=63; s=(s+1)|can[i]) --f[s];
		for(int j=0; j<6; ++j)
		{
			if(!(can[i]>>j&1)) continue;
			--num[j];
			if(Check()) {putchar(j+'a'); break;}
			++num[j];
		}
	}
	return 0;
}
