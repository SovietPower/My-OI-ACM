/*
想一下能猜出，最优解中海拔只有0和1，且海拔相同的点都在且只在1个连通块中。
这就是个平面图最小割。~~也可以转~~必须转对偶图最短路，不然只能T到90分了。。
不能忽略回去的边，因为最小割的形状可能很奇怪。
还是建反向边吧，虽然会有一条反向边，但是很难对应上去。。
注意n要加1，即点数是501*501=251001而不是250000。。够坑(也就坑我这种卡的了)。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define ID(x,y) ((x-1)*n+y)
const int N=501*501+5/*>250005!*/,M=N<<3,INF=0x3f3f3f3f;

int n,src,des,Enum,H[N],cur[N],nxt[M],fr[M],to[M],cap[M],lev[N],pre[N],num[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int w,int u,int v)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	static int q[N];
	for(int i=src; i<des; ++i) lev[i]=des+1;
	int h=0,t=1; q[0]=des, lev[des]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==des+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=des;
}
int Augment()
{
	int mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
long long ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src; long long res=0;
	while(lev[src]<=des)
	{
		if(x==des) x=src,res+=Augment();
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}

int main()
{
	n=read()+1, Enum=1, src=1, des=n*n;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<n; ++j) AddEdge(read(),ID(i,j),ID(i,j+1));
	for(int i=1; i<n; ++i)
		for(int j=1; j<=n; ++j) AddEdge(read(),ID(i,j),ID(i+1,j));
	for(int i=1; i<=n; ++i)
		for(int j=1; j<n; ++j) AddEdge(read(),ID(i,j+1),ID(i,j));
	for(int i=1; i<n; ++i)
		for(int j=1; j<=n; ++j) AddEdge(read(),ID(i+1,j),ID(i,j));
	printf("%lld\n",ISAP());

	return 0;
}
