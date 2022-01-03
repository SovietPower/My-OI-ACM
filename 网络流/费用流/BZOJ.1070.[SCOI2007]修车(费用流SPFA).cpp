/*
��tm������*2����
������Աi����ά��W1,W2,...,Wn����ô���ѵ�ʱ���� W1 + W1+W2 + W1+W2+W3... = W1*n + W2*(n-1) + ... + Wn*1
����j�ǵ�a���޵� �����Ĺ�����(n-a+1)*t[i][j] 
��j�ǵ�����a���޵� �����Ĺ�����a*t[i][j] 
ÿ����Ա�������������Կ��԰�ǰ�ߵĳ��������£���һ����Ա���n����ʾn���׶�(i�׶α�ʾ������i����)��ÿ�����ֱ������� 

ע: ��ı�� & ����q[]��Ρ�����Ū����
*/
#include<queue>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=700,M=50000,INF=0x3f3f3f3f;

int n,m,src,des,Enum,H[N],fr[M<<1],to[M<<1],nxt[M<<1],cap[M<<1],cost[M<<1];
int dis[N],pre[N];
std::queue<int> q;
bool inq[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int c)
{
	to[++Enum]=v, nxt[Enum]=H[u], fr[Enum]=u, cap[Enum]=1, cost[Enum]=c, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], fr[Enum]=v, cap[Enum]=0, cost[Enum]=-c, H[v]=Enum;
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
				if(!inq[to[i]]) inq[to[i]]=1, q.push(to[i]);
			}
	}
	return dis[des]<INF;
}
int MCMF()
{
	int c=0;
//	for(int i=des;i!=src;i=fr[pre[i]])
//		mn=std::min(mn,cap[pre[i]]);
	for(int i=des;i!=src;i=fr[pre[i]])
		--cap[pre[i]],++cap[pre[i]^1],c+=cost[pre[i]];
	return c;
}

int main()
{
	Enum=1;
	m=read(),n=read();
	for(int t,i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			t=read();
			for(int k=1;k<=n;++k)
				AddEdge(i,n*(j+1)-k+1,k*t);
		}
	src=0, des=n*(m+1)+1;
	for(int i=1;i<=n;++i) AddEdge(src,i,0);
	for(int i=n+1;i<des;++i) AddEdge(i,des,0);
	int res=0;
	while(SPFA()) res+=MCMF();
	printf("%.2lf",1.0*res/n);

	return 0;
}
