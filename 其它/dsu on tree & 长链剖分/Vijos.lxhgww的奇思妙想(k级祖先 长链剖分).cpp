/*
长链剖分模板。
6,7,8,20个点RE，没什么办法了。。（迷）
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define BIT 18
typedef long long LL;
const int N=3e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],fa[N][19],dep[N],son[N],mxd[N],top[N],hb[N];
std::vector<int> up[N],down[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x)
{
	int mx=dep[x];
	for(int i=1; 1<<i<=mx; ++i) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x][0])
			fa[v][0]=x, dep[v]=dep[x]+1, DFS1(v), mxd[v]>mx&&(mx=mxd[v],son[x]=v);
	mxd[x]=mx;
}
void DFS2(int x,int tp)
{
	top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x][0]&&v!=son[x]) DFS2(v,v);
	}
}
inline int Query(int k,int x)
{
	if(!k) return x;
	if(k>dep[x]) return 0;
	x=fa[x][hb[k]], k^=1<<hb[k];
	return dep[x]-dep[top[x]]>=k?down[top[x]][dep[x]-dep[top[x]]-k]:up[top[x]][k-dep[x]+dep[top[x]]];
}

int main()
{
	int n=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1), DFS2(1,1);
	for(int i=1; i<=n; ++i)
		if(top[i]==i)
		{
			int lim=mxd[i]-dep[i];
			for(int x=i,j=0; j<=lim; ++j) up[i].push_back(x),x=fa[x][0];
			for(int x=i,j=0; j<=lim; ++j) down[i].push_back(x),x=son[x];
		}
	for(int mx=1,i=2; i<=n; ++i) i>>mx&1&&(++mx), hb[i]=mx-1;
//	for(int i=2; i<=n; ++i) hb[i]=hb[i-1]+(i>>(hb[i-1]+1)&1);
	for(int ans=0,Q=read(); Q--; printf("%d\n",ans=Query(ans^read(),ans^read())));

	return 0;
}
