/*
1816K	16MS
$Description$
һ��Բ��˳������0,1,...,n-1��n���㣬����m���߶Σ��߶ο��Դ�������Ҳ���Դ������������Ƿ������������߶β��ཻ 
$Solution$
��ÿ���߶ο���һ���㣬ֻ����Բ�����Բ��������������ǿ��԰��߶β��i,i'���ֱ��ʾ������� 
���ڶ˵��ཻ���߶λ����ì�� 
��i������j�ཻ����: 
i��Բ�� j����Բ�⣻i��Բ�� j����Բ�� 
j��Բ�� i����Բ�⣻j��Բ�� i����Բ�� 
ע�����Ҫ˫���ж� 
����һ��Ҫ�� 
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
			if(i!=j && st[j]<st[i]&&st[i]<ed[j]&&ed[j]<ed[i])//��ͬ���ཻ˳����ɶ�ö��һ������ 
				AddEdge(i*2-1,j*2), AddEdge(i*2,j*2-1), AddEdge(j*2-1,i*2), AddEdge(j*2,i*2-1);
	for(int i=1; i<=m<<1; ++i)
		if(!dfn[i]) Tarjan(i);
	bool f=1;
	for(int i=1; i<=m; ++i)
		if(bel[i*2-1]==bel[i<<1]) {f=0; break;}
	puts(f?"panda is telling the truth...":"the evil panda is lying again");

	return 0;
}
