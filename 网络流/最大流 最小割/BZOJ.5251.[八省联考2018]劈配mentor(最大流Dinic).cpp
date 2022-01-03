/*
195228kb	6676ms
对于每个人，每次枚举一个志愿看是否能增广即可。
对于第二问，可以保留第一问中$n$次增广前后的$n$张图，二分，在对应图上看是否能增广即可。
貌似匈牙利的某种写法比网络流优多了...懒得看...
增广失败的话原图流量不会变啊，不用特意删掉新加的边，把表头head改了即可，而且判断是否能增广只需要判断BFS()是否返回1。
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=408,M=(N+40005)*2,INF=0x3f3f3f3f;

int T;
struct Graph
{
	int Enum,H[N],nxt[M],to[M],cap[M],cur[N],lev[N];
	inline void Init(int n)
	{
		Enum=1, memset(H,0,n+1<<2);
	}
	inline void AE(int u,int v,int w)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
	}
	bool BFS()
	{
		static int q[N];
		memset(lev,0,T+1<<2);
		int h=0,t=1; q[0]=0, lev[0]=1;
		while(h<t)
		{
			int x=q[h++];
			for(int i=H[x]; i; i=nxt[i])
				if(!lev[to[i]] && cap[i])
				{
					q[t++]=to[i], lev[to[i]]=lev[x]+1;
					if(to[i]==T) return 1;
				}
		}
		return 0;
	}
	int DFS(int x,int flow)
	{
		if(x==T) return flow;
		int used=0;
		for(int &i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]+1 && cap[i])
			{
				int delta=DFS(to[i],std::min(flow,cap[i]));
				if(delta)
				{
					cap[i]-=delta, cap[i^1]+=delta, used+=delta;
					if(used==flow) return flow;
				}
			}
		return lev[x]=0,used;
	}
	void Dinic()
	{
		while(BFS()) memcpy(cur,H,T+1<<2), DFS(0,INF);
	}
}G[203];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	static int B[203],s[203],Ans1[203],tmpH[N];
	static std::vector<int> v[203][203];

	freopen("mentor.in","r",stdin);
	freopen("mentor.out","w",stdout);

	for(int Tests=read(),C=read(); Tests--; )
	{
		int n=read(),m=read(); T=n+m+1;
		G[0].Init(T);
		for(int i=1; i<=n; ++i) G[0].AE(0,i,1);
		for(int i=1; i<=m; ++i) G[0].AE(i+n,T,B[i]=read());
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j) v[i][j].clear();
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j) v[i][read()].push_back(j+n);
		for(int i=1; i<=n; ++i) s[i]=read();

		for(int i=1; i<=n; ++i)
		{
			G[i]=G[i-1];
			int j;
			for(j=1; j<=m; ++j)
			{
				std::vector<int> &vec=v[i][j];
				for(int k=0,l=vec.size(); k<l; ++k)  G[i].AE(i,vec[k],1);
				if(G[i].BFS()) {G[i].Dinic(); break;}
				if(vec.size()) G[i].Enum=G[i-1].Enum, memcpy(G[i].H,G[i-1].H,T+1<<2);
			}
			printf("%d ",Ans1[i]=j);
		}
		putchar('\n');
	
		for(int i=1; i<=n; ++i)
			if(Ans1[i]<=s[i]) putchar('0'), putchar(' ');
			else
			{
				int l=1,r=i-1,mid,ans=0,dream=s[i];
				while(l<=r)
				{
					mid=l+r>>1;
					int tmpEnum=G[mid-1].Enum;
					memcpy(tmpH,G[mid-1].H,T+1<<2);
					bool ok=0;
					for(int j=1; j<=dream; ++j)
					{
						std::vector<int> &vec=v[i][j];
						for(int k=0,l=vec.size(); k<l; ++k)  G[mid-1].AE(i,vec[k],1);
						if(G[mid-1].BFS()) {ok=1; break;}
					}
					if(ok) ans=mid, l=mid+1;
					else r=mid-1;
					G[mid-1].Enum=tmpEnum, memcpy(G[mid-1].H,tmpH,T+1<<2);
				}
				printf("%d ",i-ans);
			}
		putchar('\n');
	}
	return 0;
}
