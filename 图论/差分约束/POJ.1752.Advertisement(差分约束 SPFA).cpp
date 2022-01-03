/*
1240K	735MS
$Description$
��$n$������һ��ֱ�����ܲ���ÿ���˵���� $Si$���յ� $Ei$ ��֪��ÿ������Է�һ������ƣ�һ����$i$�ܿ����Ĺ��������Ϊ $Ei-Si+1$��
Ҫ��ʹÿ���˿����Ĺ����������С�� $k$ (�� $Ei-Si+1<k$ ��Ӧ���� $Ei-Si+1$)�����������Ҫ���ٹ���Ƽ�������
$Solution$
�� $Sum_i$ ��ʾ�� $[1,i]$ �������������ô�������� $Sum_{Ei}-Sum_{Si-1}>=k$�����Ƕ��� $Ei-Si+1>=k$ �� 
�� $C=Ei-Si+1$����C<k���� $Sum_{Ei}-Sum_{Si-1}=C$���������ʽ�� 
ͬʱÿ��λ�õ����� $0<=Sum_i-Sum_{i-1}<=1$
�� $Sum_i$ Ϊ�㽨�ߣ��� $Sum_0$ -> $Sum_n$ ���·��Ϊ������Ҫ���� 
�������: ��$i$�����˹���ƣ����� $dis_i-dis_{i-1}=1$ 

ע�⣬Dijkstra�����������· 
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=10005,M=60005,INF=0x3f3f3f3f;

int n,K,Enum,H[N<<1],nxt[M],to[M],val[M],dis[N<<1];
bool vis[N<<1];
//std::priority_queue<pr> q;
std::queue<int> que;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
}
//int Dijkstra(int mn,int mx)
//{
//	for(int i=mn+1; i<=mx; ++i) dis[i]=-INF;
//	q.push(mp(0,mn));
//	while(!q.empty())
//	{
//		int x=q.top().second;q.pop();
//		if(vis[x]) continue;
//		vis[x]=1;
//		for(int i=H[x]; i; i=nxt[i])
//			if(dis[to[i]]<dis[x]+val[i])
//			{
//				dis[to[i]]=dis[x]+val[i];
//				if(!vis[to[i]]) q.push(mp(dis[to[i]],to[i]));
//			}
//	}
//	return dis[mx];
//}
int SPFA(int mn,int mx)
{
	for(int i=mn+1; i<=mx; ++i) dis[i]=-INF;
	que.push(mn);
	while(!que.empty())
	{
		int x=que.front();que.pop();
		vis[x]=0;
		for(int i=H[x]; i; i=nxt[i])
			if(dis[to[i]]<dis[x]+val[i])
			{
				dis[to[i]]=dis[x]+val[i];
				if(!vis[to[i]]) que.push(to[i]),vis[to[i]]=1;
			}
	}
	return dis[mx];
}

int main()
{
	K=read(),n=read();
	int mx=0,mn=N<<1;
	for(int st,ed,t,i=1; i<=n; ++i)
	{
		st=read()+N, ed=read()+N;
		if(st>ed) std::swap(st,ed);
		mn=std::min(mn,--st), mx=std::max(mx,ed);
		if((t=ed-st)<K) AddEdge(st,ed,t),AddEdge(ed,st,-t);
		else AddEdge(st,ed,K);
	}
	mn-=2;
	for(int i=mn; i<=mx; ++i) AddEdge(i-1,i,0),AddEdge(i,i-1,-1);
	printf("%d\n",SPFA(mn,mx));
	for(int i=mn; i<=mx; ++i)
		if(dis[i]==dis[i-1]+1) printf("%d\n",i-N);
	return 0;
}
