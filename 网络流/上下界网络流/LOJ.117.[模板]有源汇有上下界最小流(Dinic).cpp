/*
��Դ�������½���С�� 
Sol1. ���Ⱥ���Դ��������һ����ͼ����SS->TT�������
Ȼ������(T->S,[0,INF])������һ��SS->TT���������Ϊ����ӱߵ����� 
�޽����: ���ߺ����������+֮ǰ������� != ��dgr[](dgr>0) 
����: ��һ��������Ѿ������½磬�����½������������ı��Ѿ������� 
��ô���������������ͻᾡ����С�� 

Sol2. ���Ⱥ���Դ��������һ����ͼ��Ȼ������(T->S,[0,INF])����SS->TT�������okflow 
Ȼ��ɾȥT->S�������ߣ���T->S�������mn�����Ϊokflow-mn 
����: ��һ�������������ʹ�����������½磻
�ڶ������� ��������������=����������ļ��٣���T->S�����������S->T����ܼ��ٵ�����(���������) 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5e4+9,M=125009+N;
const LL INF=1e14;

int n,m,src,des,Enum,H[N],nxt[M<<1],to[M<<1],lev[N],cur[N],q[N],dgr[N];
LL cap[M<<1];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,LL w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
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
			if(!lev[to[i]]&&cap[i])
			{
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
				if(to[i]==des) return 1;
			}
	}
	return 0;
}
LL Dinic(int u,LL flow)
{
	if(u==des) return flow;
	LL used=0;
	for(int &i=cur[u];i;i=nxt[i])
		if(lev[to[i]]==lev[u]+1 && cap[i])
		{
			LL delta=Dinic(to[i],std::min(cap[i],flow-used));
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
	n=read(),m=read();int s=read(),t=read(),ss=0,tt=n+1;
	LL low,upp,sum=0,okflow=0;
	for(int u,v,i=1;i<=m;++i)
	{
		u=read(),v=read(),low=read(),upp=read(),
		dgr[u]-=low,dgr[v]+=low, AddEdge(u,v,upp-low);
	}
	for(int i=1;i<=n;++i)
		if(dgr[i]>0) AddEdge(ss,i,dgr[i]),sum+=dgr[i];
		else if(dgr[i]<0) AddEdge(i,tt,-dgr[i]);
	src=ss, des=tt;
	while(BFS()) okflow+=Dinic(src,INF);
	AddEdge(t,s,INF);
	while(BFS()) okflow+=Dinic(src,INF);
	if(okflow==sum) printf("%lld",cap[Enum]);
	else printf("please go home to sleep");

	return 0;
}
