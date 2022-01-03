/*
每一天的餐巾需求相当于必须遍历某些点若干次 
设q[i]为Dayi需求量 (x,y)表示边x容y费 
将每个点i拆成i,i'，由i'->T连(q[i],0)的边，表示求最大流的话一定要流满q[i] 
对于i，由S->i连(q[i],0)的边，表示满足Dayi需求后最多还能给出q[i]块餐巾(感觉INF好像also ok?) 
对于三种方式: 
购买(花p买一块餐巾): 由S->i'连(INF,p)，表示可以直接花p供给Dayi的需求 
送到快洗部(a天洗完 每块花b): 由i->(i'+a)连(INF,b)，表示给以一块花b供给Day(i+a) 
送到慢洗部(c天洗完 每块花d): 由i->(i'+c)连(INF,d)，表示给以一块花d供给Day(i+c) 
注意某天的餐巾可以留到下一天，所以i->i+1连(INF,0)(也可以i'->(i+1)') 
也可以贪心+三分...
注意数据(流量)比较大要longlong 
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
