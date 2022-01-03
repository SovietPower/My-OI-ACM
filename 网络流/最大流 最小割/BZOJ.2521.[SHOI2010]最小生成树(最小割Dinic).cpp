/*
876kb	60ms
status�����ô����ô�죿~~������һ��20��Ҳ60+~~
һ���߲��������߼��ٿ��Կ���һ�������������߲��䡣
����Ҫ�ӵı�labΪ(A->B,v)����ô�϶���Ҫʹ���������⣬A->B��ÿ��·���ϵ���СȨֵ��>v����������ͨA,Bʱ(��Kruskal��Union())��һ����ѡ�������ߡ�
Ҫ��·������С�ߵ�Ȩֵ>v����Ҫ����·����������һ��Ȩֵ<=vʱ����ͨ����������С��(ʹ������ͨ)�����һ���ߵĴ��ۼ�v[lab]-v[i]+1��
����ͼ��˫��ߡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=505,M=3215;

int n,m,lab,s[805],t[805],v[805];
int src,des,Enum,cur[N],H[N],nxt[M],to[M],cap[M],lev[N],que[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	for(int i=1; i<=n; ++i) lev[i]=0,cur[i]=H[i];
	lev[src]=1, que[0]=src; int h=0,t=1;
	while(h<t)
	{
		int x=que[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(!lev[to[i]] && cap[i])
			{
				lev[to[i]]=lev[x]+1, que[t++]=to[i];
				if(to[i]==des) return 1;
			}
	}
	return 0;
}
int Dinic(int x,int flow)
{
	if(x==des) return flow;
	int used(0);
	for(int &i=cur[x]; i; i=nxt[i])
		if(lev[to[i]]==lev[x]+1&&cap[i])
		{
			int delta=Dinic(to[i],std::min(flow-used,cap[i]));
			if(delta)
			{
				cap[i]-=delta, cap[i^1]+=delta;
				if((used+=delta)==flow) return flow;
			}
		}
	lev[x]=0;
	return used;
}

int main()
{
	n=read(),m=read(),lab=read(),Enum=1;
	for(int i=1; i<=m; ++i) s[i]=read(),t[i]=read(),v[i]=read();
	src=s[lab], des=t[lab];
	for(int i=1; i<=m; ++i)
		if(i!=lab&&v[i]<=v[lab]) AddEdge(s[i],t[i],v[lab]-v[i]+1),AddEdge(t[i],s[i],v[lab]-v[i]+1);
	int res=0;
	while(BFS()) res+=Dinic(src,1e9);
	printf("%d",res);

	return 0;
}
