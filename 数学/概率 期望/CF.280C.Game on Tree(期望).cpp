/*
62ms	9872KB
$Description$
给你一棵有$n$个白点的有根树，每次随机选择一个点，将它和它的子树中所有点染黑。
问期望操作多少次后所有点都被染黑？
$Solution$
期望好玄啊。。(好吧是我太弱) 
因为概率具有可加性，一棵树可以分解为多棵子树，而子树分解的最终状态就是点，所以我们可以计算每个点的期望操作次数再求和，即$E(总操作次数)=E(每个点被选中操作次数)$。
这个期望操作次数是指作为白点被选中染黑的期望次数。
因为一个点祖先节点被染黑后，这个节点操作次数就为0了，所以得出一个点x的期望E(x)=1/dep[x].
直接DFS。。
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=1e5+5;

int n,Enum,H[N],nxt[N<<1],to[N<<1];
double Ans;

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
	Ans+=1.0/d;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) DFS(to[i],x,d+1);
}

int main()
{
	n=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	DFS(1,1,1);
	printf("%.10lf",Ans);

	return 0;
}
