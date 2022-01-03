/*
576ms	9300KB
$Description$
����һ��ͼ����1���뻨��1ʱ�䡣H��1�ŵ���һ�������ꡣ��$k$��������ÿ���������յ�����ʱ��$s_i$�����͵���λ��$u_i$�����������õ�ʱ��$t_i$��
����$i$��$t_i$ʱ����1�ŵ����ú�H������1�ŵ��������������ȥ�͡�ÿһʱ��H���Դ��������������������ϸ��ն���˳����������
��С�� ÿ�������õ���������ĵȴ�ʱ������ֵ��
$Solution$
��Ϊ�ϸ���˳�������������Կ���$f[i]$��ʾ����ǰ$i$��������������$u_i$λ����������ʱ�䡣
����ôʹ���ֵ��С���ء������ִ�$x$�����͵�ʱ��Ϊ$p_i$������$x-s_i\geq p_i$����$x-p_i\geq s_i$�����ת�ơ�
��$d_{i,j}$Ϊ$i$��$j$���롣Ȼ����һ������$i+1~j$������ȥ�ͣ�����ʱ����$d_{1,i}+\max_{k=i+1~j}t_k+d_{i+1,i+1}+...+d_{j-1,j}$����ÿ��$l��[i+1,j]$Ҫ��$x-(f[i]+d_{1,i}+\max_{k=i+1~l}t_k+d_{i+1,i+1}+...+d_{l-1,l})-s_i\geq 0$��
����ֻҪ��$f[i]$ȥ���θ���$f[j](j>i)$ʱ����ά������������֤��������������ת�ƾͺ��ˡ��������岻��д�ˡ�����
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define pc putchar
#define pr std::pair<LL,LL>
using namespace std;
typedef long long LL;
const int N=1005,M=1e5+6;
const LL INF=1e16;

int Enum,H[N],nxt[M],to[M],val[M],u[N],s[N],t[N];
LL d[N][N],dis[N],f[N];
bool vis[N];
std::priority_queue<pr> q;

inline int read()
{
	int now=0; char c=gc();
	for(; !isdigit(c); c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void Dijkstra(int s)
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	dis[s]=0, q.push(pr{0,s});
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+val[i])
				dis[v]=dis[x]+val[i], q.push(pr{-dis[v],v});
	}
}
bool Check(LL x,int n)
{
	if(x+s[1]-(t[1]+d[1][u[1]])<0) return 0;
	f[0]=0;
	for(int i=1; i<=n; ++i) f[i]=INF;
	for(int i=0; i<n; ++i)
	{
		if(f[i]==INF) continue;
		int maxt=0,pi=u[i];
		LL sum=0,now=INF,nowmax=0,tmp=f[i]+d[1][pi];
		for(int j=i+1; j<=n; ++j)
		{
			int pj=u[j];
			if(j!=i+1) sum+=d[u[j-1]][pj];
			else sum+=d[1][pj];
			maxt=std::max(maxt,t[j]);
			now=std::min(now,x+s[j]-tmp-sum);
			nowmax=std::max(nowmax,std::max(maxt-tmp,0ll));
			if(now<nowmax) break;
			if((x+s[j])-(tmp+sum+std::max(maxt-tmp,0ll))>=0)
				f[j]=std::min(f[j],f[i]+d[1][pi]+sum+std::max(maxt-(f[i]+d[1][pi]),0ll));
		}
		
	}
	return f[n]<INF;
}

int main()
{
	int n=read(),m=read();
	for(int i=1,u,v; i<=m; ++i) u=read(),v=read(),AE(u,v,read());
	for(int i=1; i<=n; ++i)
	{
		Dijkstra(i);
		for(int j=1; j<=n; ++j) d[i][j]=dis[j];
	}
	for(int i=1; i<=n; ++i) d[0][i]=d[i][0]=0;
	int k=read();
	for(int i=1; i<=k; ++i) s[i]=read(), u[i]=read(), t[i]=read();
	LL l=0,r=INF,mid;
	while(l<r)
	{
		if(Check(mid=l+r>>1,k)) r=mid;
		else l=mid+1; 
	}
	printf("%lld\n",l);

	return 0;
}
