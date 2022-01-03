/*
126688kb	9332ms
$Description$
��һ��$n*n$�����������������������ϰ��㡣$q$��ѯ�ʣ�ÿ��ѯ�ʰ�һ�����������Ӵ�$(x1,y1)$�Ƶ�$(x2,y2)$ �����ܽӴ��ϰ����Ҳ������߽磬���ӵı߳�������Ƕ��١�
$n\leq1000,q\leq3*10^5$��
$Solution$
���ǿ���ֱ�ӽ����ϰ��㿴�����㣬����Χ�ĸ����ϰ������ߡ�������Ҫ��һ�������������
��ÿ���ϰ���������ͨBFS�����Եõ�ͨ��ÿ�����ϰ���λ�õ����ֱ����
Ȼ�����ֱ���Ӵ�С���μ���㲢��Ϊ���ʹ���ÿ������Χ֮ǰ�����ʹ��ĵ����ߣ�Ҳ����ö��ȨֵС���������ߣ����������ߣ���Kruskalһ������
��ʵ����Kruskal�ع���������ʱ��ΪȨֵ�ڵ��ϣ����Բ���Ҫ�½�������ʾ���ˣ�ֱ�ӽ�Ȩֵ��ĵ�����ȨֵС�ĵ���Ϊ���ӽڵ㼴�ɡ�
�����·��ѯ�ʾ���ֱ����LCA��Ȩֵ�ˡ�
���Ӷ�$O(n^2+q\log n^2)$��
ע���ʼ��disΪINF���������ϰ���ʱ����dis��Ϊ0����
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1003,M=1e6+5;
const int dd[]={1,0,-1,0,1};
const int dx[]={0,0,-1,-1,-1,1,1,1};
const int dy[]={-1,1,-1,0,1,-1,0,1};

int n,id[N][N],A[M],fa[M];
std::vector<int> v[N];
char IN[MAXIN],*SS=IN,*TT=IN;

namespace HLD
{
	int Enum,H[M],nxt[M],to[M],fa[M],sz[M],son[M],dep[M],top[M];

	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
	inline int LCA(int u,int v)
	{
		while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
		return dep[u]<dep[v]?u:v;
	}
	void DFS1(int x)
	{
		int mx=0; sz[x]=1;
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x])
			{
				fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
				if(sz[v]>mx) mx=sz[v], son[x]=v;
			}
	}
	void DFS2(int x,int tp)
	{
		top[x]=tp;
		if(son[x])
		{
			DFS2(son[x],tp);
			for(int i=H[x]; i; i=nxt[i])
				if(to[i]!=fa[x]&&to[i]!=son[x]) DFS2(to[i],to[i]);
		}
	}
}

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Merge(int x,int y)//x<-y
{
	y=Find(y);
	if(x!=y) fa[y]=x, HLD::AE(x,y);
}
void BFS()
{
	static int dis[N][N];
	static bool vis[N][N];
	static std::queue<pr> q;

	memset(dis,0x3f,sizeof dis);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(!id[i][j]) q.push(mp(i,j)),vis[i][j]=1,dis[i][j]=0;
	while(!q.empty())
	{
		int x=q.front().first,y=q.front().second;
		q.pop();
		for(int i=0,xn,yn,d=dis[x][y]; i<8; ++i)
			if((xn=x+dx[i])>0&&xn<=n&&(yn=y+dy[i])>0&&yn<=n&&!vis[xn][yn])
				vis[xn][yn]=1, dis[xn][yn]=d+1, q.push(mp(xn,yn));
	}
	for(int i=1; i<=n; ++i)
		for(int j=1,ds,t; j<=n; ++j)
			if(t=id[i][j])
			{
				ds=std::min(dis[i][j],std::min(std::min(i,n-i+1),std::min(j,n-j+1)));
				ds=(ds<<1)-1;//maxd = 2r-1
				A[t]=ds, v[ds].push_back(t);
			}
}

int main()
{
	static pr ref[M];
	static bool vis[N][N];

	n=read(); int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		register char c=gc(); while(c!='.'&&c!='#') c=gc();
		if(c=='.') id[i][1]=++cnt, ref[cnt]=mp(i,1);
		for(int j=2; j<=n; ++j) if(gc()=='.') id[i][j]=++cnt, ref[cnt]=mp(i,j);
	}

	BFS();
	for(int i=1; i<=cnt; ++i) fa[i]=i;
	for(int i=n; i; --i)
	{
		const std::vector<int> &vec=v[i];
		for(int j=0,l=vec.size(); j<l; ++j)
		{
			int t=vec[j],x=ref[t].first,y=ref[t].second;
			vis[x][y]=1;
			for(int i=0,xn,yn; i<4; ++i)
				if((xn=x+dd[i])>0&&xn<=n&&(yn=y+dd[i+1])>0&&yn<=n&&vis[xn][yn])
					Merge(t,id[xn][yn]);
		}
	}
	for(int i=1; i<=cnt; ++i) if(fa[i]==i) Merge(0,i);
	HLD::DFS1(0), HLD::DFS2(0,0);

	for(int q=read(),p1,p2,x1,y1,x2,y2; q--; )
	{
		p1=id[read()][read()], p2=id[read()][read()];
		if(!p1||!p2) puts("0");
		else printf("%d\n",A[HLD::LCA(p1,p2)]);
	}
	return 0;
}
