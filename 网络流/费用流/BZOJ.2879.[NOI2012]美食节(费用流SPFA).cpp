/*
ͬ"�޳�":����ÿ����ʦ���p�����ʾp��ʱ��㣬ÿ������m����ʦÿ��ʱ������� 
��������O(nmp)+������ ��O(nm*p^2)(����SPFA����) = GG 
���Է�����O(nmp)���ߴ�������ò����� 
���Կ���ֻ�������ߣ�ÿ����һ��·��O(n)���� 
���ӶȾ���O(nmp+p^2) 
ע: �ӱ߻��ǲ���ֻ��һ��(��һ����ʦ�½�һ�㣬����Ϊ�ϴη���) 
��Ϊ��"�޳�"�з������ǣ���������W1,W2,...,Wn�Ĺ��ף����������Ĵ� 
��һ��ֻ����һ�� ��ÿ��ֻ���ǵ�ǰ���Ž⣬��Ȼ���� 
��Ҫ��¼�ϴεĳ�ʦ���ĸ�����Ϊ��Ż��� 
*/
#include<queue>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=2000,M=50000,INF=0x3f3f3f3f;

int n,m,tot,src,des,Enum,H[N],fr[M<<1],to[M<<1],nxt[M<<1],cap[M<<1],cost[M<<1];
int dis[N],pre[N],tm[105][105],freq[N],orig[N];
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
int MCMF()
{
	int mn=INF,c=0;
	for(int i=des;i!=src;i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des;i!=src;i=fr[pre[i]])
		cap[pre[i]]-=mn,cap[pre[i]^1]+=mn,c+=mn*cost[pre[i]];
	int x=fr[pre[des]], anc=orig[x];
	orig[++tot]=anc, ++freq[anc];
	for(int i=1;i<=n;++i) AddEdge(i,tot,1,freq[anc]*tm[i][anc]);
	AddEdge(tot,des,1,0);
//WA:AddEdge(x,++tot,INF,c), AddEdge(tot,des,1,0);//Update
//	for(int i=des;i!=src;i=fr[pre[i]])
//		if(i>n) printf("%d'->",i-n);
//		else printf("%d->",i);
//	printf("%d :%d\n",src,c);
	return c;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("28792.in","r",stdin);
#endif

	Enum=1;
	n=read(),m=read();
	src=0, des=n+m+1, tot=des;
	for(int i=1;i<=n;++i) AddEdge(src,i,read(),0);
	for(int t,i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			AddEdge(i,n+j,INF,(tm[i][j]=read()));
	for(int i=n+1;i<des;++i)
		freq[orig[i]=i-n]=1, AddEdge(i,des,1,0);
	int res=0;
	while(SPFA()) res+=MCMF();
	printf("%d",res);

	return 0;
}
