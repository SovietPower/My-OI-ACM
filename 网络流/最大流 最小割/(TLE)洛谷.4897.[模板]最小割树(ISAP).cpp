/*
最小割树模板。具体见：https://www.cnblogs.com/SovietPower/p/9734013.html。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=507,M=3007,INF=1e9;

int n,src,des,A[N],ans[N][N],Enum,H[N],fr[M],to[M],nxt[M],cap[M],Cap[M],pre[N],lev[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void AE(int w,int v,int u)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, Cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, Cap[Enum]=w;
}
bool BFS()
{
	static int q[N];
	int n=::n;
	for(int i=1; i<=n; ++i) lev[i]=n+1;
	int h=0,t=1; q[0]=des, lev[des]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==n+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=n;
}
inline int Augment()
{
	int mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	static int cur[N],num[N];
	if(!BFS()) return 0;
	memset(num,0,n+2<<2);
	for(int i=1; i<=n; ++i) cur[i]=H[i],++num[lev[i]];
	int res=0,x=src;
	while(lev[src]<=n)
	{
		if(x==des) x=src,res+=Augment();
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=n;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}
void Cut(int x)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(cap[i]&&!vis[to[i]]) Cut(to[i]);
}
void Solve(int l,int r)
{
	static int tmp[2][N];
	if(l==r) return;

	for(int i=2; i<=Enum; ++i) cap[i]=Cap[i];
	src=A[l], des=A[r];
	int mincut=ISAP();

	memset(vis,0,sizeof vis), Cut(src);
	for(int i=1; i<=n; ++i)
		if(vis[i])
			for(int j=1; j<=n; ++j)
				if(!vis[j]) ans[j][i]=ans[i][j]=std::min(ans[i][j],mincut);

	int cnt[2]={0,0};
	for(int i=l,x=A[i]; i<=r; x=A[++i]) tmp[vis[x]][cnt[vis[x]]++]=x;
	for(int i=0; i<cnt[0]; ++i) A[l+i]=tmp[0][i];
	for(int i=0,mid=l+cnt[0]; i<cnt[1]; ++i) A[mid+i]=tmp[1][i];
	Solve(l,l+cnt[0]-1), Solve(l+cnt[0],r);
}

int main()
{
	Enum=1, n=read(); int m=read();
	for(int i=1; i<=m; ++i) AE(read(),read(),read());
	for(int i=1; i<=n; ++i) A[i]=i;
	memset(ans,0x3f,sizeof ans);
	Solve(1,n);
	for(int Q=read(); Q--; printf("%d\n",ans[read()][read()]));

	return 0;
}
