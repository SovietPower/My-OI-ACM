/*
832kb	64ms
$Description$
求一个子集，满足其元素下标异或和不为0，且价值和最大。
$Solution$
按价值从大到小依次插入线性基，这样最后得到的集合就是价值和最大的了。
贪心策略简单证明：假设当前选取的集合S价值为{v1,v2,...,vn}，标号为{id1,id2,...,idn}。所有物品中价值最大的为vMax(idMax)，且当前集合中不包含vMax.
那么vMax一定可以替换掉S中的某个元素，使得价值和更大。
如果不能直接插入vMax，说明S∪{1}变得线性相关了，即S中一定存在一个子集，其下标的Xor和等于idMax。
即$$ id[x1]^id[x2]^...^id[xn]=id[Max] $$
然后id[Max]可以把任意一个元素替换掉，假设是x1，那么两边同时异或id[Max]^id[x1]：$$ id[Max]^id[x2]^...^id[xn]=id[x1] $$
这样就可以把id[x1]线性表示出来。而S中如果不加id[x1]的话是一定表示不出id[x1]的，因为S中异或和不为0(左边异或掉id[x1]是不等于id[x1]的)。
所以替换后的线性基和之前是等价的。
写x&(1ll<<i)的话别忘了1ll。(虽然好像没影响)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1005;

LL base[69];
struct Node{
	LL id; int val;
	bool operator <(const Node &x)const{
		return val>x.val;
	}
}A[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i].id=read(), A[i].val=read();
	std::sort(A+1,A+1+n);
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		LL now=A[i].id;
		for(int j=60; ~j; --j)
			if(now&(1ll<<j))
				if(base[j]) now^=base[j];
				else {base[j]=now; break;}
		if(now) ans+=A[i].val;
	}
	printf("%d\n",ans);

	return 0;
}
