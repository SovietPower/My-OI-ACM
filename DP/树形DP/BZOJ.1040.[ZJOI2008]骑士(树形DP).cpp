/*
40992kb	1876ms
不难看出矛盾关系可以构成一棵树，如果取一个节点，那么它的父节点就不能取，树形DP就行了。
这不是没有上司的舞会吗。。
但是漏了一种情况，即这个关系可能形成一个环(从n条边和样例能看出来)，且有多个连通块，每个连通块一定且仅在根节点处有一个环。
在环上选择一条边断开，把端点分别作为根节点dp一遍，取max就是该连通块的答案。最后所有连通块相加。
注意取max是取max{f[x][0]}，即不能选取当前的根节点，因为此时已经断开了，最优解可能是另一端点被选中的情况。这两个取max所有情况就都有了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int n,s1,s2,mark,val[N],Enum,H[N],nxt[N<<1],to[N<<1];
LL f[N][2];
bool vis[N];

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
void Find_Circle(int x,int fa)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa)
		{
			if(vis[to[i]])
				s1=x, s2=to[i], mark=i;
			else Find_Circle(to[i],x);
		}
}
void DFS(int x,int fa)
{
	f[x][0]=0, f[x][1]=val[x];
	for(int v,i=H[x]; i; i=nxt[i])
		if(to[i]!=fa && i!=mark && (i^1)!=mark)
		{
			DFS(v=to[i],x);
			f[x][0]+=std::max(f[v][0],f[v][1]);//两种情况都可以 别漏。。
			f[x][1]+=f[v][0];
		}
}

int main()
{
	n=read(),Enum=1;
	for(int i=1; i<=n; ++i) val[i]=read(),AddEdge(read(),i);
	LL res=0,tmp;
	for(int i=1; i<=n; ++i)
		if(!vis[i])
		{
			mark=0, Find_Circle(i,i);//s1->s2
//			if(mark)
//			{
				DFS(s1,s1), tmp=f[s1][0];
				DFS(s2,s2), tmp=std::max(tmp,f[s2][0]);
				res+=tmp;
//			}
//			else DFS(i,i), res+=std::max(f[i][0],f[i][1]);
		}
	printf("%lld",res);

	return 0;
}
