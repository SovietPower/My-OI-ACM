/*
150836kb	18488ms
$Description$
有$k$个国家，$n$个城市分属于不同国家，$m$条边。要求每个国家有恰好一个城市作为首都，每条边至少有一个端点是首都。
求是否有解。
$n,m,k\leq 10^6$。
$Solution$
每个城市要么建首都要么不建，考虑2-SAT 
这样一个国家内城市两两连边是很显然的，但是边数为O(n^2) 
每个国家中仅有一个建首都，考虑新建前缀S[i]=1/0这2n个点表示[1,i]中建了/没建首都 
现在考虑这些限制:(A[i]=1/0表示i城市建/不建) 
0.若A[i]=1，则S[i]=1；若S[i]=0，则A[i]=0(对于i自己) 
1.若A[i]=1，则S[i-1]=0；若S[i-1]=1，则A[i]=0 (一个国家一个首都的限制)(前者由A[i]->A[i-1]'是多余的，连到S_{i-1}'自然会连到A_{i-1}') 
2.若S[i-1]=1，则S[i]=1；若S[i]=0，则S[i-1]=0 (前缀关系) 
后缀优化的原理是一样的，不过这题并不需要 
再加上边端点的限制就可以了 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=4e6+5,M=N<<1;

int n,m,k,Enum,H[N],nxt[M],to[M],id,low[N],dfn[N],sk[N],top,cnt,bel[N];
bool ins[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
inline void Tarjan(int x)
{
	dfn[x]=low[x]=++id, ins[x]=1, sk[++top]=x;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!dfn[v=to[i]]) Tarjan(v),low[x]=std::min(low[x],low[v]);
		else if(ins[v]) low[x]=std::min(low[x],dfn[v]);
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			ins[sk[top]]=0, bel[sk[top]]=cnt;
		}while(x!=sk[top--]);
	}
}

int main()
{
	n=read(),m=read(),k=read();
	for(int u,v,i=1; i<=m; ++i)
		u=read(),v=read(),AddEdge(u+n,v),AddEdge(v+n,u);
	for(int i=1; i<=n; ++i) AddEdge(i,2*n+i),AddEdge(3*n+i,i+n);
	for(int num,now,las,i=1; i<=k; ++i)
	{
		num=read(), las=read();
		for(int j=2; j<=num; ++j,las=now)
		{
			now=read(),
			AddEdge(2*n+las,2*n+now), AddEdge(3*n+now,3*n+las),
			AddEdge(now,3*n+las), AddEdge(2*n+las,now+n);
		}
	}
	for(int i=1; i<=n<<2; ++i)
		if(!dfn[i]) Tarjan(i);
	for(int i=1; i<=n; ++i)
		if(bel[i]==bel[i+n]) {printf("NIE"); return 0;}
	for(int i=n<<1|1; i<=3*n; ++i)
		if(bel[i]==bel[i+n]) {printf("NIE"); return 0;}
	printf("TAK");

	return 0;
}
//150832kb	19404ms
//{//优化编号方式 注意这样编号要-1 -> 于是这样更慢了 
//	for(int u,v,i=1; i<=m; ++i)
//		u=read()-1,v=read()-1,AddEdge(u<<1|1,v<<1),AddEdge(v<<1|1,u<<1);
//	for(int i=0; i<n; ++i) AddEdge(i<<1,i+n<<1),AddEdge(i+n<<1|1,i<<1|1);
//	for(int num,now,las,i=1; i<=k; ++i)
//	{
//		num=read(), las=read()-1;
//		for(int j=2; j<=num; las=now,++j)
//		{
//			now=read()-1,
//			AddEdge(las+n<<1,now+n<<1), AddEdge(now+n<<1|1,las+n<<1|1),
//			AddEdge(now<<1,las+n<<1|1), AddEdge(las+n<<1,now<<1|1);
//		}
//	}
//	n<<=2;
//	for(int i=0; i<n; ++i)
//		if(!dfn[i]) Tarjan(i);
//	for(int i=0; i<n; i+=2)
//		if(bel[i]==bel[i^1]) {printf("NIE"); return 0;}
//	printf("TAK");
//}
