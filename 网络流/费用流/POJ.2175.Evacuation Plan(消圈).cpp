/*
688K	329MS
ֱ���ܷ�������T������Ҳû��Ҫ��
�������������ڸ�����ֻ���������ıߣ�����ô�ظø����������㣬���Եõ�һ����ŵĽ⡣������ǵ�ǰ�����µ���С��������
���Խ����������磬�ҳ����������ڸ�������һ������ˡ�
$S\to i$��ÿ���ߵ������϶��������ģ����Բ���Ҫ����$i'\to T$�ľͲ�һ���ˣ���
���Ӷ�$O(nm)$��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=205,M=(105*105+N)*2,INF=0x3f3f3f3f;

int Enum,H[N],nxt[M],to[M],cost[M],dis[N],pre[N],g[105][105];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w,int c)
{
	if(w) to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cost[Enum]=c;
}
int SPFA(const int n)
{
	static int tm[N];
	static bool inq[N];
	std::queue<int> q;
	memset(dis,0x3f,n+1<<2);
	dis[n]=0, q.push(n), tm[n]=1;
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[to[i]]>dis[x]+cost[i])
			{
				dis[v=to[i]]=dis[x]+cost[i], pre[v]=x;
				if(!inq[v])
				{
					if(++tm[v]>=n) return v;
					q.push(v), inq[v]=1;
				}
			}
	}
	return -1;
}
void FindCircle(int x,const int n)
{
	static bool vis[N];
	while(!vis[x]) vis[x]=1, x=pre[x];//p��һ���ڻ��ϣ������ܻص�������Ӧ�����ҳ���������
	int tmp=x;
	do
	{
		int v=pre[x];//v->x
		if(x<=n && v>n) --g[x][v-n];
		else if(x>n && v<=n) ++g[v][x-n];
		x=v;
	}while(x!=tmp);
}

int main()
{
	static int a[N],b[N],c[N],d[N],cap[N],use[N];
	const int n=read(),m=read(),T=n+m+1;
	for(int i=1; i<=n; ++i) a[i]=read(),b[i]=read(),read();
	for(int i=1; i<=m; ++i) c[i]=read(),d[i]=read(),cap[i]=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			use[j]+=g[i][j]=read();
			int cost=std::abs(a[i]-c[j])+std::abs(b[i]-d[j])+1;
			AE(i,j+n,INF-g[i][j],cost), AE(j+n,i,g[i][j],-cost);//negative!
		}
	for(int i=1; i<=m; ++i) AE(i+n,T,cap[i]-use[i],0), AE(T,i+n,use[i],0);
	int p=SPFA(T);
	if(p==-1) puts("OPTIMAL");
	else
	{
		FindCircle(p,n), puts("SUBOPTIMAL");
		for(int i=1; i<=n; ++i,putchar('\n'))
			for(int j=1; j<=m; ++j) printf("%d ",g[i][j]);
	}

	return 0;
}
