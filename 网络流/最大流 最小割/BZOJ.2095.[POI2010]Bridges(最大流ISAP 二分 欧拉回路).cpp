/*
最小化最大的一条边，二分答案。然后就变成了给一张无向图定向使其为欧拉回路 
二分答案后对于一个位置的两条边可能都保留，即双向边，需要给它定向；可能只保留小的一条，即单向边，不需考虑 
如何给它定向呢，或者说怎么形成欧拉回路呢 
形成欧拉回路的充要条件：弱连通图；每个点出度=入度 
记点i的度数 dgr[i]=out[i]-in[i] 
对于一条方向确定的边(u,v)，如果改变它的方向，会使dgr[u]-=2,dgr[v]+=2，也就是说u的2度数分配给了v 
对于in[x]!=out[x]的点都要通过改变某些边方向满足in[x]==out[x] 
最大流，构图就不说了 
刚开始时对一条无向边保留一次它反向的机会，随便定个向，就权值小的吧 

注意度数是每次u,v都改变1的，建边时dgr/2 
如果有某个点出入度之差为奇数，则不可能形成欧拉回路 
ISAP初始度数的最大值要是des+1...
无限TLE(Dinic)原来是M小了...mmp..
无限WA(ISAP)还是找不出原因...
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=1005,M=2005+2*N,INF=1e9;

int n,m,src,des,dgr[N],u[M],v[M],A[M],B[M];
int Enum,cur[N],H[N],nxt[M<<1],fr[M<<1],to[M<<1],cap[M<<1],lev[N],q[N],path[N],num[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}
int Rebuild(int x)
{
	Enum=1, memset(H,0,sizeof H), memset(dgr,0,sizeof dgr);
	for(int i=1;i<=m;++i)
	{
		if(A[i]<=x) ++dgr[u[i]],--dgr[v[i]];//选择作为单向边或是选中这个方向 需改变的度数就是1！
		if(B[i]<=x) AddEdge(u[i],v[i],1);//由u->v可以给出1度数 
	}
	int tot=0;
	for(int i=1;i<=n;++i)
		if(dgr[i]>0) AddEdge(src,i,dgr[i]>>1),tot+=dgr[i]>>1;
		else if(dgr[i]<0) AddEdge(i,des,-dgr[i]>>1);
	return tot;//返回不平衡的度数 
}
bool BFS()
{
	for(int i=src;i<=des;++i) lev[i]=des+1,cur[i]=H[i];
	q[0]=des, lev[des]=0;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(lev[to[i]]==des+1 && cap[i^1])//i^1
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=des;
}
int Augment()
{
	int mn=INF;
	for(int i=des;i!=src;i=fr[path[i]])
		mn=std::min(mn,cap[path[i]]);
	for(int i=des;i!=src;i=fr[path[i]])
		cap[path[i]]-=mn, cap[path[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	if(!BFS()) return -1;
	memset(num,0,sizeof num);//mmp
	for(int i=src;i<=des;++i) ++num[lev[i]];
	int x=src,flow=0;
	while(lev[src]<=des)
	{
		if(x==des) flow+=Augment(),x=src;
		bool can=0;
		for(int i=cur[x];i;i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, path[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x];i;i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=src) x=fr[path[x]];
		}
	}
	return flow;
}
int MF()
{
	for(int i=1;i<=n;++i)
		if(dgr[i]&1) return -1;//如果有度数为1的点，则不可能形成欧拉回路 
	return ISAP();
}

int main()
{
	n=read(),m=read(),src=0,des=n+1;
	int mx=0,mn=INF;
	for(int i=1;i<=m;++i)
	{
		u[i]=read(),v[i]=read(),A[i]=read(),B[i]=read();
		if(A[i]>B[i]) std::swap(A[i],B[i]),std::swap(u[i],v[i]);//用A做较小的边，单向边也肯定是较小的边啊 
		mn=std::min(mn,A[i]), mx=std::max(mx,B[i]);
	}
	int l=mn,r=mx+1,mid;
	while(l<r)
	{
		mid=l+r>>1;
		if(Rebuild(mid)==MF()) r=mid;
		else l=mid+1;
	}
	if(l==mx+1) printf("NIE");
	else printf("%d",l);

    return 0;
}
