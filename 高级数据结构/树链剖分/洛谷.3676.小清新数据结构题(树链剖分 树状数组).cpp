/*
689ms	22292KB

*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],val[N],sum[N],fa[N],dep[N],sz[N],son[N],top[N],L[N],R[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct BIT
{
	int n,t1[N]; LL t2[N];
	#define lb(x) (x&-x)
	inline void Modify2(int p,int v)
	{
		for(LL v2=1ll*p*v; p<=n; p+=lb(p)) t1[p]+=v, t2[p]+=v2;
	}
	inline void Modify(int l,int r,int v)
	{
		Modify2(l,v), Modify2(r+1,-v);
	}
	inline LL Query2(int x)
	{
		LL res1=0,res2=0;
		for(int p=x; p; p^=lb(p)) res1+=t1[p], res2+=t2[p];
		return res1*(x+1)-res2;
	}
	inline LL Query(int l,int r)
	{
		return Query2(r)-Query2(l-1);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sum[x]+=sum[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	top[x]=tp, L[x]=++Index;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x]&&v!=son[x]) DFS2(v,v);
	}
	R[x]=Index;
}
void Modify(int x,int v)
{
	while(top[x]!=1) T.Modify(L[top[x]],L[x],v), x=fa[top[x]];
	T.Modify(1,L[x],v);
}
LL Query(int x)
{
	LL res=0;
	while(top[x]!=1) res+=T.Query(L[top[x]],L[x]), x=fa[top[x]];
	return res+T.Query(1,L[x]);
}

int main()
{
	int n=read(),Q=read(); T.n=n;
	for(int i=1; i<n; ++i) AE(read(),read());
	for(int i=1; i<=n; ++i) sum[i]=val[i]=read();
	dep[1]=1, DFS1(1), DFS2(1,1);

	LL Ans=0;
	for(int i=1; i<=n; ++i) Ans+=1ll*sum[i]*sum[i], T.Modify(L[i],L[i],sum[i]);
	for(int x,y,s1=sum[1]; Q--; )
		if(read()==1) x=read(), y=read()-val[x], Ans+=2ll*y*Query(x)+y*y*dep[x], Modify(x,y), val[x]+=y, s1+=y;//¸üÐÂs1£¡
		else x=read(), printf("%lld\n",Ans+1ll*(dep[x]+1)*s1*s1-2ll*s1*Query(x));

	return 0;
}
