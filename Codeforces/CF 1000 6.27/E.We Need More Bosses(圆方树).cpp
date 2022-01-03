/*
93ms	38500KB
$Description$
����һ������ͼ���������ѡ������S,T(S��T)��Ϊ����յ㣬��vΪS->T���뾭���ıߵ�������������v��
(such that����ʱsuch���Ǹ����ʰ�)
$Solution$
Բ����������������Բ��֮��ı߱�ȨΪ0��Բ��֮��ı߱�ȨΪ1����ֱ����
������Բ����ٽ����㡣��
�ٷ���⣺����йصı�һ�����š�������֮��û���ŵĵ�ϲ�Ϊ1���㣬����һ�����������������ֱ���������������ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=3e5+5;

int n,m,tot,Index,dfn[N],low[N],Max,V,top,sk[N];
struct Edge
{
	int Enum,H[N<<1],nxt[N<<2],to[N<<2],val[N<<2];//Square point...
	inline void AddEdge(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
	inline void AddTreeEdge(int u,int v,int w)
	{
		to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], val[Enum]=w, H[v]=Enum;
	}
}G,T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Tarjan(int x,int f)
{
	low[x]=dfn[x]=++Index, sk[++top]=x;
	for(int i=G.H[x],v; i; i=G.nxt[i])
		if(!dfn[v=G.to[i]])
		{
			Tarjan(v,x), low[x]=std::min(low[x],low[v]);
			if(dfn[x]==low[v])
			{
				T.AddTreeEdge(x,++tot,0);
				do{
					T.AddTreeEdge(tot,sk[top--],0);
				}while(sk[top+1]!=v);
			}
			else if(dfn[x]<low[v]) T.AddTreeEdge(x,v,1), --top;//��ջ��
		}
		else if(v!=f) low[x]=std::min(low[x],dfn[v]);
}
void DFS(int x,int f,int d)
{
	if(d>Max) Max=d, V=x;
	for(int i=T.H[x]; i; i=T.nxt[i])
		if(T.to[i]!=f) DFS(T.to[i],x,d+T.val[i]);
}

int main()
{
	tot=n=read(),m=read();
	for(int i=1; i<=m; ++i) G.AddEdge(read(),read());
	Tarjan(1,1);
	DFS(1,1,0), DFS(V,V,0);
	printf("%d",Max);

	return 0;
}
