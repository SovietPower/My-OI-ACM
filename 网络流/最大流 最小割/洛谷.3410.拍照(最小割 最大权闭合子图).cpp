/*
���Ȩ�պ���ͼ����һ������ͼ��ÿ�����е�Ȩ���е�Ϊ���е�Ϊ������������һ�������(i,j)��ѡ���˵�i�ͱ���ѡ���j 
���ۣ���ÿ����Ȩ��i����s��i��һ������Ϊw[i]�ıߣ�����ÿ����Ȩ��j����j��t��һ������Ϊabs(w[j])�ı� 
����ԭͼ�ıߣ�����������ΪINF�� 
���Ȩ = ��Ȩ�� - ����� 
֤��������������Ϊ��С���ô��ȥ�ı�һ��������INF�ı� 
ѡ��һ����Ȩ�㼴���������s�ıߣ�ѡ��һ����Ȩ�㼴�������t�ı� 
���ѡ����һ����Ȩ��i����ѡ��Ȩ��j(i,j�б�)���������s��i�ıߣ�ͬʱ�����j��t�ıߣ�s��t��ͨ����������С��� 
�����ѡ��Ȩ��i��ѡ��Ȩ��j�������s��i�ıߣ�ͬʱ���j��t�ıߣ�s��t����ͨ�����ǲ����j��t�ı�Ҳ�ܱ�֤s��t��ͨ�������������С 
(�����ܱ�֤ѡ�˵������Ӧ�ĸ��㶼��ѡ��ͬʱ��õ�Ȩֵ���(������Ȩֵ����))
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=205,M=102*102*2,INF=0x3f3f3f3f;

int n,m,src,des,cost[N],H[N],cur[N],Enum,to[M],cap[M],nxt[M],q[N],lev[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
		if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum] = v;
	nxt[Enum] = H[u];
	cap[Enum] = w;
	H[u] = Enum;
}

bool BFS()
{
	for(int i=src;i<=des;++i) cur[i]=H[i], lev[i]=0;
	int h=0,t=1,x;
	q[0]=src, lev[src]=1;
	while(h<t)
	{
		x=q[h++];
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
			int delta=Dinic(to[i],min(flow-used,cap[i]));
			if(delta)
			{
				cap[i]-=delta, cap[i^1]+=delta, used+=delta;
//				printf("%d %d %d\n",u,delta,used);
				if(used==flow) return flow;
			}
		}
	lev[u]=0;
	return used;
}

int main()
{
	n=read(),m=read();
	src=0, des=n+m+1, Enum=1;
	int tot=0;
	for(int u,v,i=1;i<=n;++i)
	{
		v=read(),u=read(), tot+=v;
		AddEdge(0,i,v), AddEdge(i,0,0);
		while(u) AddEdge(i,u+n,INF),AddEdge(u+n,i,0), u=read();
	}
	for(int i=1;i<=m;++i) cost[i]=read();
	for(int i=n+1;i<des;++i) AddEdge(i,des,cost[i-n]), AddEdge(des,i,0);
	int res=0;
	while(BFS())
		res+=Dinic(src,INF);
	printf("%d",tot-res);

	return 0;
}
