/*
9940kb	2808ms
$Description$
����һ��$n$���������ÿ��������һ���ַ�����һ����$m$�Ĵ�$S$�����ж�����·��ѭ��ƥ���˸�������ѭ��ƥ��Ĵ�ָ����$SS...SS$�Ĵ���$S$���������Σ���
$n,m\leq10^5,\ \sum n,m\leq10^6$��
$Solution$
����Ρ�������μ����$rt$�Ĵ𰸡�
��$pre[i]$��ʾ��֮ǰ�ģ�������ѭ��ƥ����$S$��ǰ׺$i$��·���ж��٣�$suf[i]$��ʾ��֮ǰ�ģ�������ѭ��ƥ����$S$�ĺ�׺$i$��·���ж��١�
һ�����������Ϊǰ׺$dep\%m$���֣�Ȼ��$s[rt]=s[dep\%m+1]$���Ϳ���ͳ��$suf[m-dep\%m-1]$�Ĺ��ס�
��Ϊ��׺����ͬ��

��ĳ�����$dep$�Ƿ���ѭ��ƥ����$S$��ǰ׺$i$���������������$dep\sim dep-m+1$ƥ��������$S$���������$dep-m$ƥ����ǰ׺$i$����ʵֻҪ�Ȱ�$S$��ɳ���Ϊ$n$��ѭ�������ٶ�����$Hash$�Ϳ����ǡ�����ÿ�β���һ���ַ�ʱ���ַ�����ͷ���룬ֻ��Ҫ�ж�$hs_{now}==hs[dep]$��
�к�׺�Ͷ�Ӧһ���Ǹ�$hs_{now}$���ˣ�ÿ���ڿ�ͷ�����ַ���������������$s[n-2],s[n-1],s[n]$���õ���Hashֵ��$s[n],s[n-1],s[n-2]$�ģ����԰Ѵ���������Hashֵ����һ��$hs_{now}==hs'[dep]$�ͺ�����

���Ӷ�$O(n\log n)$��������ݷ�ΧӦ�ÿ������İȣ���Ӧ�á�����ʵ�����ݷ�ΧС�ǣ���
��ʼ��$1e6$��$pow$���黹����ÿ�γ�ʼ��$n$��=-=
���ⵥ��������$3\leq n,m\leq 1e5$�ġ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define seed 31
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
typedef unsigned long long ull;
const int N=1e5+5;

int m,s[N],ch[N],Enum,H[N],nxt[N<<1],to[N<<1],Min,root,sz[N],pre[N],suf[N],spre[N],ssuf[N],Maxd;
LL Ans;
ull pw[N],hs[N],hs2[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline void GetHash(ull *a,int *s,int n,int m)
{
	for(int i=m+1; i<=n; ++i) s[i]=s[i-m];
	for(int i=1; i<=n; ++i) a[i]=a[i-1]*seed+s[i];
}
void FindRoot(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa)
			FindRoot(v,x,tot), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v]);
	mx=std::max(mx,tot-mx);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int fa,int dep,ull val,const int Chrt)
{
	Maxd=std::max(Maxd,dep), val+=pw[dep-1]*ch[x];
	int tmp=dep%m;
	if(val==hs[dep]) ++pre[tmp], s[tmp+1]==Chrt&&(Ans+=ssuf[m-tmp-1]);
	if(val==hs2[dep]) ++suf[tmp], s[m-tmp]==Chrt&&(Ans+=spre[m-tmp-1]);
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa) DFS(v,x,dep+1,val,Chrt);
}
void Solve(int x)
{
	vis[x]=1; int mx=0; spre[0]=ssuf[0]=1;
//	spre[0]=ch[x]==s[1], ssuf[0]=ch[x]==s[m];//�������Ҫ�еİȡ���Ϊͳ�ƹ���ʱҪ��s[p]=ch[rt]��
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]])
		{
			Maxd=0, DFS(v,x,1,0,ch[x]), Maxd=std::min(Maxd,m-1), mx=std::max(mx,Maxd);
			for(int j=0,tmp=Maxd; j<=tmp; ++j) spre[j]+=pre[j], ssuf[j]+=suf[j], pre[j]=suf[j]=0;
		}
	for(int i=0; i<=mx; ++i) spre[i]=ssuf[i]=0;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) Min=N, FindRoot(v,x,sz[v]), Solve(root);
}

int main()
{
	pw[0]=1;
	for(int T=read(),mx=0; T--; )
	{
		int n=read(),m=read(); ::m=m;
		Enum=0, memset(H,0,n+1<<2), memset(vis,0,n+1);
		if(mx<n)
		{
			for(int i=mx+1; i<=n; ++i) pw[i]=pw[i-1]*seed;
			mx=n;
		}
		register char c; while(!isalpha(c=gc())); ch[1]=c-65+1;
		for(int i=2; i<=n; ++i) ch[i]=gc()-65+1;
		for(int i=1; i<n; ++i) AE(read(),read());
		while(!isalpha(c=gc())); s[1]=c-65+1;
		for(int i=2; i<=m; ++i) s[i]=gc()-65+1;
		GetHash(hs,s,n,m), std::reverse(s+1,s+1+m), GetHash(hs2,s,n,m), std::reverse(s+1,s+1+m);
		Ans=0, Min=N, FindRoot(1,1,n), Solve(root), printf("%lld\n",Ans);
	}

	return 0;
}
