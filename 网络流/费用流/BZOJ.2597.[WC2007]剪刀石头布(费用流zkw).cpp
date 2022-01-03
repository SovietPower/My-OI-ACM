/*
2292kb	416ms
$Description$
����һ�Ų��ֱ߷�����ȷ���ľ���ͼ������Ҫ��ʣ�µı�ȷ������ʹ��ͼ�е���Ԫ��������ࡣ
$n\leq100$��
$Solution$
����ѡ��֮����Ӱ�죬����$n$��С���⿼������������

�����������ܵõ�����Ԫ��������$C_n^3$�������ǿ���������ʹ��Ԫ���������١�
���������֮�䲻����Ԫ������ôһ����ĳ�������Ϊ$2$��ĳ�������Ϊ$2$����һ������ȳ��ȶ�Ϊ$1$��
����ֻ������ȡ����һ�������Ϊ$2$����ô�����$1$����Ԫ����������Ϊ$3$����ô�����$C_3^2=3$����Ԫ����������õ�$A$��������Ϊ$B,C,D$��$A,B,C$��$A,B,D$��$A,C,D$֮�䶼�β�����Ԫ����...
Ҳ������һ��������Ϊ$dgr$�������$C_{dgr}^2$����Ԫ������ô�𰸾���$C_n^3-\sum_{i=1}^nC_{dgr_i}^2$��
������ÿ�θı�$1$�����ٵ���Ԫ��������$C_{dgr}^2-C_{dgr-1}^2=dgr-1$��

Ȼ��Ϳ��Կ��Ǹ�ÿ�����������ˡ���ÿ�����½�һ����$x$����Դ����$x$������$1$������$0$�ıߣ�$x$��ߵ����˵�ֱ�������Ϊ$1$������Ϊ$0$�ıߡ�
����ԭͼ��$n$���㣬ÿ��������ֱ�������Ϊ$1$������Ϊ$0,1,2,3...$�ıߡ�
�ܷ�������$C_n^3-cost$���Ǵ��ˡ�

ʵ���ϣ�����ȷ���ı߲�����Ҫ���������Ѵ��ȼ���$\frac{dgr_i(dgr_i-1)}{2}$��Ȼ��ö��$i$������ı�ʱ�����ô�$dgr_i$��ʼö�پͿ����ˡ����Ż������ԣ�
����`memset(A,...,ĳ��ȷ����С)`��ע��`A[]`��`int`����`bool`��`bool`��һ�ֽڣ�

��������[�����+����]���������ܵúܿ졣
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=105+105*52,M=4*105*105*2;

int src,des,Cost,Enum,cur[N],H[N],nxt[M],fr[M],to[M],cap[M],cost[M],dis[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w,int c)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	static bool inq[N];
	static std::queue<int> q;
	memset(dis,0x3f,des+1<<2);
	dis[0]=0, q.push(0);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int i=H[x],v; i; i=nxt[i])
			if(cap[i] && dis[v=to[i]]>dis[x]+cost[i])
				dis[v]=dis[x]+cost[i], !inq[v]&&(q.push(v),inq[v]=1);
	}
	return dis[des]<0x3f3f3f3f;
}
int DFS(int x)
{
	if(x==des) return 1;
	vis[x]=1;
	for(int &i=cur[x]; i; i=nxt[i])
		if(!vis[to[i]] && cap[i] && dis[to[i]]==dis[x]+cost[i] && DFS(to[i]))
			return --cap[i],++cap[i^1],Cost+=cost[i],1;
	return 0;
}
int MCMF()
{
	while(SPFA())
	{
		memcpy(cur,H,des+1<<2), memset(vis,0,des+1);//bool��1�ֽڣ�����
		while(DFS(0));
	}
	return Cost;
}

int main()
{
	static int dgr[105],id[N],tag[N],Ans[105][105];
	const int n=read(); Enum=1, src=0, des=(n*n+n)/2+1;
	if(n<3) return putchar('0'),0;
	for(int i=1,tot=n; i<=n; ++i)
	{
		for(int j=1; j<=i; ++j) read();
		for(int j=i+1; j<=n; ++j)
			switch(AE(0,++tot,1,0),read())
			{
				case 0: tag[tot]=1, ++dgr[j]; break;
				case 1: tag[tot]=2, ++dgr[i]; break;
				case 2: AE(tot,i,1,0), id[tot]=Enum, AE(tot,j,1,0); break;//->i: i wins
			}
	}
	int ans=n*(n-1)*(n-2)/6;
	for(int i=1; i<=n; ++i)
	{
		ans-=dgr[i]*(dgr[i]-1)/2;
		for(int j=dgr[i]; j<n-1; ++j) AE(i,des,1,j);
	}
	printf("%d\n",ans-MCMF());
	for(int i=1,tot=n; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			if(tag[++tot]) Ans[i][j]=tag[tot]-1;
			else Ans[i][j]=cap[id[tot]]?1:0;
	for(int i=1; i<=n; ++i,putchar('\n'))
	{
		for(int j=1; j<i; ++j) printf("%d ",Ans[j][i]^1);
		for(int j=i; j<=n; ++j) printf("%d ",Ans[i][j]);
	}

	return 0;
}
