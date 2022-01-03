/*
1044KB	516MS
在所有点中任选两个点作为源点$S$、汇点$T$，求它们之间的最小割$ans$，并把原图分成两个点集$S',T'$，用$ans$更新两个点集间的答案。
然后再分别对两个点集$S',T'$重复这个过程，直到集合中只剩一个点。
这样就可以求出所有点对的最小割，且得到了一棵最小割树。可以证明这是对的。
可以证明一个结论是：记$mincut(x,y)$为$x,y$之间的最小割，对于图中任意三个点$a,b,c$，有$mincut(a,b)>=min(mincut(a,c),mincut(b,c))$。
然后可以得出，对于任意两个点$u,v$，令$x,y$为它们树上路径中$mincut$最小的边的两个端点，那么$mincut(u,v)=mincut(x,y)$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 150000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=160,M=6007;

int n,src,des,Enum,H[N],nxt[M],to[M],fr[M],Cap[M],cap[M],pre[N],lev[N],tmp[2][N],A[N],ans[N][N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int w,int v,int u)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, Cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, Cap[Enum]=w;
}
bool BFS()
{
	static int q[N];
	for(int i=1; i<=n; ++i) lev[i]=n+1;
	int h=0,t=1; lev[des]=0, q[0]=des;
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
	int mn=1e6;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	static int num[N],cur[N];

	if(!BFS()) return 0;

	memset(num,0,sizeof num);//
	for(int i=1; i<=n; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src,res=0;
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
		if(cap[i] && !vis[to[i]]) Cut(to[i]);
}
void Solve(int l,int r)
{
	if(l==r) return;

	for(int i=2; i<=Enum; ++i) cap[i]=Cap[i];
	src=A[l], des=A[r];
	int cnt[2]={0,0}, mincut=ISAP();

	memset(vis,0,sizeof vis);
	Cut(src);
	for(int i=1; i<=n; ++i)
		if(vis[i])
			for(int j=1; j<=n; ++j)
				if(!vis[j]) ans[i][j]=ans[j][i]=std::min(ans[j][i],mincut);

	for(int i=l,x=A[i]; i<=r; x=A[++i]) tmp[vis[x]][cnt[vis[x]]++]=x;
	for(int i=0; i<cnt[0]; ++i) A[l+i]=tmp[0][i];
	for(int i=0,mid=l+cnt[0]; i<cnt[1]; ++i) A[mid+i]=tmp[1][i];
	Solve(l,l+cnt[0]-1), Solve(l+cnt[0],r);
}

int main()
{
	for(int T=read(),m; T--; )
	{
		Enum=1, memset(H,0,sizeof H);
		memset(ans,0x3f,sizeof ans);

		n=read(),m=read();
		while(m--) AE(read(),read(),read());
		for(int i=1; i<=n; ++i) A[i]=i;
		Solve(1,n);
		for(int Q=read(); Q--; )
		{
			int x=read(),res=0;
			for(int i=1; i<=n; ++i)
				for(int j=i+1; j<=n; ++j)
					if(ans[i][j]<=x) ++res;
			printf("%d\n",res);
		}
		putchar('\n');
	}
	return 0;
}
