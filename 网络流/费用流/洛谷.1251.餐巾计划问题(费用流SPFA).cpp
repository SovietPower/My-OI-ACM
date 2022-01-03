/*
ÿһ��Ĳͽ������൱�ڱ������ĳЩ�����ɴ� 
��q[i]ΪDayi������ (x,y)��ʾ��x��y�� 
��ÿ����i���i,i'����i'->T��(q[i],0)�ıߣ���ʾ��������Ļ�һ��Ҫ����q[i] 
����i����S->i��(q[i],0)�ıߣ���ʾ����Dayi�������໹�ܸ���q[i]��ͽ�(�о�INF����also ok?) 
�������ַ�ʽ: 
����(��p��һ��ͽ�): ��S->i'��(INF,p)����ʾ����ֱ�ӻ�p����Dayi������ 
�͵���ϴ��(a��ϴ�� ÿ�黨b): ��i->(i'+a)��(INF,b)����ʾ����һ�黨b����Day(i+a) 
�͵���ϴ��(c��ϴ�� ÿ�黨d): ��i->(i'+c)��(INF,d)����ʾ����һ�黨d����Day(i+c) 
ע��ĳ��Ĳͽ����������һ�죬����i->i+1��(INF,0)(Ҳ����i'->(i+1)') 
Ҳ����̰��+����...
ע������(����)�Ƚϴ�Ҫlonglong 
*/
#include<queue>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5000,M=6*N,INF=0x3f3f3f3f;

int n,m,src,des,dis[N],pre[N];
int Enum,H[N],nxt[M<<1],fr[M<<1],to[M<<1],cap[M<<1],cost[M<<1];
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
	to[++Enum]=v, fr[Enum]=u, cap[Enum]=w, cost[Enum]=c, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, fr[Enum]=v, cap[Enum]=0, cost[Enum]=-c, nxt[Enum]=H[v], H[v]=Enum;
}
bool SPFA()
{
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		inq[x]=0;
		for(int i=H[x];i;i=nxt[i])
			if(cap[i] && dis[to[i]]>dis[x]+cost[i])
			{
				dis[to[i]]=dis[x]+cost[i], pre[to[i]]=i;
				if(!inq[to[i]]) inq[to[i]]=1,q.push(to[i]);
			}
	}
	return dis[des]<INF;
}
LL MCMF()
{
	int mn=INF; LL c=0;
	for(int i=des;i!=src;i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des;i!=src;i=fr[pre[i]])
		cap[pre[i]]-=mn,cap[pre[i]^1]+=mn,c+=1LL*mn*cost[pre[i]];
	return c;
}

int main()
{
	Enum=1;
	n=read();
	src=0, des=n<<1|1;
	for(int a,i=1;i<=n;++i)
		a=read(),AddEdge(src,i,a,0),AddEdge(i+n,des,a,0);
	int p=read(),a=read(),b=read(),c=read(),d=read();
	for(int i=1;i<=n;++i) AddEdge(src,i+n,INF,p);
	for(int i=1;i<n;++i) AddEdge(i,i+1,INF,0);
	for(int i=1;i<=n-a;++i) AddEdge(i,i+n+a,INF,b);
	for(int i=1;i<=n-c;++i) AddEdge(i,i+n+c,INF,d);
	LL res=0;
	while(SPFA()) res+=MCMF();
	printf("%lld",res);

	return 0;
}
