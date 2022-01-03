//1107ms	75700KB
//https://www.cnblogs.com/SovietPower/p/9294996.html
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define pb push_back
#define Vec std::vector<int>
#define mod (1000000007)
#define Add(x,v) (x)+=(v),(x)>=mod&&((x)-=mod)
typedef long long LL;
const int N=300005;//2e5+5???

int n,A[N],Enum,H[N],nxt[N<<1],to[N<<1],dfn[N],Index,fa[N],sz[N],dep[N],son[N],tp[N],sk[N],top;
int cnt,P[N],phi[N],mu[N],sum[N],f[N],inv[N];
bool not_P[N];
Vec fac[N],pt[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void Add_direct(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline int LCA(int u,int v)
{
	while(tp[u]!=tp[v]) dep[tp[u]]>dep[tp[v]]?u=fa[tp[u]]:v=fa[tp[v]];
	return dep[u]>dep[v]?v:u;
}
void Pre()
{
	mu[1]=phi[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!not_P[i]) P[++cnt]=i, mu[i]=-1, phi[i]=i-1;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<=n; ++j)
		{
			not_P[v]=1;
			if(i%P[j]) mu[v]=-mu[i], phi[v]=phi[i]*(P[j]-1);
			else {mu[v]=0, phi[v]=phi[i]*P[j]; break;}
		}
	}
	for(int i=1; i<=n; ++i)
		for(int j=i; j<=n; j+=i) fac[j].push_back(i);
	inv[1]=1;
	for(int i=2; i<=n; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
void preDFS1(int x)
{
	const Vec &fc=fac[A[x]];
	for(int i=0,l=fc.size(); i<l; ++i)  pt[fc[i]].push_back(x);
	int mx=0; sz[x]=1, dfn[x]=++Index;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, preDFS1(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
void preDFS2(int x,int _tp)
{
	tp[x]=_tp;
	if(son[x])
	{
		preDFS2(son[x],_tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=son[x]&&to[i]!=fa[x]) preDFS2(to[i],to[i]);
	}
}
void Insert(int x)
{
	if(top==1) {sk[++top]=x; return;}
	int lca=LCA(x,sk[top]);
	while(dfn[sk[top-1]]>=dfn[lca]) Add_direct(sk[top],sk[top--]);
	if(sk[top]!=lca) Add_direct(lca,sk[top]), sk[top]=lca;
	sk[++top]=x;
}
void Build(const Vec &p)
{
	int n=p.size();
	sk[top=1]=1;
	if(p[0]==1) for(int i=1; i<n; ++i) Insert(p[i]);
	else for(int i=0; i<n; ++i) Insert(p[i]);
	while(--top) Add_direct(sk[top],sk[top+1]);
}
LL DFS(int x,int d)//虚树上有其它的点！
{
	LL res1=0, res2=0, s=A[x]%d?0:phi[A[x]];
	for(int v,i=H[x]; i; i=nxt[i])
		res1+=DFS(v=to[i],d), res2+=1ll*s*sum[v]%mod, Add(s,sum[v]);
	sum[x]=s%mod, H[x]=0;//! 都忘了虚树怎么写了。。
	return (res1%mod+res2*(LL)dep[x]%mod)%mod;//子树的答案和当前点为LCA独立，别算一块。。
}
void Calc(int d)
{
	const Vec &p=pt[d];
//	if(!p.size()) return;
	Build(p);
	LL res=0, sum=0; int n=p.size();
	for(int i=0; i<n; ++i) if(!(A[p[i]]%d)) sum+=phi[A[p[i]]];
	sum%=mod;
	for(int i=0; i<n; ++i) if(!(A[p[i]]%d)) res+=1ll*phi[A[p[i]]]*(sum-phi[A[p[i]]])%mod*dep[p[i]]%mod;
	res%=mod, res-=2ll*DFS(1,d)%mod;
	f[d]=(res%mod+mod)%mod;//+mod!
	Enum=0;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	Pre(), preDFS1(1), preDFS2(1,1);
	memset(H,0,sizeof H);
	for(int i=1; i<=n; ++i) Calc(i);
	LL ans=0;
	for(int d=1; d<=n; ++d)
	{
		LL sum=0;
		for(int i=1; i*d<=n; ++i) sum+=mu[i]*f[i*d];
		ans+=1ll*(sum%mod)*d%mod*inv[phi[d]]%mod;
	}
	printf("%I64d\n",2ll*(ans%mod)*inv[n]%mod*inv[n-1]%mod);

	return 0;
}
