/*
3624kb	4016ms
01分数规划。要跑最大费用最大流。
输出的时候最好加个eps，不然可以被卡。
当然还可以写整数二分或者KM...
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define eps 1e-7
#define INF 1e14
const int N=205,M=90000;

int n,src,des,Enum,H[N],to[M],fr[M],nxt[M],cap[M],pre[N];
bool inq[N];
double Ans,dis[N],A[N][N],B[N][N],cost[M];
std::queue<int> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w,double c)
{
	to[++Enum]=v, nxt[Enum]=H[u], fr[Enum]=u, H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, nxt[Enum]=H[v], fr[Enum]=v, H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	for(int i=1; i<=des; ++i) dis[i]=-INF;
	q.push(src), dis[src]=0;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		inq[x]=0;
		for(int v,i=H[x]; i; i=nxt[i])
			if(dis[to[i]]<dis[x]+cost[i] && cap[i])
			{
				dis[v=to[i]]=dis[x]+cost[i], pre[v]=i;
				if(!inq[v]) inq[v]=1,q.push(v);
			}
	}
	return dis[des]>-INF;
}
void MCMF(){
	for(int i=des; i!=src; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1], Ans+=cost[pre[i]];
}
bool pre_Check(double C)
{
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			/*if(i!=j) j是女生，不是自己。。*/ 
			AddEdge(i,j+n,1,A[i][j]-C*B[i][j]);
	for(int i=1; i<=n; ++i) AddEdge(src,i,1,0),AddEdge(i+n,des,1,0);
	Ans=0;
	while(SPFA()){
		MCMF();
		if(Ans<0) break;
	}
	return Ans>=0;
}
bool Check(double C)
{
	int cnt=1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			cap[++cnt]=1, cost[cnt]=A[i][j]-C*B[i][j], cap[++cnt]=0, cost[cnt]=-A[i][j]+C*B[i][j];
	for(int i=1; i<=n; ++i)
		cap[++cnt]=1, cost[cnt]=0, cap[++cnt]=0, cost[cnt]=0,
		cap[++cnt]=1, cost[cnt]=0, cap[++cnt]=0, cost[cnt]=0;
	Ans=0;
	while(SPFA()){
		MCMF();
		if(Ans<0) break;
	}
	return Ans>=0;
}

int main()
{
	n=read(),Enum=1,src=0,des=n<<1|1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) A[i][j]=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) B[i][j]=read();
	double l=0,r=10000.1,mid;
	if(pre_Check(mid=(l+r)*0.5)) l=mid;
	else r=mid;
	while(r>l+eps)
		if(Check(mid=(l+r)*0.5)) l=mid;
		else r=mid;
	printf("%.6lf",l+eps);

	return 0;
}
