/*
1368kb	24ms
���Ⱥڰ����ӵĽ����ȼ��ں������ڰ׸���ͼ���ƶ���������ָ��λ�á�~~�����������֪������������������~~
��ô���嵽ָ��λ�þ���һ��·����������ô����ģ�������·����
���Ƿ��ֳ���·���������յ�ĸ������Ĵ���Ϊ1��·����������ĸ��ӽ�������Ϊ2��
�����뵽��ÿ������in��out���������޷����ֳ�����Ϊ���/�յ���·����������Ĵ������Ĳ��
���ǲ�������㣬in,x,out��x����ԭ�㣬���x����Ϊlim��in,outƽ��������������Ϊlim/2��
ֱ��lim/2��ô��ע��ÿ����ֻ����Ϊ�����յ�һ�Ρ���x��������ڣ���ô����Ϊ�յ�һ�ζ�����Ϊ��㣬������(in->x,(lim+1)/2),(x->out,lim/2)�����Ǻڵ��ף���������һ�Σ����õ㲻��Ҫ������������lim/2��
���Ѿ���in->x��x->out����1�����ˡ�
������ʼͼ�еĺڵ�i������(S->x(i),1)����������ͼ�еĺڵ�i������(x(i)->T,1)����(u->v,w)��ʾu->v�ĵ���ߣ�����Ϊw��
�������ڵ�i,j������(out(i),in(j),INF)��
����ֻ�������㡣
���������ô��ô��֣������͸�һ��ˮ�Ĳ��е���������
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1300,M=N*24,INF=0x3f3f3f3f;

int n,m,S,T,id[25][25][3],Enum,H[N],cur[N],nxt[M],to[M],cap[M],cost[M],dis[N],Cost;
bool vis[N];
std::queue<int> q;
char st[25][25],ed[25][25];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define AE(u,v,w,c) to[++Enum]=v,nxt[Enum]=H[u],H[u]=Enum,cap[Enum]=w,cost[Enum]=c,to[++Enum]=u,nxt[Enum]=H[v],H[v]=Enum,cap[Enum]=0,cost[Enum]=-c
bool SPFA()
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	dis[S]=0, q.push(S);
	while(!q.empty())
	{
		int x=q.front();
		q.pop(), vis[x]=0;
		for(int v,i=H[x]; i; i=nxt[i])
			if(cap[i] && dis[v=to[i]]>dis[x]+cost[i])
				dis[v]=dis[x]+cost[i], !vis[v]&&(q.push(v),vis[v]=1);
	}
	return dis[T]<INF;
}
int DFS(int x,int f)
{
	if(x==T) return f;
	vis[x]=1;
	for(int &i=cur[x],v,tmp; i; i=nxt[i])
		if(cap[i] && !vis[v=to[i]] && dis[v]==dis[x]+cost[i])
			if(tmp=DFS(v,std::min(cap[i],f)))
				return cap[i]-=tmp,cap[i^1]+=tmp,Cost+=tmp*cost[i],tmp;
	return 0;
}
int MCMF()
{
	int res=0;
	while(SPFA())
	{
		for(int i=S; i<=T; ++i) cur[i]=H[i];
		while(int tmp=DFS(S,INF)) res+=tmp;
	}
	return res;
}

int main()
{
	n=read(),m=read(),Enum=1,S=0,T=n*m*3+1;
	for(int i=1; i<=n; ++i) scanf("%s",st[i]+1);
	for(int i=1; i<=n; ++i) scanf("%s",ed[i]+1);
	int tot=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			id[i][j][0]=++tot,id[i][j][1]=++tot,id[i][j][2]=++tot;
	int tot1=0, tot2=0;
	for(int i=1; i<=n; ++i)//0:x 1:in 2:out
	{
		char c=gc();
		for(; !isdigit(c); c=gc());
		for(int j=1; j<=m; ++j, c=gc())
		{
			const char s=st[i][j],t=ed[i][j];
			const int x=id[i][j][0],in=id[i][j][1],out=id[i][j][2],lim=c-'0';
			if(s=='1') AE(S,x,1,0), ++tot1;
			if(t=='1') AE(x,T,1,0), ++tot2;
			if(s=='1'&&t=='0') AE(in,x,lim>>1,1), AE(x,out,lim+1>>1,1);
			else if(s=='0'&&t=='1') AE(in,x,lim+1>>1,1), AE(x,out,lim>>1,1);
			else AE(in,x,lim>>1,1), AE(x,out,lim>>1,1);
			if(i<n) AE(out,id[i+1][j][1],INF,0), AE(id[i+1][j][2],in,INF,0);//ͬɫ�ĵ�ȻҲ��������(��ɶ�ء�_��)
			if(i<n&&j<m) AE(out,id[i+1][j+1][1],INF,0), AE(id[i+1][j+1][2],in,INF,0);
			if(i<n&&j>1) AE(out,id[i+1][j-1][1],INF,0), AE(id[i+1][j-1][2],in,INF,0);
			if(j<m) AE(out,id[i][j+1][1],INF,0), AE(id[i][j+1][2],in,INF,0);
		}
	}
	printf("%d\n",(tot1==tot2&&MCMF()==tot1)?Cost>>1:-1);

	return 0;
}
