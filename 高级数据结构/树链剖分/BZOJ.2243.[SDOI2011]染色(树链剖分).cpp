//17440kb	3760ms
//维护区间颜色数、最左、最右颜色即可。
//-(L[]==R[])要加括号！woc才发现。
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,S=N<<2,MAXIN=5e5;

int n,A[N],cnt,fa[N],dep[N],sz[N],son[N],top[N],pos[N],H[N],Enum,to[N<<1],nxt[N<<1];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Seg_tree
{
	#define ls l,m,rt<<1
	#define rs m+1,r,rt<<1|1
	#define lson rt<<1
	#define rson rt<<1|1

	int B[N],Lc[S],Rc[S],sum[S],tag[S];
	inline void Update(int rt){
//		cov[rt]=cov[lson]==cov[rson]?cov[lson]:0;//不需要维护区间是否被同种颜色覆盖了吧 复杂度也不高 
		Lc[rt]=Lc[lson], Rc[rt]=Rc[rson];
		sum[rt]=sum[lson]+sum[rson]-(Lc[rson]==Rc[lson]);
	}
	inline void Cover(int rt,int v){
		tag[rt]=Lc[rt]=Rc[rt]=v, sum[rt]=1;
	}
	inline void PushDown(int rt){
		if(tag[rt]) Cover(lson,tag[rt]),Cover(rson,tag[rt]),tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) Cover(rt,B[l]);
		else{
			int m=l+r>>1;
			Build(ls), Build(rs), Update(rt);
		}
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) Cover(rt,v);
		else{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			if(L<=m) Modify(ls,L,R,v);
			if(m<R) Modify(rs,L,R,v);
			Update(rt);
		}
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return sum[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(ls,L,R)+Query(rs,L,R)-(Rc[lson]==Lc[rson]);
			else return Query(ls,L,R);
		return Query(rs,L,R);
	}
	int Query_pos(int l,int r,int rt,int p)
	{
		if(l==r) return Lc[rt];//直接单点查吧 也不用Lc[],Rc[]了 
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(p<=m) return Query_pos(ls,p);
		return Query_pos(rs,p);
	}
}t;
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void pre_DFS(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			dep[v]=dep[x]+1, fa[v]=x, pre_DFS(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
void DFS(int x,int tp)
{
	t.B[pos[x]=++cnt]=A[x], top[x]=tp;
	if(son[x]){
		DFS(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x]&&to[i]!=son[x]) DFS(to[i],to[i]);
	}
}
void Modify(int x,int y,int v)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		t.Modify(1,cnt,1,pos[top[x]],pos[x],v);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) std::swap(x,y);
	t.Modify(1,cnt,1,pos[x],pos[y],v);
}
//#define D printf("Delete!%d col:%d\n",pos[x],pre1)
int Query(int x,int y)
{
	int res=0,pre1=0,pre2=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y),std::swap(pre1,pre2);
		if(t.Query_pos(1,cnt,1,pos[x])==pre1) --res;
		res+=t.Query(1,cnt,1,pos[top[x]],pos[x]);
		pre1=t.Query_pos(1,cnt,1,pos[top[x]]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) std::swap(x,y),std::swap(pre1,pre2);
//	if(x==y && (t.Query_pos(1,cnt,1,pos[x])==pre1||t.Query_pos(1,cnt,1,pos[y])==pre2)) --res; else ...;
	if(t.Query_pos(1,cnt,1,pos[x])==pre1) --res;//这里不该判x与y相等 然后少减 
	if(t.Query_pos(1,cnt,1,pos[y])==pre2) --res;
	return res+t.Query(1,cnt,1,pos[x],pos[y]);
}
inline char Get(){
	char c=gc(); while(c!='C'&&c!='Q') c=gc(); return c;
}

int main()
{
	n=read();int m=read();
	for(int i=1; i<=n; ++i) A[i]=read()+1;
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	pre_DFS(1), DFS(1,1), t.Build(1,cnt,1);
	int x,y,v;
	while(m--)
		if(Get()=='C') x=read(),y=read(),v=read()+1,Modify(x,y,v);
		else x=read(),y=read(),printf("%d\n",Query(x,y));
	return 0;
}
