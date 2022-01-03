/*
976kb	4808ms
以为裸点分治，但数据范围怎么这么小？快打完了发现不对。。
n^2做的话其实是个sb题。。
枚举每一个点为根，为了不重复计算，我们要求所求的三个点必须分别位于三棵子树上。
考虑当前前3棵子树深度为deep的点分别有a,b,c个，新增的子树深度为deep的点有d个，那么新加的答案为:
$$dab+dac+dbc=d[ab+(a+b)c]$$
同理第5棵子树同一深度的点数为e，新加答案:
$$...=e[ab+(a+b)c+(a+b+c)d]$$
那么第6棵子树新加的答案应为:
$$...=f[ab+(a+b)c+(a+b+c)d+(a+b+c+d)e]$$
(以下sz表示每棵子树中处于某一深度的点数)
于是我们可以求每棵子树某一深度的点数，每次答案先加上当前 $sz*[]里的式子$，再维护[]里的整个式子，即加上 $sz*先前的子树和$，再更新子树的和($a+b+c...+=sz$)。
更好的方式是直接从组合数的定义上理解，即答案加上当前子树乘上之前的子树中选两个的方案数，然后更新选两个的方案数，即 $当前子树sz*之前子树选一个的方案数$，再更新子树中选一个的方案数，就是加上sz.
加强版需要长链剖分？~~好像用处不大~~先不管了。
~~O(n)DP也不管了~~
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=5005;

int n,Enum,Maxd,H[N],nxt[N<<1],to[N<<1],c1[N],c2[N],sum[N];
long long Ans;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;	
}
void DFS(int x,int f,int d)
{
	++sum[d], Maxd=std::max(Maxd,d);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) DFS(to[i],x,d+1);
}

int main()
{
	n=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	long long Ans=0;
	for(int x=1; x<=n; ++x)
	{
		memset(c1,0,sizeof c1), memset(c2,0,sizeof c2);
		for(int i=H[x]; i; i=nxt[i])
		{
			Maxd=1, DFS(to[i],x,1);
			for(int j=1; j<=Maxd; ++j)//这么枚举复杂度也是ok的。
			{
				Ans+=c2[j]*sum[j], c2[j]+=c1[j]*sum[j], c1[j]+=sum[j],
				sum[j]=0;
			}
		}
	}
	printf("%lld",Ans);

	return 0;
}
