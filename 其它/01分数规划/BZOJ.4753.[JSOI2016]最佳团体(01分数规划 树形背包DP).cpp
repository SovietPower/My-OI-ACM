/*
$Description$
ÿ�����з���si���ֵpi��Ҫ��ѡһЩ��������ͨ�飬�ܴ�СΪk��ʹ��(��pi)/(��si)���	 
$Solution$
01�����滮��Ȼ��dp����f[i][j]��ʾi����ѡj�������Ȩֵ�ͣ�ֱ�ӱ�������ת�Ƽ��� 
��ö���ӽڵ�ѡ������ʱ������x��1.2.3.4�ĸ��ӽڵ㣬���Ӷ�Ϊ1*sz[1]+sz[1]*sz[2]+(sz[1]+sz[2])*sz[3]+(sz[1]+sz[2]+sz[3])*sz[4] 
�൱��ÿ�Ե���LCA���й��ף�������n^2��LCA�������ⲿ�ָ��Ӷ�ΪO(n^2)
��O(n^2*log ans)
ע: �ܶ��ʼֵ��Ҫ��0����Ϊ���нϴ���������˵ ����涨f[0][1]Ϊ-INF 
epsΪʲô��Ҫ1e-5����<1e-4����������(Ҳ�����Ⲣ���Ǿ�ȷ�𰸣�~~��ʱ�󷨺�~~) 
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=2505;
const double eps=1e-5,INF=1e10;

int n,m,Enum,H[N],nxt[N],to[N],sz[N];
double cost[N],p[N],val[N],f[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS(int x)
{
	int mn=(x>0); sz[x]=mn;
	for(int i=2; i<=m; ++i) f[x][i]=-INF;
	f[x][1]=val[x];
	for(int v,i=H[x]; i; i=nxt[i])
	{
		DFS(v=to[i]);
		for(int j=sz[x]; j>=mn; --j)//���� //�������޾��ǵ�ǰ����sz���ӽڵ�sz֮�� 
			for(int k=1; k<=sz[v]; ++k)
				f[x][j+k]=std::max(f[x][j+k],f[x][j]+f[v][k]);
		sz[x]+=sz[v];
	}
}
double Solve(double x)
{
	for(int i=1; i<=n; ++i) val[i]=p[i]-x*cost[i];
//	memset(f,0xc2,sizeof f), f[0][0]=0;//too slow
	DFS(0);
	return f[0][m]>=0;
}

int main()
{
	m=read(), n=read();
	for(int i=1; i<=n; ++i)
		cost[i]=read(),p[i]=read(),AddEdge(read(),i);
	double l=0.0,r=1e4,mid; val[0]=-INF;//f[0][1]
	while(r-l>eps)
	{
		if(Solve(mid=(l+r)/2.0)) l=mid;
		else r=mid;
	}
	printf("%.3lf",mid);

	return 0;
}
