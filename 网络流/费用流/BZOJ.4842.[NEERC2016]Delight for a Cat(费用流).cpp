/*
980kb	4212ms
�������һ�����ʱ��������������ô��һ���Ҳһ�����㡣~~���о���������Ƿ�����û��Ϊʲô��~~���������������ʱ�䶼����˯������ô����Ҫ��ÿ��$k$��С����ѡ��$[t2,k-t1]$��ʱ�̴���Ϸ��ͬʱҪ��ѡ����$\sum s_i-e_i$����С��

����Ҫ�����Ϸ��ʱ��ǡ��Ϊ$t2$��ô���أ�
��ÿ��ʱ�̽�һ����$i$����$i$��$i+k$���ߣ���������ֱ�������㣩������$1$����$s_i-e_i$����һ�����$p$��$p$��$1\sim k$ÿ����������$1$����$0$�ıߣ�Դ��$S$��$p$������$t2$����$0$�ıߡ�
�������ѡ��$i$��һ����ѡ$i+k$������ÿ��$k$���䶼��ǡ��ѡ��$t2$��ʱ�̡�

�����ڴ���Ϸ��ʱ�������ߵ�$k-t1$�ء�
��$i$��$i+1$���ߣ�����$k-t1-t2$����$0$��$S$��$p$�����������ĳ�$k-t1$��
��������ÿ��$k$���䣬Ӧ���е�$t2$������Ϸ�ıߺ�֮ǰһ�����������ߡ������Զ�ѡ$k-t1-t2$��ʱ�̴���Ϸ��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1007,M=3*N*2;
const LL INF=0x3f3f3f3f3f3f3f3f;

int S,T,A[N],B[N],Enum,H[N],nxt[M],to[M],cap[M],len[M],cur[N];
bool vis[N];
LL Cost,dis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w,int c)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, len[Enum]=c;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, len[Enum]=-c;
}
bool SPFA()
{
	static bool inq[N];
	static std::queue<int> q;
	memset(dis,0x3f,T+1<<3);//<<3!!!
	dis[S]=0, q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop(), inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(cap[i]&&dis[to[i]]>dis[x]+len[i])
				dis[v=to[i]]=dis[x]+len[i], !inq[v]&&(q.push(v),inq[v]=1);
	}
	return dis[T]<INF;
}
bool DFS(int x)
{
	if(x==T) return 1;
	vis[x]=1;
	for(int &i=cur[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&dis[v]==dis[x]+len[i]&&cap[i]&&DFS(v))//&&cap[i]!!! �б�Ҫ�İ� 
			return --cap[i],++cap[i^1],Cost+=len[i],1;
	return 0;
}
void MCMF()
{
	while(SPFA())
	{
		memcpy(cur,H,T+1<<2), memset(vis,0,T+1);
		while(DFS(S));
	}
}

int main()
{
	static int e[N];
	int n=read(),K=read(),t1=read(),t2=read(),P=n+1;
	Enum=1, S=0, T=n+2; LL ans=0;
	for(int i=1; i<=n; ++i) ans+=A[i]=read();
	for(int i=1; i<=n; ++i) B[i]=read();
	AE(S,P,K-t1,0);
	for(int i=1; i<=K; ++i) AE(P,i,1,0);
	for(int i=1,tmp=K-t1-t2; i<=n; ++i) AE(i,i+1>n?T:i+1,tmp,0), AE(i,i+K>n?T:i+K,1,A[i]-B[i]), e[i]=Enum;
	MCMF(), printf("%lld\n",ans-Cost);
	for(int i=1; i<=n; ++i) putchar(cap[e[i]]?'E':'S');

	return 0;
}
