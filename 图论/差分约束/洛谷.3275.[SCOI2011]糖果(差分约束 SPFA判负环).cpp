/*
差分约束：对于 n[a] - n[b] <= w 的不等式，可以转化成 n[a] <= n[b] + w
换个形式 dis[a] <= dis[b] + w(a,b)
用SPFA做，dis[a]>dis[b]+w(a,b) 时会进行松弛 
求最小值用最长路，求最大值用最短路 
1.>= 求最小值。为什么是最长路？如果是最短路，很多条件可能不被满足， 
(SPFA松弛时是将 dis[a]>dis[b]+w(a,b) -> dis[a]=dis[b]+w(a,b))
2.<= 求最大值。为什么是最短路？因为要满足所有小于等于的条件，只有最短的路才能满足图中所有约束条件；如果比最短路长，可能有些条件不被满足 
3.如果出现没有等号的项，用整数的连续性 

源点从后往前加边，可以过链 
注意此题每个小朋友都要分到糖果，有源点向每个点建边时，边权为1而不是0 
*/
#include<cstdio>
#include<cctype>
using namespace std;
const int N=1e5+5;

int n,k,Enum,H[N],nxt[N*3],to[N*3],val[N*3],dis[N];
bool Flag,vis[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum] = v;
	nxt[Enum] = H[u];
	val[Enum] = w;
	H[u] = Enum;
}

void SPFA(int x)
{
	if(Flag) return;
	vis[x]=1;
	for(int i=H[x];i;i=nxt[i])
	{
		if(Flag) return;
		if(dis[to[i]]<dis[x]+val[i])
		{
			if(vis[to[i]])
			{
				Flag=1;
				return;
			}
			dis[to[i]]=dis[x]+val[i],
			SPFA(to[i]);
		}
	}
	vis[x]=0;
}

int main()
{
	n=read(),k=read();
	for(int opt,a,b,i=1;i<=k;++i)
	{
		opt=read(),a=read(),b=read();
		switch(opt)
		{
			case 1:
				AddEdge(a,b,0),AddEdge(b,a,0);
				break;
			case 2:
				if(a==b)
				{
					printf("-1");
					return 0;
				}
				AddEdge(a,b,1);
				break;
			case 3:
				AddEdge(b,a,0);
				break;
			case 4:
				if(a==b)
				{
					printf("-1");
					return 0;
				}
				AddEdge(b,a,1);
				break;
			case 5:
				AddEdge(a,b,0);
				break;
		}
	}
	for(int i=n;i;--i)
		AddEdge(0,i,1);
	SPFA(0);
	long long res=0;//long long
	for(int i=1;i<=n;++i)
		res+=dis[i];
	printf("%lld",Flag?-1:res);

	return 0;
}
