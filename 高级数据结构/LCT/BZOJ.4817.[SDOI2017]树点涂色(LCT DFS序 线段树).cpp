/*
29372kb	5412ms
1.2�����ʣ�����3.ÿ����Ĵ�val�ܲ���ά������
������ǰ�ͬ����ɫ�ĵ㻮�ֵ�ͬһ��ͨ���У���ô���Ⱦɫ�Ĺ��̾���Access()!
������е�䶼����ߣ���ͬ��ɫ����ʵ��������һ������ʵ�߱�Ϊ���ʱ����ȴ�ĵ������������е�val+1(Access()��ԭ��x���Ҷ��Ӵ�+1����Ϊx��ɫ����)��
����߱�Ϊʵ��ʱ����ȴ�ĵ������������е�val-1(fa[x]��ɫ��x��ͬ����fa[x]�Ĺ���û��).(��ʵ����Ϊ ʵ������(����)�͵����������+1������ν��)
����2.����val[x]+val[y]-2*val[LCA]+1��3.���������в�ѯ���ֵ�����߶���+DFS��ά����
��Щ����...�����������ά��ÿ���㵽���ӽڵ�ıߣ�Ҳ�ǿ��Եģ����ǲ���ά������LCT����������㡣
ps��
1. ��������DFS���ϵģ��������$dep$Ӧ��DFS��洢��������$dep[to[i]]=dep[x]+1$�������д�����⣩��
2. **`Access()`�и����������������������Ҫ�ҵ���ȴδ������ģ��ĵ㣬����������������ӣ�������ֱ������������**
3. ���ڲ����������$val[x]+val[y]-2*val[LCA(x,y)]+1$�Ϳ����ˣ�����Ҫ����$fa[LCA(x,y)]$��$x$����ɫ�ᱻ�������Σ���Ӧ��һ����ͳ����һ�Ρ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define B 17
const int N=1e5+5;

int n,cnt,dep[N],in[N],out[N],Enum,H[N],to[N<<1],nxt[N<<1];
int pos[N],id[N],log2[N<<1],tot,tm,st[N<<1][18];
struct Seg_Tree
{
	#define ls l,m,rt<<1
	#define rs m+1,r,rt<<1|1

	int val[N<<2],mx[N<<2],tag[N<<2];
	inline void Update(int rt){
		mx[rt]=std::max(mx[rt<<1],mx[rt<<1|1]);
	}
	inline void Add(int rt,int v){
		val[rt]+=v, tag[rt]+=v, mx[rt]+=v;
	}
	inline void PushDown(int rt){
		Add(rt<<1,tag[rt]), Add(rt<<1|1,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) val[rt]=mx[rt]=dep[l];
		else{
			int m=l+r>>1;
			Build(ls), Build(rs), Update(rt);
		}
	}
	int Query_P(int l,int r,int rt,int pos)
	{
		if(l==r) return val[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(pos<=m) return Query_P(ls,pos);
		return Query_P(rs,pos);
	}
	int Query_Max(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mx[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query_Max(ls,L,R),Query_Max(rs,L,R));
			else return Query_Max(ls,L,R);
		return Query_Max(rs,L,R);
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) Add(rt,v);
		else
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			if(L<=m) Modify(ls,L,R,v);
			if(m<R) Modify(rs,L,R,v);
			Update(rt);
		}
	}
}t;
namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],sk[N],L[N]/*Attention!*/;
	bool rev[N];
	inline void Update(int x){
		L[x]= lson?L[lson]:x;
	}
	inline void Rev(int x){
		std::swap(lson,rson), rev[x]^=1;
	}
	inline void PushDown(int x){
		if(rev[x]) Rev(lson),Rev(rson),rev[x]=0;
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[a]=x, fa[x]=b, son[a][l]=son[x][r], son[x][r]=a;
		Update(a);
	}
	void Splay(int x)
	{
		int t=1,a=x; sk[1]=x;
		while(n_root(a)) sk[++t]=a=fa[a];
		while(t) PushDown(sk[t--]);
		while(n_root(x))
		{
			if(n_root(a=fa[x])) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
//	#define D(A,B) printf("Modify:%d->%d %d\n",x,A,B);
	void Access(int x)
	{
		for(int pre=0; x; x=fa[pre=x])
		{
			Splay(x);
			if(rson) t.Modify(1,cnt,1,in[L[rson]],out[L[rson]],1);//L[]!!!
			if(pre) t.Modify(1,cnt,1,in[L[pre]],out[L[pre]],-1);
			rson=pre;
		}
	}
}
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f)
{
	int t=++tm; st[pos[x]=++tot][0]=tm, id[tm]=x;
	in[x]=++cnt;
	LCT::fa[x]=f;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) dep[cnt+1]=dep[in[x]]+1/*Attention!*/, DFS(to[i],x), st[++tot][0]=t;
	out[x]=cnt;
}
void Init_RMQ()
{
	for(int i=2; i<=tot; ++i) log2[i]=log2[i>>1]+1;
	for(int j=1; j<=log2[tot]; ++j)
		for(int i=tot-(1<<j-1); i; --i)
			st[i][j]=std::min(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int LCA(int l,int r)
{
	l=pos[l], r=pos[r];
	if(l>r) std::swap(l,r);
	int k=log2[r-l+1];
	return id[std::min(st[l][k],st[r-(1<<k)+1][k])];
}
int Query(int x,int y){
	int w=LCA(x,y);// printf("LCA:%d,%d:%d\n",x,y,w);
	return t.Query_P(1,cnt,1,in[x])+t.Query_P(1,cnt,1,in[y])-2*t.Query_P(1,cnt,1,in[w])+1;
}

int main()
{
	n=read();int q=read(),opt,x,y;
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	dep[1]=1, DFS(1,0), t.Build(1,cnt,1), Init_RMQ();
	while(q--)
	{
		opt=read(),x=read();
		if(opt==1) LCT::Access(x);
		else if(opt==2) y=read(), printf("%d\n",Query(x,y));
		else printf("%d\n",t.Query_Max(1,cnt,1,in[x],out[x]));
	}
	return 0;
}
