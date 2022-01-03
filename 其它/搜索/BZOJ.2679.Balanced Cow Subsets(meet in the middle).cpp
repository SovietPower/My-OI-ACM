/*
7132kb	2584ms
$Description$
给定$n$个数$A_i$。求它有多少个子集，满足能被划分为两个和相等的集合。
$n\leq 20,1\leq A_i\leq10^8$。
$Solution$
显然我们要预处理哪些集合可以被划分为两个和相等的集合。每个元素三种状态，这样我们就可以得到一个$O(3^n)$的做法。。
显然不行啊，但是和相等这种东西可以折半啊！
将序列分成两半分开DFS。这样两个和相等的集合$S_1,S_2$中的元素可能会被分开。设$a$为$S_1$在前一半中序列的元素的和，$b$为$S_1$在后一半序列中的元素的和；$c,d$分别为$S_2$在前一半/后一半序列中元素的和。那么有$a+b=c+d\to a-c=d-b$。所以我们统计两半序列中哪些$a-c$相等的集合就可以了。
和为$a-c$的集合可能有多个，直接$Hash/map+vector$存一下有哪些集合就可以了（这题集合可以直接二进制状压）。
复杂度是不是还会被卡到$O(6^{\frac n2})$啊。。在SPOJ是T了，但能过BZOJ。
其实合并状态可以sort后线性合并，就快很多了。（不对啊，感觉复杂度差不多啊==，我hash写太丑了？）
当然这也不是正解，还有更快的，比如：https://blog.csdn.net/u014609452/article/details/51872702
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 20000000
typedef long long LL;
const int N=61005;//为啥60005在BZOJ上RE啊，自测可过。

int n,mid,cnt,A[23],Enum,H[(1<<20)+5],sum[N],nxt[N];
bool vis[(1<<20)+5];
struct Node
{
	int s,sum;
	bool operator <(const Node &x)const
	{
		return sum<x.sum;
	}
}rs[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int s,int Sum)
{
	sum[++Enum]=Sum, nxt[Enum]=H[s], H[s]=Enum;
}
void DFS1(int x,int s,int sum)
{
	if(x<0) {AE(s,sum); return;}
	DFS1(x-1,s,sum), DFS1(x-1,s|(1<<x),sum+A[x]), DFS1(x-1,s|(1<<x),sum-A[x]);
}
void DFS2(int x,int s,int sum)
{
	if(x==n) {rs[++cnt]=(Node){s,sum}; return;}
	DFS2(x+1,s,sum), DFS2(x+1,s|(1<<x),sum+A[x]), DFS2(x+1,s|(1<<x),sum-A[x]);
}

int main()
{
	static int lsum[N];
	n=read(),mid=n>>1;
	for(int i=0; i<n; ++i) A[i]=read();
	DFS1(mid-1,0,0), DFS2(mid,0,0);
	std::sort(rs+1,rs+1+cnt);
	for(int s=0,l=1<<mid; s<l; ++s)
	{
		int t=0;
		for(int i=H[s]; i; i=nxt[i]) lsum[++t]=sum[i];
		std::sort(lsum+1,lsum+1+t);
		for(int i=1,now=1; i<=cnt; ++i)
		{
			while(now<=t && lsum[now]<rs[i].sum) ++now;
			if(now>t) break;
			if(lsum[now]==rs[i].sum) vis[rs[i].s|s]=1;
		}
	}
	int ans=0;
	for(int i=1,l=1<<n; i<l; ++i) ans+=vis[i];//同一个集合会算重啊 
	printf("%d\n",ans);

	return 0;
}
