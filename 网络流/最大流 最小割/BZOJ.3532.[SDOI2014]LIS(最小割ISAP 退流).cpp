/*
16392kb	3816ms
$LIS$。。经典模型？
令$f_i$表示以$i$结尾的$LIS$长度。
如果$f_i=1$，连边$(S,i,INF)$；如果$f_i=\max\limits_{j=1}^n\{f_j\}$，连边$(i,T,INF)$；如果$f_i=f_j+1,\ j<i$，连边$(j,i,INF)$。
这样使$LIS$长度至少减少$1$，就是删掉图中的一些点，使得$S,T$不连通。
拆点，把$i$拆成$X_i,Y_i$，连边$(X_i,Y_i,cost_i)$。$j\to i$的连边就连$Y_j\to X_i$。
求最小割就可以得到最小花费了。

对于$C_i$字典序最小的方案：
把点按照$C_i$从小到大排序，我们要依次判断边$(X_i,Y_i)$是否可以在最小割上。
边$(u,v)$在最小割上当且仅当，这条边满流，且不能再增广。
对于后一个条件就判断以$u$做源点，$v$做汇点，是否存在增广路径就可以了（从$u$到$v$ $BFS$）。
然后如果选择了边$(u,v)$，那经过$(u,v)$的路径上的其它边都不能再选。把边$(u,v)$的流量退回去，就可以使这些边一定不在最小割上了。
退流具体就是，以$u$做源点，$S$做汇点，流$cap_{(u,v)}$的流量；再以$T$做源点，$v$做汇点，流$cap_{(u,v)}$的流量。（$S,T$是原图的源汇点）
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1407,M=705*703*2,INF=0x3f3f3f3f;

int src,des,rk[N],Enum,H[N],nxt[M],to[M],fr[M],cap[M],lev[N],pre[N],dis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
inline bool cmp(int a,int b)
{
	return rk[a]<rk[b];
}
bool BFS(int S,int T)
{
	static int q[N];
	const int lim=des+1;
	for(int i=0; i<=des; ++i) lev[i]=lim;
	int h=0,t=1; q[0]=T, lev[T]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==lim && cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[S]<=des;
}
inline int Augment(int S,int T,int flow)
{
	for(int i=T; i!=S; i=fr[pre[i]])
		flow=std::min(flow,cap[pre[i]]);
	for(int i=T; i!=S; i=fr[pre[i]])
		cap[pre[i]]-=flow, cap[pre[i]^1]+=flow;
	return flow;
}
int ISAP(int S,int T,int flow)
{
	static int num[N],cur[N];
	if(!BFS(S,T)) return 0;
	memset(num,0,des+2<<2);
	for(int i=0; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int res=0,x=S;
	while(lev[S]<=des)
	{
		if(x==T) x=S, res+=Augment(S,T,flow);
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=S) x=fr[pre[x]];
		}
	}
	return res;
}

int main()
{
	static int A[N],cost[N],f[N],B[N],e[N],Ans[N];
	for(int T=read(); T--; )
	{
		const int n=read(); src=0, des=n<<1|1;
		Enum=1, memset(H,0,des+1<<2);
		for(int i=1; i<=n; ++i) A[i]=read();
		for(int i=1; i<=n; ++i) cost[i]=read();
		for(int i=1; i<=n; ++i) rk[i]=read();
		int mx=0;
		for(int i=1; i<=n; ++i)
		{
			int tmp=0;
			for(int j=1; j<i; ++j) A[i]>A[j]&&(tmp=std::max(tmp,f[j]));
			mx=std::max(mx,f[i]=tmp+1);
		}
		for(int i=1; i<=n; AE(i,i+n,cost[i]),e[i++]=Enum)
			if(f[i]!=1)
			{
				if(f[i]==mx) AE(i+n,des,INF);
				for(int j=1; j<i; ++j) if(f[j]+1==f[i] && A[j]<A[i]) AE(j+n,i,INF);
			}
			else AE(0,i,INF);
		int tot=ISAP(0,des,INF);
		printf("%d ",tot);
//Subtask2
		for(int i=1; i<=n; ++i) B[i]=i;
		std::sort(B+1,B+1+n,cmp); int cnt=0;
		for(int i=1,x=B[1],ex=e[x]; i<=n&&tot; x=B[++i],ex=e[x])
			if(!cap[ex^1] && !BFS(x,x+n))
				tot-=cap[ex], Ans[++cnt]=x, ISAP(x,src,cap[ex]), ISAP(des,x+n,cap[ex]), cap[ex]=cap[ex^1]=0;
		std::sort(Ans+1,Ans+1+cnt), printf("%d\n",cnt);
		for(int i=1; i<=cnt; ++i) printf("%d%c",Ans[i]," \n"[i==cnt]);
	}
	return 0;
}
