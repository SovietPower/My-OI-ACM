//注意树剖一条链上或一棵子树内的编号是连续的 
//建树时用的是第二次dfs得到的序列 
//不要频繁转longlong 
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,MAXIN=1e6;

int n,m,root,mod,A[N],Enum,H[N],to[N<<1],nxt[N<<1];
int val[N],fa[N],son[N],sz[N],dep[N],top[N],cnt,id[N],sum[N<<2],tag[N<<2];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}

void DFS1(int x)
{
	int mx=-1;sz[x]=1;
	for(int i=H[x];i;i=nxt[i])
		if(to[i]!=fa[x])
		{
			fa[to[i]]=x, dep[to[i]]=dep[x]+1,
			DFS1(to[i]), sz[x]+=sz[to[i]];
			if(mx<sz[to[i]]) son[x]=to[i],mx=sz[to[i]];
		}
}
void DFS2(int x,int tp)
{
	id[x]=++cnt, val[cnt]=A[x], top[x]=tp;
	if(!son[x]) return;
	DFS2(son[x],tp);
	for(int i=H[x];i;i=nxt[i])
		if(to[i]!=fa[x]&&to[i]!=son[x])//if(!id[to[i]])
			DFS2(to[i],to[i]);
}
inline void PushUp(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1], sum[rt]>=mod?sum[rt]-=mod:0;
}
void PushDown(int rt,int m)
{
	tag[rt<<1]+=tag[rt], tag[rt<<1]>=mod?tag[rt<<1]-=mod:0;
	tag[rt<<1|1]+=tag[rt], tag[rt<<1|1]>=mod?tag[rt<<1|1]-=mod:0;
	sum[rt<<1]=(sum[rt<<1]+tag[rt]*(m-(m>>1)))%mod;
	sum[rt<<1|1]=(sum[rt<<1|1]+tag[rt]*(m>>1))%mod;
	tag[rt]=0;
}
void Build(int l,int r,int rt)
{
	if(l==r) {sum[rt]=val[l]; return;}
	int m=l+r>>1;
	Build(l,m,rt<<1),Build(m+1,r,rt<<1|1);
	PushUp(rt);
}
void Tree_Add(int l,int r,int rt,int L,int R,int v)
{
	if(L<=l && r<=R)
	{
		sum[rt]=(sum[rt]+(r-l+1)*v)%mod,
		tag[rt]+=v, tag[rt]>=mod?tag[rt]-=mod:0;
		return;
	}
	if(tag[rt]) PushDown(rt,r-l+1);
	int m=l+r>>1;
	if(L<=m) Tree_Add(l,m,rt<<1,L,R,v);
	if(m<R) Tree_Add(m+1,r,rt<<1|1,L,R,v);
	PushUp(rt);
}
int Tree_Query(int l,int r,int rt,int L,int R)
{
	if(L<=l && r<=R) return sum[rt];
	if(tag[rt]) PushDown(rt,r-l+1);
	int m=l+r>>1;
	if(L<=m)
		if(m<R) return (Tree_Query(l,m,rt<<1,L,R)+Tree_Query(m+1,r,rt<<1|1,L,R))%mod;
		else return Tree_Query(l,m,rt<<1,L,R);
	else return Tree_Query(m+1,r,rt<<1|1,L,R);
}
void Chain_Add(int x,int y,int v)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		Tree_Add(1,n,1,id[top[x]],id[x],v);
		x=fa[top[x]];
	}
	if(id[x]>id[y]) std::swap(x,y);
	Tree_Add(1,n,1,id[x],id[y],v);
}
int Chain_Query(int x,int y)
{
	int res=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		res+=Tree_Query(1,n,1,id[top[x]],id[x]), res>=mod?res-=mod:0;
		x=fa[top[x]];
	}
	if(id[x]>id[y]) std::swap(x,y);
	res+=Tree_Query(1,n,1,id[x],id[y]), res>=mod?res-=mod:0;
	return res;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3384.in","r",stdin);
#endif

	n=read(),m=read(),root=read(),mod=read();
	for(int i=1;i<=n;++i) A[i]=read(),A[i]>=mod?A[i]%=mod:0;
	for(int u,v,i=1;i<n;++i) u=read(),v=read(),AddEdge(u,v);
	DFS1(root),DFS2(root,root);
	Build(1,n,1);
	int opt,x,y,z;
	while(m--)
	{
		opt=read(),x=read();
		if(opt==1) y=read(),z=read(),Chain_Add(x,y,z%mod);
		else if(opt==2) y=read(),printf("%d\n",Chain_Query(x,y));
		else if(opt==3) y=read(),Tree_Add(1,n,1,id[x],id[x]+sz[x]-1,y%mod);
		else printf("%d\n",Tree_Query(1,n,1,id[x],id[x]+sz[x]-1));
	}

	return 0;
}
