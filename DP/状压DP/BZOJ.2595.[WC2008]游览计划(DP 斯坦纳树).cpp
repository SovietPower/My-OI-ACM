/*
2080kb	148ms
$Description$
һ��$n\times m$������������Ȩֵ����ʾѡ�õ�Ļ��ѣ���ʹ����$k$��ȨΪ0�ĵ���ͨ����С���ѡ���ָͨ�������е㶼��ѡ��·��ʹ����ͨ�����������$n,m,K\leq 10$��
$Solution$
f[i][s]��ʾ��iΪ���ڵ㣬��ǰ�ؼ������ͨ״̬Ϊs(ÿ�����Ƿ�����i��ͨ)ʱ�����Ž⡣i��ö�ٵõ��ĸ��ڵ㣬���˸��ڵ������DP�ˡ�
��ôiΪ���ڵ�ʱ����״̬s�ĸ���Ϊ $f[i][s]=min{f[i][s']+f[i][\complement_{s}s']-cost[i]},s'\in s$��ö���Ӽ�s'����Ȼֻ��Ҫs'�Ĳ�������cost[i]����Ϊ����״̬��������cost[i]�����ˣ�
���������ϲ��뵱ǰ��ͨ��һ���µķǹؼ���v����vΪ������ô $f[v][s]=min{f[k][s]+cost[v]},k,v����$
��һ�����¿��԰�˳�򣬵ڶ�������û������˳�򣬵�������̶�״̬s������SPFA��������ת�ơ�
�������������ÿ��ת�Ƽ�¼ת��ǰ�ĵ���״̬s����Ϊ������ת�Ƶ�Ҳ���������Ӽ����¡���������һ���ؼ��㿪ʼDFS���ɡ�
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define En(i,j) (i*m+j)//Encode
#define De(w) mp(w/m,w%m)//Decode
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=102,INF=1e9,to[5]={1,0,-1,0,1};

int n,m,cost[N],f[(1<<10)+1][N];//������˳�� ע��!
pr pre[(1<<10)+1][N];
bool inq[N],vis[N];
std::queue<int> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void SPFA(int *f,pr *pre,int s)
{
	while(!q.empty())
	{
		int now=q.front();
		q.pop(), inq[now]=0;
		for(int x=now/m,y=now%m,xn,yn,nxt,i=0; i<4; ++i)
			if((xn=x+to[i])>=0&&xn<n&&(yn=y+to[i+1])>=0&&yn<m && f[nxt=En(xn,yn)]>f[now]+cost[nxt])
			{
				f[nxt]=f[now]+cost[nxt], pre[nxt]=mp(now,s);
				if(!inq[nxt]) inq[nxt]=1, q.push(nxt);
			}
	}
}
void DFS(int p,int s)
{
	if(!pre[s][p].second) return;//pre.second�� ��ת���� 
	vis[p]=1;
	if(pre[s][p].first==p) DFS(p,s^pre[s][p].second);
	DFS(pre[s][p].first,pre[s][p].second);
}

int main()
{
	n=read(), m=read(); int K=0, rt=0;
	memset(f,0x3f,sizeof f);
	for(int tot=0,i=0; i<n; ++i)
		for(int j=0; j<m; ++j,++tot)
		{
			cost[tot]=read();
			if(!cost[tot]) f[1<<(K++)][tot]=0, rt=tot;
		}
	for(int s=1; s<(1<<K); ++s)
	{
		for(int i=0; i<n*m; ++i)
		{
			for(int sub=(s-1)&s; sub; sub=(sub-1)&s)
				if(f[s][i]>f[sub][i]+f[sub^s][i]-cost[i])
					f[s][i]=f[sub][i]+f[sub^s][i]-cost[i], pre[s][i]=mp(i,sub);
			if(f[s][i]<INF) q.push(i), inq[i]=1;//����㣬inq[]���ǲ���ʡ�� 
		}
		SPFA(f[s],pre[s],s);
	}
	printf("%d\n",f[(1<<K)-1][rt]);
	DFS(rt,(1<<K)-1);
	for(int i=0,tot=0; i<n; ++i,putchar('\n'))
		for(int j=0; j<m; ++j,++tot)
			if(!cost[tot]) putchar('x');
			else putchar(vis[tot]?'o':'_');

	return 0;
}
