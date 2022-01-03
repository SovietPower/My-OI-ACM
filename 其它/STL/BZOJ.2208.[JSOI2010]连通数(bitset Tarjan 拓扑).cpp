/*
63888kb	1080ms
�����㣬����scc֮�乱�׼�Ϊszscc[i]*szscc[j] 
��f[i][j]��ʾscci�Ƿ��ܵ�sccj 
��������ÿ�ΰ�now��f����to��f 
��bitset�Ż� 
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
const int N=2005,M=4e6+5;

int n,bel[N],Enum,H[N],Snum,Sh[N];
int cnt,dgr[N],sz[N],dfn[N],low[N],id,sk[N],top,q[N];
bool ins[N];
char s[N];
std::bitset<N> f[N];
struct Edge
{
	int nxt,to;
}e[M],se[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	e[++Enum].to=v, e[Enum].nxt=H[u], H[u]=Enum;
}
inline void AddEdge2(int u,int v){
	++dgr[v];
	se[++Snum].to=v, se[Snum].nxt=Sh[u], Sh[u]=Snum;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++id, sk[++top]=x, ins[x]=1;
	for(int v,i=H[x]; i; i=e[i].nxt)
		if(!dfn[v=e[i].to])
			Tarjan(v), low[x]=std::min(low[x],low[v]);
		else if(ins[v])
			low[x]=std::min(low[x],dfn[v]);
	if(dfn[x]==low[x])
	{
		++cnt;
		do{
			bel[sk[top]]=cnt, ++sz[cnt];
			ins[sk[top--]]=0;
		}while(x!=sk[top+1]);
	}
}
void Rebuild()
{
	for(int x=1; x<=n; ++x)
		for(int i=H[x]; i; i=e[i].nxt)
			if(bel[e[i].to]!=bel[x]) AddEdge2(bel[e[i].to],bel[x]);//���� 
}
int Solve()//cnt��n��� 
{
	int h=0,t=0;
	for(int i=1; i<=cnt; ++i)
		if(!dgr[i]) q[t++]=i;
	for(int i=1; i<=cnt; ++i) f[i][i]=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=Sh[x]; i; i=se[i].nxt)
		{
			if(!--dgr[se[i].to]) q[t++]=se[i].to;
			f[se[i].to]|=f[x];
		}
	}
	int res=0;
	for(int i=1; i<=cnt; ++i)
		for(int j=1; j<=cnt; ++j)
			if(f[i][j]) res+=sz[i]*sz[j];
	return res;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",s+1);
		for(int j=1; j<=n; ++j)
			if(s[j]=='1') AddEdge(i,j);
	}
	for(int i=1; i<=n; ++i)
		if(!dfn[i]) Tarjan(i);
	Rebuild();
	printf("%d",Solve());

	return 0;
}
