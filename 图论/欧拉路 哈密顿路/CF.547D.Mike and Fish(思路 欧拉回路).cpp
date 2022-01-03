/*
139ms	28400KB
$Description$
给定平面上n个点，将这些点染成红or蓝色，要求每行、每列红色点与蓝色点数量的差的绝对值<=1。输出方案(保证有解)。
$Solution$
将每个横坐标、纵坐标分别看做一个点，将每个点(x,y)拆成x(row)->y(column)的边 
这样我们可以将边染色，使得与每个点相连的两种颜色差<=1 
于是对于所有的欧拉回路，我们可以直接交替染色 
但是会有度数为奇数的点，这样的点一定有偶数个，我们对其两两配对连边，这样所有奇度数的点度数就都为偶数了 
对于每个连通块，选一个初始度数为奇数的点(若没有则任选度数为偶数的点)，求一条欧拉回路(若是奇度数点则应先走与配对的奇度数点相连的边)，将路径上的边交替染色即可 
正确性:  
对于一条欧拉回路，除起点外每个点相连的红边与蓝边数是相同的 
对于起点，欧拉回路的第一条边和最后一条边的颜色可能是相同的 
若起点初始度数为奇数，由于先走了与新连出的边，所以就算第一条和最后一条边的颜色相同也没关系 
(同色的话由于有影响的点在同行同列，一定连通，所以整个连通块只会额外多出一条边颜色不同)
若起点初始度数为偶数，则连通块是一个二分图，第一条和最后一条边的颜色一定不相同 
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=4e5+5,MAX=2e5;

int n,Enum,H[N],to[N<<1],nxt[N<<1],id[N<<1],dgr[N],top,sk[N],A[N];
char Ans[N];
bool vis[N<<1],v[N];//点和边的vis是不一样的啊！

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int i){
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, id[Enum]=i;
}
void DFS(int x)
{
	v[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[i])
		{
			vis[i]=vis[i^1]=1, H[x]=i;
			DFS(to[i]);
			sk[++top]=id[i], i=H[x];
		}
}

int main()
{
	n=read(); Enum=1;
	for(int x,y,i=1; i<=n; ++i)
		x=read(),y=read()+MAX,AddEdge(x,y,i),AddEdge(y,x,i);
	int cnt=0;
	for(int i=1; i<=MAX<<1; ++i)
		if(dgr[i]&1) A[++cnt]=i;
	for(int i=1; i<=cnt; i+=2)
		AddEdge(A[i],A[i+1],0),AddEdge(A[i+1],A[i],0);
	for(int i=1; i<=cnt; ++i)
		if(!v[A[i]])
		{
			DFS(A[i]);
			bool f=0;
			while(top)
				Ans[sk[top--]]=f?'r':'b',f^=1;
		}
	for(int i=1; i<=MAX<<1; ++i)
		if(!v[i])
		{
			DFS(i);
			bool f=0;
			while(top)
				Ans[sk[top--]]=f?'r':'b',f^=1;
		}
	Ans[n+1]='\0';
	printf("%s",Ans+1);

	return 0;
}
