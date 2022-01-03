/*
����1.��㽨ͼ 
����2.��ʵ���ǲ��ò���ˣ�����Ҳû��Ҫ�ؽ�ͼ����ԭ�����Բ�㽨��������ΪINF���� 
����3.��֮������������ΪINF 
ע��һ����Ҫ�ӵ�һ�в�ͬ��m��λ�ÿ�ʼ�ߣ�2.3���ڵ�n������һ��λ�ý�����(���������һ��)
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=10005,M=200000,INF=0x3f3f3f3f;

int n,m,src,des,id[30][30],A[N],C[M<<1],Enum,dis[N],pre[N],H[N],fr[M<<1],to[M<<1],nxt[M<<1],cap[M<<1],cost[M<<1];
bool inq[N];
std::queue<int> q;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w,int c)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, C[Enum]=cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, C[Enum]=cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		inq[x]=0;
		for(int i=H[x]; i; i=nxt[i])
			if(cap[i] && dis[to[i]]>dis[x]+cost[i])
			{
				dis[to[i]]=dis[x]+cost[i], pre[to[i]]=i;
				if(!inq[to[i]]) q.push(to[i]),inq[to[i]]=1;
			}
	}
	return dis[des]<INF;
}
int MCMF()
{
	int res=0,mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(cap[pre[i]],mn);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn,cap[pre[i]^1]+=mn,res+=cost[pre[i]]*mn;
	return res;
}

int main()
{
	freopen("digit.in","r",stdin);
	freopen("digit.out","w",stdout);

	m=read(),n=read();
	Enum=1, src=0, des=(2*m+n-1)*n+1;
	int cnt=0,v,lim=des-1>>1;
	for(int i=0; i<n-1; ++i)
		for(int j=1; j<=i+m; ++j)
			A[id[i][j]=++cnt]=read(),AddEdge(cnt+lim,cnt+i+m,1,0),AddEdge(cnt+lim,cnt+i+m+1,1,0);
	for(int i=1; i<=m+n-1; ++i) A[id[n][i]=++cnt]=read(),AddEdge(cnt+lim,des,1,0);
	for(int i=1; i<=cnt; ++i) AddEdge(i,i+lim,1,-A[i]);
	for(int i=1; i<=m; ++i) AddEdge(src,i,1,0);
	int res1=0;
	while(SPFA()) res1+=MCMF();

	int res2=0;
	for(int i=2; i<=Enum; ++i) cap[i]=C[i];
	for(int i=1; i<=cnt; ++i) AddEdge(i,i+lim,INF,-A[i]);
	for(int i=1; i<=m+n-1; ++i) AddEdge(id[n][i]+lim,des,INF,0);
	while(SPFA()) res2+=MCMF();

	int res3=0;
	for(int i=2; i<=Enum; ++i) cap[i]=C[i];
	for(int i=0; i<n-1; ++i)
		for(int j=1; j<=i+m; ++j)
			AddEdge(id[i][j]+lim,id[i][j]+i+m/*��Ϊ��n�еı�ŷ�ʽ ������ֱ��id[i+1][j]*/,INF,0),AddEdge(id[i][j]+lim,id[i][j]+i+m+1,INF,0);
	for(int i=1; i<=m+n-1; ++i) AddEdge(id[n][i]+lim,des,INF,0);
	while(SPFA()) res3+=MCMF();

//	int res2=0;
//	Enum=1, memset(H,0,sizeof H);
////	for(int i=1; i<=m; ++i) AddEdge(src,i,INF,-A[i]);//Ҫ���m�����ֿ�ʼ(Ӧ����ָ��ͬ��λ��) 
////	src=des+1, AddEdge(src,0,m,0);
//	for(int i=1; i<=m; ++i) AddEdge(src,i,1,-A[i]);
//	for(int i=0; i<n-1; ++i)
//		for(int j=1; j<=i+m; ++j)
//			AddEdge(id[i][j],id[i][j]+i+m,1,-A[id[i][j]+i+m]),AddEdge(id[i][j],id[i][j]+i+m+1,1,-A[id[i][j]+i+m+1]);
//	for(int i=1; i<=m+n-1; ++i) AddEdge(id[n][i],des,INF,0);
//	while(SPFA()) res2+=MCMF();
//
//	int res3=0;
//	Enum=1, memset(H,0,sizeof H);
//	for(int i=1; i<=m; ++i) AddEdge(src,i,1,-A[i]);
//	for(int i=0; i<n-1; ++i)
//		for(int j=1; j<=i+m; ++j)
//			AddEdge(id[i][j],id[i][j]+i+m,INF,-A[id[i][j]+i+m]),AddEdge(id[i][j],id[i][j]+i+m+1,INF,-A[id[i][j]+i+m+1]);
//	for(int i=1; i<=m+n-1; ++i) AddEdge(id[n][i],des,INF,0);
//	while(SPFA()) res3+=MCMF();

	printf("%d\n%d\n%d",-res1,-res2,-res3);

	return 0;
}
