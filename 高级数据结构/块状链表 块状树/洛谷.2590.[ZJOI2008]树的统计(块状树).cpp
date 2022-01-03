/*
对树上节点进行分块，每个点记录dep,fa,val,Max,Sum，Max,Sum表示当前点在该块内的子树中权值最大值与和 
节点i各值表示从root[i]到i一段路径的的对应值。因为求值时应是向上找到LCA，所以记录一个从根到叶的信息 
修改一个点i时影响的只是该块内从fa[i]以下的点，暴力向下更新 
查询路径时不断向上找LCA。注意每次都是让深度大的跳，以避免分类讨论 
当两个点在一个块内时暴力一步步向上 直到LCA 
存两组边，一是原图中的边，二是每个块内的关系边 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=3e4+5,INF=0x3f3f3f3f;

int n,limit,val[N],rt[N],dep[N],fa[N],Max[N],Sum[N],Enum,H[N],nxt[N<<1],to[N<<1];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}

void Build(int x,int &res)
{
	if(res) rt[x]=rt[fa[x]],--res;
	else rt[x]=x,res=limit;
	for(int i=H[x];i;i=nxt[i])
		if(to[i]!=fa[x])
			dep[to[i]]=dep[x]+1,fa[to[i]]=x,Build(to[i],res);
}
void Update(int x,int Mx,int Sm)
{
	Sm+=val[x], Sum[x]=Sm;
	Mx=std::max(Mx,val[x]), Max[x]=Mx;
	for(int i=H[x];i;i=nxt[i])
		if(rt[x]==rt[to[i]] && to[i]!=fa[x])
			Update(to[i],Mx,Sm);
}
int Query(int x,int y,bool f)
{
	int sm=0,mx=-INF;
	while(rt[x]!=rt[y])//不在同一块时直接用整块的信息 
	{
		if(dep[x]<dep[y]) std::swap(x,y);
		if(dep[rt[x]]<dep[rt[y]]) std::swap(x,y);
		mx=std::max(mx,Max[x]), sm+=Sum[x];
		x=fa[rt[x]];
	}
	while(x!=y)//在同一个块内，不能直接用整块的信息，一步步跳 
	{
		if(dep[x]<dep[y]) std::swap(x,y);
		mx=std::max(mx,val[x]), sm+=val[x];
		x=fa[x];
	}
//	while(x!=y)
//	{
//		if(dep[x]<dep[y]) std::swap(x,y);
//		if(rt[x]==rt[y])//在同一个块内，不能直接用整块的信息，一步步跳 
//		{
//			mx=std::max(mx,val[x]), sm+=val[x];
//			x=fa[x];
//		}
//		else
//		{
//			if(dep[rt[x]]<dep[rt[y]]) std::swap(x,y);
//			mx=std::max(mx,Max[x]), sm+=Sum[x];
//			x=fa[rt[x]];
//		}
//	}
	mx=std::max(mx,val[x]), sm+=val[x];//Don't forget!!
	return f?mx:sm;
}

int main()
{
	n=read(),limit=pow(n,0.45);
//	limit=sqrt(n);
	for(int u,v,i=1;i<n;++i) u=read(),v=read(),AddEdge(u,v);
	for(int i=1;i<=n;++i) Max[i]=val[i]=read();
	int res=0;
	Build(1,res);
	for(int i=1;i<=n;++i)
		if(rt[i]==i) Update(i,val[i],0);
	int q=read(),u,v;char s[7];
	while(q--)
	{
		scanf("%s",s),u=read(),v=read();
		if(s[0]=='C')
		{
			val[u]=v;
			if(u==rt[u]) Update(u,val[u],0);//显然不能从上一块更新 
			else Update(u,Max[fa[u]],Sum[fa[u]]);//是从当前节点更新,not fa[u]!fa[u]的Sum这样就多了 
		}
		else if(s[1]=='M') printf("%d\n",Query(u,v,1));
		else printf("%d\n",Query(u,v,0));
	}

	return 0;
}
