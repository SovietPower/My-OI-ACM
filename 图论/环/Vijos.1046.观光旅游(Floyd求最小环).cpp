/*
��С����
�����㷨����e(u,v)��ʾu->v�����ߣ�min(u,v)��ʾɾ��e(u,v)��u->v�����· 
		����С��Ϊ min(u,v) + e(u,v)
		O(EV^2) 
�Ż��������ֳ����Σ��ϵ�Ϊi��j��k��������Ϊ�������룬��·�����н��� 
	 �����뵽 Map[i][k] + Map[k][j] + Min[i][j]��Map������ֱ�������ıߣ�Min�����· 
	 ֻҪi��j�����·Min[i][j]������k���������һ���� 
	 Folyd�У������ѭ������k-1�κ�dis[i][j]��ʾi��j��·���У����е�ı�Ŷ�<k�����·�� 
	 ���ϣ�Floydһ�����ҵ���С�� 
(Floydԭ��http://blog.csdn.net/zhongkeli/article/details/8832946)

ע���ر� ע��3*INF��Ҫ��� 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=103,INF=1e8;

int n,m,dis[N][N],Map[N][N],Ans;

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Floyd()
{
	Ans=INF;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dis[i][j]=Map[i][j];
	for(int k=1;k<=n;++k)
	{
		for(int i=1;i<k;++i)
			for(int j=i+1;j<k;++j)
				Ans=min(Ans,dis[i][j]+Map[i][k]+Map[k][j]);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
	}
}

int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
//				if(i==j)
//					Map[i][j]=0;
//				else
					Map[i][j]=INF;
		for(int u,v,w,i=1;i<=m;++i)
			u=read(),v=read(),w=read(),
			Map[u][v]=Map[v][u]=min(Map[v][u],w);
		Floyd();
		if(Ans==INF)
			puts("No solution.");
		else
			printf("%d\n",Ans);
	}
	
	return 0;
}
