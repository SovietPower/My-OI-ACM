/*
122404kb	1924ms
len(Ti)+len(Tj)可以直接算出来，每个小于n的长度会被计算n-1次。
$$\sum_{i=1}^n\sum_{j=i+1}^n i+j = (n-1)*\sum_{i=1}^n = (n-1)*\frac{n*(n+1)}{2}$$
**SAM：**求后缀的LCP，我们可以想到将字符串反转，求前缀的最长公共后缀。
parent树上每个叶子节点都对应一个前缀，两个节点间的最长公共后缀在它们的LCA处，长度为len[LCA]。
于是对于每个节点我们统计有多少对叶子节点的LCA为它。树形DP就可以了。
**SA：**LCP当然是看height了。枚举后缀，计算它与之前串所构成的LCP。
如果ht[i]>=ht[i-1]，那么它与之前串的LCP和i-1一样；否则ht[i]就是这部分的LCP长度。
用单调栈维护离i最近且ht[p]<=i的位置p，则f[i]=f[p]+(i-p)*ht[i]。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e6+5;

struct Suffix_Automaton
{
	int n,las,tot,fa[N],son[N][26],len[N],sz[N],A[N],tm[N];
	char s[N>>1];
	void Insert(int c)
	{
		int p=las,np=++tot;
		len[las=np]=len[p]+1, sz[np]=1;
		for(; p&&!son[p][c]; p=fa[p]) son[p][c]=np;
		if(!p) fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else
			{
				int nq=++tot; len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof son[q]);
				fa[nq]=fa[q], fa[q]=fa[np]=nq;
				for(; son[p][c]==q; p=fa[p]) son[p][c]=nq;
			}
		}
	}
	void Build()
	{
		las=tot=1;
		scanf("%s",s+1), n=strlen(s+1);
		std::reverse(s+1,s+1+n);
		for(int i=1; i<=n; ++i) Insert(s[i]-'a');
		for(int i=1; i<=tot; ++i) ++tm[len[i]];
		for(int i=1; i<=n; ++i) tm[i]+=tm[i-1];
		for(int i=1; i<=tot; ++i) A[tm[len[i]]--]=i;

		long long res=0;
		for(int i=tot,x=A[i],f; i; x=A[--i])
			f=fa[x], res+=1ll*sz[f]*sz[x]*len[f], sz[f]+=sz[x];
		printf("%lld\n",1ll*n*(n+1)/2*(n-1)-(res<<1));
	}
}sam;

int main()
{
	sam.Build();
	return 0;
}
