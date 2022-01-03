/*
8760kb	192ms
题意：给定仙人掌图，边权为1，求其直径。
类似求树的直径，可以用(类似)树形DP求每个点其子树(在仙人掌上就是诱导子图)最长链、次长链，用每个点子节点不同子树的 max{最长链}+max{次长链} 更新答案。(不需要存次长链，求解过程中先更新ans，然后再更新最长链即可)
设f[i]为点i的诱导子图中最长链的长度。
对于环，我们找一个环上dep[]最小的点x代表这个环 看做一个点(dep为按DFS顺序更新的)，求出f[x]，环以外的部分像树一样直接做就可以。
对于环的处理：f[x]比较显然，f[x]=max{f[v]+dis(x,v)}，v为其环上一点，dis(x,v)为x,v在环上的最小距离。
环上如何更新答案？把环上所有点都拿出来，ans=max{f[u]+f[v]+dis(u,v)}。
u,v是环上的点，按顺序编号，dis(u,v)=v-u(v-u<=len/2)，那么ans可以写成 max{f[u]-u+f[v]+v}。固定v，因为u是单增的，所以之前最大的f[u]-u在后面也是最大的，可以用单调队列维护。
dis()是环上最小距离，所以v-u不能超过 环长/2。因为是个环，所以把它拆成一个3/2*len的序列更新ans。
之后用f[v]+dis(x,v)更新f[x]。
扫一遍所有的环，总共复杂度是$O(m)$。

总结：Tarjan，对于不在同一环上的点，用f[x]+f[v]+1更新ans，再用f[v]更新f[x]；对于其它的点，像上面那样取出环单调队列处理。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e4+5,M=N<<2;//边数。。大概最多2n条？

int n,m,Ans,Enum,H[N],to[M],nxt[M],dfn[N],low[N],id,fa[N],dep[N],f[N],q[N],A[N<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DP(int x,int ed)
{
	int n=dep[ed]-dep[x]+1;//length
	for(int i=n; i; --i) A[i]=f[ed], ed=fa[ed];
	int n2=n+(n>>1);//能同时更新别的的最多只有n/2个点，所以只需要3/2*n 
	for(int i=n+1; i<=n2; ++i) A[i]=A[i-n];
	int h=1,t=1; q[1]=1;
	for(int i=2; i<=n2; ++i)//i,q[]是点，拿出来的A[]是f[]！
	{
		while(h<t && i-q[h]>(n>>1)) ++h;
		Ans=std::max(Ans,A[q[h]]-q[h]+A[i]+i);
		while(h<=t && A[q[t]]-q[t]<=A[i]-i) --t;//注意这个比较是<，因为更新队首时不是根据值的大小，而是限制条件(<=竟然有90...) 
		q[++t]=i;
	}
	for(int i=2; i<=n; ++i)
		f[x]=std::max(f[x],A[i]+std::min(i-1,n-i+1));
}
void DFS(int x)
{
	dfn[x]=low[x]=++id;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			if(!dfn[v])
				fa[v]=x, dep[v]=dep[x]+1, DFS(v), low[x]=std::min(low[x],low[v]);
			if(low[v]>dfn[x])//不是环 
				Ans=std::max(Ans,f[x]+f[v]+1), f[x]=std::max(f[x],f[v]+1);
			low[x]=std::min(low[x],dfn[v]);//无向图，就不需要什么在栈中了 //只需判环，所以和下一行写法一样 
//			low[x]=std::min(low[x],low[v]);
		}
	for(int i=H[x]; i; i=nxt[i])
		if(fa[to[i]]!=x&&dfn[to[i]]>dfn[x]) DP(x,to[i]);//找环的另一个端点 
		//端点是后访问的点，而不只是&&to[i]!=fa[x]！(当x同时在两个环上时)能找到之前的环和x之后的环，但x不代表(没必要)之前访问的环，这样找环还麻烦。。不是沿to[i]的fa到x。
}

int main()
{
	n=read(),m=read();
	int num,u,v;
	while(m--){
		num=read()-1, u=read();
		while(num--) v=read(),AddEdge(u,v),u=v;
	}
	DFS(1);
	printf("%d",Ans);

	return 0;
}
