/*
28260kb	584ms
~~树剖/~~差分裸题。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int A[N],Enum,H[N],nxt[N<<1],to[N<<1],fa[N],dep[N],sz[N],son[N],top[N],sum[N];
char IN[MAXIN],*SS=IN,*TT=IN,OUT[3000000],*O=OUT;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void print(int x)
{
	if(x>9) print(x/10);
	*O++ = x%10+48;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]<dep[v]?u:v;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x]&&v!=son[x]) DFS2(v,v);
	}
}
void DFS3(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) DFS3(to[i]), sum[x]+=sum[to[i]];
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1), DFS2(1,1);
	for(int i=1,w; i<n; ++i)
		++sum[fa[A[i]]], ++sum[A[i+1]], --sum[w=LCA(A[i],A[i+1])], --sum[fa[w]];
//		++sum[A[i]], ++sum[A[i+1]], --sum[w=LCA(A[i],A[i+1])], --sum[fa[w]];
	DFS3(1);//还可以用拓扑替换掉DFS。。
	++sum[A[1]], --sum[A[n]];
//	for(int i=2; i<=n; ++i) --sum[A[i]];
	for(int i=1; i<=n; ++i) print(sum[i]),*O++='\n';//printf("%d\n",sum[i]);
	fwrite(OUT,O-OUT,1,stdout);

	return 0;
}
