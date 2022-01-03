/*
3212kb	112ms
����Ȼ�Ľ�����ͼ�����������������и�������һ������ֻ����һ�εģ���������ͼ�����ֶ����������
��ô���������ġ����$i$������$j'$���ߣ�$j$Ҳ��$i'$���ߣ������һ������$i->j'$����ô��һ��һ����$j->i'$��
ÿ��������������ֱ����һ�η��ñ�ɸ���Ȼ����ϵ�ǰ��Ȩֵ�ܵ��������������������������2�Ϳ����ˡ�

Another Solution:
��������ƥ������Ҫ������������������������ӵĴ�����һ��ֻ���1.
���ǿ��԰������������ż�Խ�����ͼ���ֱ���Դ���㣬ͬ���������Ϳ����ˡ�

ps:sb����Ӳ�ǰ�i->j�ķ������0��Ȼ��Դ������log(b[i])�ıߣ�Ȼ����ȡ�ݡ������д�귢�ֲ��ԣ����ᴦ����������⡣��̰��Ҳ�����ԡ�
����ƥ��$O(sqrt(n))$ֱ��ö�پͿ��ԣ��е�дʲôMillerRabin+set����
*/
#include <set>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=410,M=100005,INF=1e9;
const int P[9]={2,3,5,7,13,17,31};

int n,src,des,A[N],B[N],C[N],Enum,H[N],nxt[M],fr[M],to[M],cap[M],pre[N];
bool inq[N];
LL dis[N],cost[M];
std::queue<int> q;
std::set<int> is_p[2];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w,LL c)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
int FP(LL x,int k,int p)
{
	LL t=1;
	for(; k; k>>=1,x=x*x%p)
		if(k&1) t=t*x%p;
	return (int)t;
}
bool Miller_Rabin(int x)
{
	if(x==2) return 1;
	if(!(x&1)||x==1) return 0;
	for(int i=0; i<7; ++i)
		if(x==P[i]) return 1;
		else if(!(x%P[i])) return 0;
	int u=x-1,t=0;
	while(!(u&1)) u>>=1,++t;
	for(int i=0; i<7; ++i)
	{
		LL now=FP(P[i],u,x),las;
		for(int j=1; j<=t; ++j)
		{
			las=now, (now*=now)%=x;
			if(now==1&&las!=1&&las!=x-1) return 0;
		}
		if(now!=1) return 0;
	}
	return 1;
}
bool SPFA()
{
	for(int i=1; i<=des; ++i) dis[i]=-1e12;
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int v,i=H[x]; i; i=nxt[i])
			if(cap[i]&&dis[to[i]]<dis[x]+cost[i])
			{
				dis[v=to[i]]=dis[x]+cost[i], pre[v]=i;
				if(!inq[v]) q.push(v),inq[v]=1;
			}
	}
	return dis[des]>-1e12;
}
LL Solve()
{
	int flow=0,mn;
	LL sum_cost=0;
	while(SPFA())
	{//ע����ֻ��һ������ͼ����
		mn=1e9;
		for(int i=des; i!=src; i=fr[pre[i]]) mn=std::min(cap[pre[i]],mn);
		if(sum_cost+1ll*dis[des]*mn>=0){//dis[des]���Ƿ��á�
			for(int i=des; i!=src; i=fr[pre[i]]) cap[pre[i]]-=mn,cap[pre[i]^1]+=mn;
			sum_cost+=1ll*dis[des]*mn, flow+=mn;
		}
		else{
			flow+=(int)(sum_cost/std::abs(dis[des]));//����ʣ������ֵ�ܲ����ٸ�ֵ��
			break;
		}
	}
	return flow>>1;
}

int main()
{
	n=read(),Enum=1,src=0,des=n<<1|1;
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) B[i]=read();
	for(int i=1; i<=n; ++i) C[i]=read();
	for(int i=1; i<=n; ++i) AddEdge(src,i,B[i],0),AddEdge(i+n,des,B[i],0);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(A[i]>A[j]&&!(A[i]%A[j]))
			{
				int t=A[i]/A[j];
				if(is_p[0].count(t)) continue;
				if(is_p[1].count(t)) AddEdge(i,j+n,INF,1ll*C[i]*C[j]),AddEdge(j,i+n,INF,1ll*C[i]*C[j]);
				else{
					bool f=Miller_Rabin(t);
					if(f) is_p[1].insert(t),AddEdge(i,j+n,INF,1ll*C[i]*C[j]),AddEdge(j,i+n,INF,1ll*C[i]*C[j]);
					else is_p[0].insert(t);
				}
			}
	printf("%lld",Solve());

	return 0;
}
