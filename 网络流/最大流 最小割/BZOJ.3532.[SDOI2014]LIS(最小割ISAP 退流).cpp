/*
16392kb	3816ms
$LIS$��������ģ�ͣ�
��$f_i$��ʾ��$i$��β��$LIS$���ȡ�
���$f_i=1$������$(S,i,INF)$�����$f_i=\max\limits_{j=1}^n\{f_j\}$������$(i,T,INF)$�����$f_i=f_j+1,\ j<i$������$(j,i,INF)$��
����ʹ$LIS$�������ټ���$1$������ɾ��ͼ�е�һЩ�㣬ʹ��$S,T$����ͨ��
��㣬��$i$���$X_i,Y_i$������$(X_i,Y_i,cost_i)$��$j\to i$�����߾���$Y_j\to X_i$��
����С��Ϳ��Եõ���С�����ˡ�

����$C_i$�ֵ�����С�ķ�����
�ѵ㰴��$C_i$��С������������Ҫ�����жϱ�$(X_i,Y_i)$�Ƿ��������С���ϡ�
��$(u,v)$����С���ϵ��ҽ������������������Ҳ��������㡣
���ں�һ���������ж���$u$��Դ�㣬$v$����㣬�Ƿ��������·���Ϳ����ˣ���$u$��$v$ $BFS$����
Ȼ�����ѡ���˱�$(u,v)$���Ǿ���$(u,v)$��·���ϵ������߶�������ѡ���ѱ�$(u,v)$�������˻�ȥ���Ϳ���ʹ��Щ��һ��������С�����ˡ�
����������ǣ���$u$��Դ�㣬$S$����㣬��$cap_{(u,v)}$������������$T$��Դ�㣬$v$����㣬��$cap_{(u,v)}$����������$S,T$��ԭͼ��Դ��㣩
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
