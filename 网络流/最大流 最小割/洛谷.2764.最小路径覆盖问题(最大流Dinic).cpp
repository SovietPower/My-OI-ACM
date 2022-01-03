/*
��С·�����ǣ�����ͼ���Ҿ����ٵ�·����ʹ��ÿ�����ǡ����һ��·���ϣ���ͬ��·�������й����㣩��ע�⣬�����Ľ��Ҳ������Ϊһ��·���� 
(DAG)��С·�������� = ����n - ���ƥ����m 
֤������Ϊƥ���·�������������Ӧ������·�������е�ÿһ����·�����������һ������β�ڵ㡱�ⶼ��Ψһ�ĺ�������Ӧ(��ƥ��ڵ�) 
����ƥ����Ƿǽ�β�ڵ�ĸ���(׼ȷ�Ļ�ƥ����Ҫ����ż������ ��������) 
��ƥ�� ���ǽ�β�ڵ���Խ��ʱ����β�ڵ�����Խ�٣�·��������Խ�� 
��תΪ�����ͼ���ƥ�� 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
const int N=155*2,M=155*158,INF=1e5;

int n,m,src,des,Link[N],Enum,cur[N],H[N],nxt[M<<1],to[M<<1],cap[M<<1],lev[N],q[N];
bool Mark[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}

bool BFS()
{
	for(int i=src;i<=des;++i) cur[i]=H[i],lev[i]=0;
	lev[src]=1, q[0]=src;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(cap[i] && !lev[to[i]])
			{
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
				if(to[i]==des) return 1;
			}
	}
	return 0;
}
int Dinic(int u,int flow)
{
	if(u==des) return flow;
	int used=0;
	for(int &i=cur[u];i;i=nxt[i])
		if(cap[i] && lev[to[i]]==lev[u]+1)
		{
			int delta=Dinic(to[i],std::min(flow-used,cap[i]));
			if(delta)
			{
				if(to[i]>n) Link[u]=to[i], Mark[to[i]]=1;
				used+=delta, cap[i]-=delta, cap[i^1]+=delta;
				if(used==flow) return flow;
			}
		}
	lev[u]=0;
	return used;
}

int main()
{
	n=read(),m=read(),src=0,des=n+n+1;
	int u,v;
	while(m--)
		u=read(),v=read(),AddEdge(u+n,v,1);
	for(int i=1;i<=n;++i) AddEdge(src,i,INF);
	for(int i=n+1;i<des;++i) AddEdge(i,des,INF);
	int res=n;
	while(BFS()) res-=Dinic(src,INF);
	for(int i=n+1;i<des;++i)
	{
		if(Mark[i]) continue;
		int k=i-n;
		while(k)
			printf("%d ",k),k=Link[k]-n;
		putchar('\n');
	}
	printf("%d",res);

	return 0;
}
