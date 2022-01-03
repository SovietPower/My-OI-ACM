/*
46ms	1900KB
$Description$
给定一个长为$n$的足迹序列（只包含$L,R$两种字符），你需要$LRLRLR...$这样交替在$L$和$R$上走（第一步可以选择$L$也可以选$R$）。当你在$L$时，下一步可以走到任意一个没走过的$R$；在$R$时，下一步可以走到任意一个没走过的$L$。求走完这个$L,R$序列最少需要往回走几次，并输出方案（往回走是指从位置$i$走到位置$j$，$j\lt i$）。保证存在一组可行方案。
$n\leq10^5$。
$Solution$
首先$L,R$数量差大于$1$无解。
如果我们需要往回走$k$次，那么我们可以将序列分成$k+1$个分别合法的子序列。
反过来，如果我们能将序列分成$k$个合法的子序列，小于往回走的次数是不是一定小于$k$？
考虑能否证明。我们将序列分成$LL,RR,LR,RL$四种合法的子序列（第一个字符表示序列开始是什么，第二个字符表示序列末尾是什么，因为只需要关心首尾字符），假设四种子序列分别有$a,b,c,d$个。首先有$|a-b|\leq1$。
然后我们可以用不超过$a+b-1$步将所有$LL,RR$合并成一个序列，这个序列可能是四种中的任意一种。
还可以用不超过$c-1$步将所有$LR$合并成一个$LR$。对$RL$同理。这样我们就得到了一个$LR$和一个$RL$子序列。
如果把其中一个子序列的最后一个字符给另一个，就可以变成一个$LL$和一个$RR$，且不会增加次数。
那么不论刚开始$LL,RR$合并出的子序列是哪种，都可以用不超过两步拼接上剩下的两个子序列。
这样最多使用$a+b-1+c-1+d-1+2=k-1$步。这样就证明了，如果我们能能将序列划分成$k$个合法子序列，一定可以构造方案使得最多往回走$k-1$次。（可是我还是觉得有点迷...）

现在的问题是怎么讲序列划分成尽量少的合法子序列。
我们发现可以跑最小路径覆盖（每个$L/R$向它后面所有$R/L$连边，$n-最大匹配数$就是答案）（图在[官方题解](http://codeforces.com/blog/entry/20368)里有）。
但还可以发现这个匹配实际上可以直接贪心，每个字符选它能匹配的点中最靠前的匹配即可。因为一定可以调整最大匹配使得满足这种贪心。
那么复杂度就是$O(n)$的了。

具体做的时候，可以拿个栈模拟一下拼接...（菜到不会写.jpg）
*/
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define AE(u,v) nxt[u]=v, pre[v]=u
typedef long long LL;
const int N=1e5+5;

int top,pre[N],nxt[N];
std::queue<int> q[2];
char s[N];
struct Node
{
	int l,r;
}sk[N];

bool Maintain()
{
	if(top<=1) return 0;
	Node a=sk[top],b=sk[top-1];
	if(s[a.r]!=s[b.l])
	{
		AE(a.r,b.l), sk[--top]=(Node){a.l,b.r};
		return 1;
	}
	if(s[a.l]!=s[b.r])
	{
		AE(b.r,a.l), sk[--top]=(Node){b.l,a.r};
		return 1;
	}
	if(s[a.l]!=s[b.l])//LR RL
	{
		if(a.r>b.r) std::swap(a,b);
		int p=pre[b.r];
		AE(a.r,b.r), AE(b.r,b.l), nxt[p]=0, sk[--top]=(Node){a.l,p};
		return 1;
	}
	return 0;
}

int main()
{
	scanf("%s",s+1);
	const int n=strlen(s+1);
	for(int i=1,c; i<=n; q[c^1].push(i++))
		if(!q[c=s[i]=='L'].empty()) AE(q[c].front(),i), q[c].pop();
	int ans=0;
	for(int i=1; i<=n; ++i)
		if(!pre[i])
		{
			++ans;
			int p=i; while(nxt[p]) p=nxt[p];
			sk[++top]=(Node){i,p};
			while(Maintain());
		}
	printf("%d\n",ans-1);
	for(int x=sk[1].l; x; x=nxt[x]) printf("%d ",x);

	return 0;
}
