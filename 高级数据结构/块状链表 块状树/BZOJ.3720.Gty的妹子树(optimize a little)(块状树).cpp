/*
插入删除只涉及一个数，故每次可以枚举一遍，而不是重构完后sort 
由于有二分操作，所以大小定为2.0*sqrt(n)*log2(n)比较好，而不是sqrt(n) 懒得证了...
大小太麻烦了。。该用vector 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=6e4+5;
const int MaxSize=200,MaxNum=8000,MAXIN=7e6;

int n,tot,limit,belong[N],fa[N],val[N],ans;
char IN[MAXIN],*SS=IN,*TT=IN;
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
struct Block
{
	int sz,A[MaxSize];
	void Modify(int bef,int v)
	{
		int p=std::lower_bound(A+1,A+1+sz,bef)-A;
		while(p<sz && A[p+1]<v) A[p++]=A[p+1];
		while(p>1 && A[p-1]>v) A[p--]=A[p-1];
		A[p]=v;
	}
	void Insert(int v)
	{
		int i=++sz;
		while(i>1 && A[i-1]>v) A[i--]=A[i-1];
		A[i]=v;
	}
	int Query(int v)
	{
		int l=0,r=sz+1,m;
		while(l<r)
			if(A[(m=l+r>>1)]<=v) l=m+1;
			else r=m;
		return sz-l+1;
//		return sz-(int)(std::upper_bound(A+1,A+1+sz,v)-A)+1;
	}
}blo[MaxNum];
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

void Build(int x)
{
	if(blo[belong[fa[x]]].sz==limit) blo[belong[x]=++tot].Insert(val[x]),b.AddEdge(belong[fa[x]],tot);
	else blo[belong[x]=belong[fa[x]]].Insert(val[x]);
	for(int v,i=a.H[x];i;i=a.nxt[i])
		if((v=a.to[i])!=fa[x]) fa[v]=x, Build(v);
}
void Query_B(int x,int va)
{
	ans+=blo[x].Query(va);
	for(int i=b.H[x];i;i=b.nxt[i])
		Query_B(b.to[i],va);
}
void Query(int x,int va)
{
	if(val[x]>va) ++ans;
	for(int v,i=a.H[x];i;i=a.nxt[i])
		if((v=a.to[i])!=fa[x])
		{
			if(belong[x]==belong[v]) Query(v,va);
			else Query_B(belong[v],va);
		}
}

int main()
{
//#ifndef ONLINE_JUDGE
//	freopen("2137.in","r",stdin);
//#endif
//	freopen("gtygirltree.in","r",stdin);
//	freopen("gtygirltree.out","w",stdout);

	n=read(),limit=(int)sqrt(n);//limit=(int)ceil(2.0*sqrt(n)*log2(n));
	for(int u,v,i=1;i<n;++i) u=read(),v=read(),a.AddEdge(u,v);
	for(int i=1;i<=n;++i) val[i]=read();
	Build(1);
	int q=read(),opt,u,x;
	while(q--)
	{
		opt=read(),(u=read())^=ans,(x=read())^=ans;
		if(!opt) ans=0,Query(u,x),printf("%d\n",ans);
		else if(opt==1) blo[belong[u]].Modify(val[u],x),val[u]=x;
		else
		{
			val[++n]=x, fa[n]=u, a.AddEdge(u,n);
			if(blo[belong[u]].sz<limit) belong[n]=belong[u],blo[belong[u]].Insert(x);
			else blo[belong[n]=++tot].Insert(x),b.AddEdge(belong[u],tot);
		}
	}

	return 0;
}
