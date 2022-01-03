/*
31ms	6200KB
每条链只能向上覆盖，那贪心策略就显然了啊（子树每个点求最远能向上覆盖的距离）。
可以在DFS的过程中存下该链的信息，然后二分。也可以直接用并查集合并被覆盖的链。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 200000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+6;

int w[N],fa[N],F[N],q[N],dgr[N],dep[N];
LL sum[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	return x==F[x]?x:F[x]=Find(F[x]);
}

int main()
{
	int n=read(),L=read(); LL S=readll();
	for(int i=1; i<=n; ++i) if((w[i]=read())>S) return puts("-1"),0;
	for(int i=2; i<=n; ++i) ++dgr[fa[i]=read()];
	for(int i=1; i<=n; ++i) F[i]=i,sum[i]=sum[fa[i]]+w[i],dep[i]=dep[fa[i]]+1;

	int h=0,t=0,Ans=0;
	for(int i=1; i<=n; ++i) if(!dgr[i]) q[t++]=i;
	while(h<t)
	{
		int x=q[h++];
		if(vis[x]) continue;
		++Ans;

		int num=0; LL s=0;
		while(x)
		{
			int nxt=Find(x);
			num+=dep[x]-dep[nxt]+1, s+=sum[x]-sum[nxt]+w[nxt];
			if(num>L||s>S) break;

			vis[nxt]=1;
			if(!--dgr[fa[nxt]]) q[t++]=fa[nxt];
			F[nxt]=Find(fa[F[nxt]]), x=fa[nxt];
		}
	}
	printf("%d\n",Ans);

	return 0;
}
