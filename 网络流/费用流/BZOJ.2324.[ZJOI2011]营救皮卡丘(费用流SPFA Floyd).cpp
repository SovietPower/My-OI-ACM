/*
3072kb	220ms
����Ԥ�����$dis[i][j]$����ʾ��$i$��$j$�����·��������$Floyd$����
ע��$i,j$��û�д�С��ϵ���Ƶģ�$i>j$��$dis[i][j]$ҲҪ����Ȼ�����ò���������Ϊ���Դ�$i$�����м��$k,\ i<k<j$������$j$��ͬʱ$i\to j$ֻ�ܾ���$k<\max(i,j)$�ĵ㣬�������߲���$k$�ġ�

Ȼ���������ת��Ϊ�ò�����$k$��·���������е㣬��С����Ȩ�͡�
��㣬������ͼ��������������$i,j,\ i<j$��ֻ��$i$��$j'$���ߣ�����$1$������Ϊ$dis[i][j]$�������������Ҳ���ϴӱ��С�������ߣ�Ҳ������ֻ���
��$S$��$1,...,n$������$1$������$0$�ıߣ�$1,...,n$��$T$������$1$������$0$�ıߡ�
$S$��$0$������$k$������$0$�ıߣ�$0$��ÿ������ĵ�$1',...,n'$������$1$������$dis[0][i]$�ıߡ�
Ȼ������С������������ɡ�

����Ϊʲô��������$k$·�������ء�����$0$��$i'$���ͱ�ʾ�½�һ��$0\to i'\to...$��·�������ᳬ��$k$�����������$i\to j',\ i\neq0$�����ʾ��һ�����е�·���д�$i$�ߵ���$j$��
ͬʱͼ��$DAG$���һ�����������һ���Ϸ���

��������zkw��SPFA��������/������
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=305,M=(N*N/2+3*N)*2,INF=0x3f3f3f3f;

int S,T,Cost,Enum,H[N],nxt[M],fr[M],to[M],cap[M],cost[M],dis[N][N],pre[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w,int c)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	static int dis[N];
	static bool inq[N];
	static std::queue<int> q;
	memset(dis,0x3f,sizeof dis);
	dis[S]=0, q.push(S);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(cap[i] && dis[to[i]]>dis[x]+cost[i])
				dis[v=to[i]]=dis[x]+cost[i], pre[v]=i, !inq[v]&&(q.push(v),inq[v]=1);
	}
	return dis[T]<INF;
}
inline void Augment()
{
	for(int i=T; i!=S; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1], Cost+=cost[pre[i]];
}
int MCMF()
{
	while(SPFA()) Augment();
	return Cost;
}

int main()
{
	const int n=read(),m=read(),K=read();
	Enum=1, S=2*n+1, T=2*n+2;
	memset(dis,0x3f,sizeof dis);
	for(int i=0; i<=n; ++i) dis[i][i]=0;
	for(int i=1,u,v; i<=m; ++i)
		u=read(), v=read(), dis[u][v]=dis[v][u]=std::min(dis[v][u],read());
	for(int k=0; k<=n; ++k)
		for(int i=0; i<=n; ++i)
			for(int j=0; j<=n; ++j)
				if(k<i||k<j) dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
	AE(S,0,K,0);
	for(int i=1; i<=n; ++i) AE(S,i,1,0), AE(i+n,T,1,0);
	for(int i=0; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
			AE(i,j+n,1,dis[i][j]);
	printf("%d\n",MCMF());

	return 0;
}
