/*
1566ms	2.24MB
最小割树模板。具体见：https://www.cnblogs.com/SovietPower/p/9734013.html。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=507,M=3007,INF=1e9;

int n,src,des,A[N],ans[N][N],Enum,H[N],fr[M],to[M],nxt[M],cap[M],Cap[M],pre[N],cur[N],lev[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

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
	memset(lev,0,n+2<<2);
	memcpy(cur,H,n+2<<2);
	int h=0,t=1; q[0]=src, lev[src]=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(!lev[to[i]] && cap[i])
			{
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
				if(to[i]==des) return 1;
			}
	}
	return 0;
}
int DFS(int x,int flow)
{
	if(x==des) return flow;
	int used=0;
	for(int &i=cur[x]; i; i=nxt[i])
		if(cap[i] && lev[to[i]]==lev[x]+1)
		{
			int delta=DFS(to[i],std::min(flow-used,cap[i]));
			if(delta)
			{
				cap[i]-=delta, cap[i^1]+=delta, used+=delta;
				if(used==flow) return flow;
			}
		}
	lev[x]=0;
	return used;
}
int Dinic()
{
	int res=0;
	while(BFS()) res+=DFS(src,INF);
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
	int mincut=Dinic();

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
