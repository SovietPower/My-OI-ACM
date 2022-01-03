/*
插入删除只涉及一个数，故每次可以枚举一遍，而不是重构完后sort 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=6e4+5;
const int MaxSize=200,MaxNum=10000;

int n,tot,limit,belong[N],sz[MaxNum],fa[N],val[N],A[MaxNum][MaxSize];
struct Edge
{
	int Enum,H[N],to[N<<1],nxt[N<<1];
	void AddEdge(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
}a;
struct Edge2
{
	int Enum,H[MaxNum],to[MaxNum],nxt[MaxNum];
	void AddEdge(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
}b;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

void Build(int x)
{
	for(int v,i=a.H[x];i;i=a.nxt[i])
		if((v=a.to[i])!=fa[x])
		{
			fa[v]=x;
			if(sz[belong[x]]<limit) belong[v]=belong[x],A[belong[x]][++sz[belong[x]]]=val[v];
			else belong[v]=++tot,A[tot][sz[tot]=1]=val[v],b.AddEdge(belong[x],tot);
			Build(v);
		}
}
void Modify(int x,int bef,int v)
{
	int p=std::lower_bound(A[x]+1,A[x]+1+sz[x],bef)-A[x];
	while(p<sz[x] && A[x][p+1]<v) A[x][p++]=A[x][p+1];
	while(p>1 && A[x][p-1]>v) A[x][p--]=A[x][p-1];
	A[x][p]=v;
}
void Insert(int x,int v)
{
	int i=++sz[x];
	for(;i>1 && A[x][i-1]>v;--i)
		A[x][i]=A[x][i-1];
	A[x][i]=v;
}
int Search(int pos,int v)
{
	int l=0,r=sz[pos]+1,m;
	while(l<r)
		if(A[pos][(m=l+r>>1)]<=v) l=m+1;
		else r=m;
	return sz[pos]-l+1;
//	return sz[pos]-(int)(std::upper_bound(A[pos]+1,A[pos]+1+sz[pos],v)-A[pos])+1;
}
int Query_B(int x,int va)
{
	int res=Search(x,va);
	for(int i=b.H[x];i;i=b.nxt[i])
		res+=Query_B(b.to[i],va);
	return res;
}
int Query(int x,int va)
{
	int res=val[x]>va?1:0;
//	printf("%d %d\n",x,va);
	for(int v,i=a.H[x];i;i=a.nxt[i])
		if((v=a.to[i])!=fa[x])
		{
			if(belong[x]==belong[v]) res+=Query(v,va);
			else res+=Query_B(belong[v],va);
		}
	return res;
}

int main()
{
//#ifndef ONLINE_JUDGE
//	freopen("2137.in","r",stdin);
//#endif
	freopen("gtygirltree4.in","r",stdin);
	freopen("gtygirltree.out","w",stdout);

	n=read(),limit=(int)sqrt(n);//limit=pow(n,0.6);
	for(int u,v,i=1;i<n;++i) u=read(),v=read(),a.AddEdge(u,v);
	for(int i=1;i<=n;++i) val[i]=read();
	A[belong[1]=tot=1][sz[1]=1]=val[1], Build(1);
	for(int i=1;i<=tot;++i)
		std::sort(A[i]+1,A[i]+sz[i]+1);
	int q=read(),opt,u,x,ans=0;
	while(q--)
	{
		opt=read(),(u=read())^=ans,(x=read())^=ans;
		if(!opt) printf("%d\n",ans=Query(u,x));
		else if(opt==1) Modify(belong[u],val[u],x),val[u]=x;//[]
		else
		{
			val[++n]=x, fa[n]=u, a.AddEdge(u,n);
			if(sz[belong[u]]<limit) belong[n]=belong[u],Insert(belong[u],x);
			else belong[n]=++tot,A[tot][sz[tot]=1]=x,b.AddEdge(belong[u],tot);
		}
	}

	return 0;
}
