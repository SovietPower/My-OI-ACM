/*
259320kb	7584ms
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
	int Enum,H[N],nxt[M],fr[M],to[M],cap[M],pre[N],lev[N];
	inline void Init(int n)
	{
		Enum=1, memset(H,0,n+1<<2);
	}
	inline void AE(int u,int v,int w)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, fr[Enum]=u, cap[Enum]=w;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, fr[Enum]=v, cap[Enum]=0;
	}
	bool BFS()
	{
		static int q[N];
		const int lim=T+1;
		for(int i=0; i<T; ++i) lev[i]=lim;
		int h=0,t=1; q[0]=T, lev[T]=0;
		while(h<t)
		{
			int x=q[h++];
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i^1] && lev[to[i]]==lim) q[t++]=to[i], lev[to[i]]=lev[x]+1;
		}
		return lev[0]<=T;
	}
	inline void Augment()
	{
//		int mn=INF;
//		for(int i=T; i; i=fr[pre[i]])
//			mn=std::min(mn,cap[pre[i]]);
		for(int i=T; i; i=fr[pre[i]])
			--cap[pre[i]], ++cap[pre[i]^1];
	}
	void ISAP()
	{
		static int cur[N],num[N];
		memset(num,0,T+1<<2);
		for(int i=0; i<=T; ++i) cur[i]=H[i], ++num[lev[i]];
		int x=0;
		while(lev[0]<=T)
		{
			if(x==T) x=0, Augment();
			bool can=0;
			for(int i=cur[x]; i; i=nxt[i])
				if(lev[to[i]]==lev[x]-1 && cap[i])
				{
					can=1, cur[x]=i, pre[x=to[i]]=i;
					break;
				}
			if(!can)
			{
				int mn=T;
				for(int i=H[x]; i; i=nxt[i])
					if(cap[i]) mn=std::min(mn,lev[to[i]]);
				if(!--num[lev[x]]) break;
				++num[lev[x]=mn+1], cur[x]=H[x];
				if(x) x=fr[pre[x]];
			}
		}
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
				if(G[i].BFS()) {G[i].ISAP(); break;}
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
