/*
http://blog.csdn.net/just_sort/article/details/75448403
��Դ�������½������� ͨ�����һ��(T->S,[0,INF])�ı߱����Դ�� 
Sol1. ���(T->S,[0,INF])�ĵıߺ󣬰���Դ���������ͼ����һ��SS->TT���������������ʱflow=��dgr[](dgr>0)ʱ�н⣻
���н⣬ɾ��(T->S,[0,INF])�������ߣ���ʱS->T�������+֮ǰ��flow ���Ǵ� 
����: ��Ӹ���Դ����Ϊ����������ƽ������������ͼ����Ӧ�Ĳ�������� 
ֻҪ���Ӹ���Դ��ı�����������ͼ��S->T������һ�ֿ���������ԭͼ�Ŀ����� 
����SS->TT����������൱����ʹ���Ӹ���Դ��ı����������������һ�ֿ����� 
�ٽ�T->S�ı߲������ʹS->T���һ����Դ��������ͼ����S->T�������������֮ǰ�Ŀ����������������� 

ע��ɾ�ߵ�ʱ��Ҫɾ��SS��TT�����бߣ�
���ǵڶ���ֱ����S->T������� ������+�������������� ���Ǵ�(��ΪSS��TT���Ѿ�������)��
ɾ�߲�̫���ס���
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=207,M=1e4+5+N,INF=0x7fffffff;

int n,m,src,des,H[N],Enum,cap[M<<1],to[M<<1],nxt[M<<1];
int q[N],lev[N],cur[N],dgr[N];
//bool id[M<<1];

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
//	id[Enum]=i;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
//	id[Enum]=i;
}
bool BFS()
{
	for(int i=0;i<=n+1;++i) lev[i]=0,cur[i]=H[i];
	lev[src]=1, q[0]=src;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(!lev[to[i]] && cap[i])
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
		if(lev[to[i]]==lev[u]+1 && cap[i])
		{
			int delta=Dinic(to[i],std::min(flow-used,cap[i]));
			if(delta)
			{
				cap[i]-=delta, cap[i^1]+=delta, used+=delta;
				if(used==flow) return flow;
			}
		}
	lev[u]=0;
	return used;
}

int main()
{
	Enum=1;
	n=read(),m=read();int s=read(),t=read();
	int ss=0,tt=n+1,sum=0,okflow=0;
	for(int u,v,low,upp,i=1;i<=m;++i)
	{
		u=read(),v=read(),low=read(),upp=read(),
		dgr[u]-=low,dgr[v]+=low,AddEdge(u,v,upp-low);
	}
	for(int i=1;i<=n;++i)
		if(dgr[i]>0) sum+=dgr[i],AddEdge(ss,i,dgr[i]);
		else if(dgr[i]<0) AddEdge(i,tt,-dgr[i]);
	AddEdge(t,s,INF), src=ss, des=tt;
	while(BFS()) okflow+=Dinic(src,INF);
	if(okflow==sum)
	{
//		printf("%d %d\n",okflow,cap[H[tt]]);
//		okflow=cap[H[tt]];//??
//		H[ss]=H[tt]=0;
//		for(int i=1;i<=Enum;++i)
//			if(!id[i]) to[i]=0;
//		src=s, des=t;
//		while(BFS()) okflow+=Dinic(src,INF);

		src=s, des=t;
		okflow=0;
		while(BFS()) okflow+=Dinic(src,INF);

		printf("%d",okflow);
	}
	else printf("please go home to sleep");

	return 0;
}
