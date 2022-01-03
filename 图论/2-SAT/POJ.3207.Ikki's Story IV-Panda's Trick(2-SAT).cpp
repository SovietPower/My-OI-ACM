/*
1816K	16MS
$Description$
一个圆上顺序排列0,1,...,n-1共n个点，给出m条线段，线段可以从里面连也可以从外面连，问是否能满足所有线段不相交 
$Solution$
把每条线段看做一个点，只有在圆外和在圆内两种情况，于是可以把线段拆成i,i'，分别表示两种情况 
对于端点相交的线段会产生矛盾 
若i不能与j相交，则: 
i在圆内 j就在圆外；i在圆外 j就在圆内 
j在圆内 i就在圆外；j在圆外 i就在圆内 
注意这个要双向判断 
边数一定要够 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2005,M=100005;

int n,m,st[505],ed[505],Enum,H[N],nxt[M<<1],to[M<<1],dfn[N],low[N],id,top,sk[N],cnt,bel[N];
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
void Tarjan(int x)
{
	dfn[x]=low[x]=++id, sk[++top]=x, ins[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!dfn[v=to[i]]) Tarjan(v), low[x]=std::min(low[x],low[v]);
		else if(ins[v]) low[x]=std::min(low[x],dfn[v]);
	if(dfn[x]==low[x])
	{
		++cnt;
		do{
			ins[sk[top]]=0, bel[sk[top--]]=cnt;
		}while(x!=sk[top+1]);
	}
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=m; ++i)
	{
		st[i]=read(),ed[i]=read();
		if(st[i]>ed[i]) std::swap(st[i],ed[i]);
	}
	for(int i=1; i<=m; ++i)
		for(int j=1; j<=m; ++j)
			if(i!=j && st[j]<st[i]&&st[i]<ed[j]&&ed[j]<ed[i])//不同的相交顺序就由都枚举一遍解决了 
				AddEdge(i*2-1,j*2), AddEdge(i*2,j*2-1), AddEdge(j*2-1,i*2), AddEdge(j*2,i*2-1);
	for(int i=1; i<=m<<1; ++i)
		if(!dfn[i]) Tarjan(i);
	bool f=1;
	for(int i=1; i<=m; ++i)
		if(bel[i*2-1]==bel[i<<1]) {f=0; break;}
	puts(f?"panda is telling the truth...":"the evil panda is lying again");

	return 0;
}
