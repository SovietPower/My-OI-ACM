/*
546ms	89700KB
显然对于$d_{x,i}$，我们有$d_{x,i}=\sum_{v=son[x]}d_{v,i-1}$
*Dominant Indices*就是最大的$d_{x,i}$中下标最小的$i$。我们可以利用启发式合并求$d_x$。启发式合并一般的复杂度是$O(n\log n)$的，但在本题中，复杂度只与sz较小的点的深度有关，而不是点数。所以复杂度是$O(n)$的。
我们还需要将数组整体右移，以便插入一个$d_{x,0}=1$。可以用map($O(n\log n)$)，也可以用vector倒序存储，这样就是$O(n)$的了。
也可以直接用个大点的($O(n)$其实就够了)数组，每个点维护在数组中的位置。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e6+5;

int n,Enum,H[N],nxt[N<<1],to[N<<1],Ans[N],A[N],pos[N],len[N],mx[N],mxpos[N];

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
void Merge(int x,int y)//x<-y
{
	if(len[x]<len[y])
	{
		std::swap(pos[x],pos[y]), std::swap(len[x],len[y]), 
		std::swap(mx[x],mx[y]), std::swap(mxpos[x],mxpos[y]);
	}
	for(int i=0,ly=len[y],px=pos[x],py=pos[y]; i<ly; ++i)
	{
		A[px+i]+=A[py+i]; //A[px+i+1]+=A[py+i];
		if(A[px+i]>mx[x]) mx[x]=A[px+i], mxpos[x]=i;
		else if(A[px+i]==mx[x] && i<mxpos[x]) mxpos[x]=i;
	}
}
void DFS(int x,int f)
{
	A[pos[x]]=1, len[x]=1, mx[x]=1, mxpos[x]=0;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=f)
		{
			pos[v]=pos[x]+len[x]+1, DFS(v,x);//给v腾出一位，合并前将v右移一位。否则len[x]==len[v]时会重叠。。
			A[--pos[v]]=0, ++len[v], ++mxpos[v], Merge(x,v);
		}
	Ans[x]=mxpos[x];
}

int main()
{
	n=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	pos[1]=1, DFS(1,1);
	for(int i=1; i<=n; ++i) printf("%d\n",Ans[i]);

	return 0;
}
