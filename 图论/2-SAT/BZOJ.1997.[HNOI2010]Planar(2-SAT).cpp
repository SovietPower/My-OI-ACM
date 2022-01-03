/*
存在一个环，说明什么？
画了一下样例二，直接是个环；然后重新画了下样例一，可以画成一个环，非环上的边可以连在环内或环外 
这些非环上的边不能相交。然后就成了POJ原题了，只是圆上排列顺序不同。
不过边数很多，必须利用平面图的性质: 平面图的边数小于等于3n-6，来将边数降到O(n)级别 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=20005,M=4e5+5,MAXIN=2e6;

int n,m,A[N]/*规定一个数在圆上的位置*/,st[N],ed[N],Enum,H[N],nxt[M],to[M];
int sk[N],top,cnt,bel[N],id,dfn[N],low[N];
bool ins[N],isc[N];
char IN[MAXIN],*SS=IN,*TT=IN;

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
		if(!dfn[v=to[i]]) Tarjan(v),low[x]=std::min(low[x],low[v]);
		else if(ins[v]) low[x]=std::min(low[x],dfn[v]);
	if(low[x]==dfn[x])
	{
		++cnt;
		do{
			bel[sk[top]]=cnt, ins[sk[top--]]=0;
		}while(x!=sk[top+1]);
	}
}

int main()
{
	int t=read();
	while(t--)
	{
		n=read(),m=read();
		for(int i=1; i<=m; ++i) st[i]=read(),ed[i]=read();
		for(int i=1; i<=n; ++i) A[read()]=i;
		if(m>3*n-6) {puts("NO"); continue;}
		cnt=Enum=id=0, memset(H,0,sizeof H);
		memset(isc,0,sizeof isc), memset(dfn,0,sizeof dfn);
		for(int i=1; i<=m; ++i)
			if(A[st[i]]>A[ed[i]]) st[i]=A[st[i]],ed[i]=A[ed[i]],std::swap(st[i],ed[i]);
			else st[i]=A[st[i]],ed[i]=A[ed[i]];
		for(int i=1; i<=m; ++i)
			if(st[i]+1==ed[i]||(st[i]==1&&ed[i]==n)) isc[i]=isc[i+m]=1;
		for(int i=1; i<=m; ++i)
			if(!isc[i]) for(int j=1; j<=m; ++j)
					if(!isc[j] && i!=j && st[j]<st[i]&&st[i]<ed[j]&&ed[j]<ed[i])
						AddEdge(i,j+m),AddEdge(i+m,j),AddEdge(j,i+m),AddEdge(j+m,i);
		for(int i=1; i<=m<<1; ++i)//是枚举两个集合的边。。
			if(!isc[i] && !dfn[i]) Tarjan(i);
		bool f=1;
		for(int i=1; i<=m; ++i)
			if(!isc[i] && bel[i]==bel[i+m]) {f=0; break;}
		puts(f?"YES":"NO");
	}
	return 0;
}
