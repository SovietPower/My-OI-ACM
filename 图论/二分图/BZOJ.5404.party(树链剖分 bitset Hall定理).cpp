/*
220140kb	7192ms(������)
$Description$
����һ������ÿ������һ���ز�$a_i$������ͬ����$q$��ѯ�ʣ�ÿ�θ�$2\leq c\leq 5$���˼���λ�ã����ǻ��ߵ����ǵĹ���LCA����
ÿ���˿��Դ����ߵ�·���ϴ�һЩ�ز����������㣺�����˴����ز�������ͬ��������������ͬ�ز���
�����һ���ܴ��������ز���
$n\leq 3\times 10^5,\ q\leq 5\times 10^4$���ز�����$\leq 1000$��
$Solution$
ֻ��ָ�򸸽ڵ�ĵ����·������c���˿϶���LCA����ϡ���ô�ͳ�����c����LCA��·����������x�������ܴ�c��·���и�ѡ��x�����������ǲ�ͬ��
��Ҫά��һ��·������������������������+ÿ����ά��һ��bitset�������vectorһ������һ��bitset��SDOI R2�ֳ�����Ҽǵÿռ仹�����ر�󡣡���Ȼ��������ֻ��1000�֣�һ���㿪һ��bitsetû���⡣���ϲ�ʱ��Ҫͨ���߶�����
�������x����ôc���˶�Ҫ�ӿ�ѡ�ز��в��ظ���ѡx������ÿ���˲��x�������һ������ͼ�걸ƥ�䡣
��Hall������߼���(c*x����)����һ���Ӽ����ұ߼������ڵĵ���Ӧ��С�ڸ��Ӽ���С����Ϊÿ���˵�x�����������ͬ(������x��)�����Զ�ÿ����ֻ���ж�x����ѡ���Ӽ���
c��С��2^cö���Ӽ������ұ߼������ڵ�������ѡ���˵�bitset�Ĳ��Ĵ�Сsize����ö����s���ˣ���ôÿ��ö���� x*s <= size��
���� x = min{size/s}��
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bitset std::bitset<M>
const int N=3e5+3,M=1002;

int n,m,Q,A[N],num[100],H[N],Enum,to[N],nxt[N],fa[N],dep[N],sz[N],son[N],top[N],dfn[N],Index;
Bitset bit[N];//prefix
char IN[MAXIN],*SS=IN,*TT=IN;//,OUT[N*30],*O=OUT;
struct Segment_Tree
{
	#define lson rt<<1
	#define rson rt<<1|1
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	int col[N];
	Bitset t[N<<2];

	#define Update(rt) t[rt]=t[lson]|t[rson]
	void Build(int l,int r,int rt)
	{
		if(l==r) t[rt][col[l]]=1;
		else Build(l,l+r>>1,rt<<1), Build((l+r>>1)+1,r,rt<<1|1), Update(rt);
	}
	Bitset Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return t[rt];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(ToL,L,R)|Query(ToR,L,R);
			else return Query(ToL,L,R);
		return Query(ToR,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
//inline void print(int x)
//{
//	if(x>9) print(x/10);
//	*O++ = x%10+'0';
//}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
	{
		fa[v=to[i]]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
		if(sz[v]>mx) mx=sz[v], son[x]=v;
	}
}
void DFS2(int x,int tp)
{
	top[x]=tp, dfn[x]=++Index, T.col[Index]=A[x];
	bit[x][A[x]]=1;
	if(son[x])
	{
		bit[son[x]]|=bit[x], DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=son[x]) DFS2(to[i],to[i]);
	}
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
Bitset Query(int u,int w)
{
	Bitset s;
	while(top[u]!=top[w]) s|=bit[u], u=fa[top[u]];
	return s|T.Query(1,n,1,dfn[w],dfn[u]);
}

int main()
{
	for(int i=1,s=0; i<1<<5; num[i++]=s,s=0)
		for(int j=0; j<5; ++j) if(i>>j & 1) ++s;
	n=read(),m=read(),Q=read();
	for(int i=2; i<=n; ++i) AddEdge(read(),i);
	for(int i=1; i<=n; ++i) A[i]=read();
	DFS1(1), DFS2(1,1), T.Build(1,n,1);
	for(int c,p[7],lca,ans; Q--; )
	{
		c=read();
		for(int i=1; i<=c; ++i) p[i]=read();
		lca=LCA(p[1],p[2]);
		for(int i=3; i<=c; ++i) lca=LCA(lca,p[i]);
		ans=m;
		for(int s=1; s<1<<c; ++s)
		{
			Bitset tmp;
			for(int i=1; i<=c; ++i)
				if(s>>i-1 & 1) tmp|=Query(p[i],lca);
			ans=std::min(ans,(int)(tmp.count()/num[s]));
		}
		printf("%d\n",ans*c);
//		print(ans*c), *O++='\n';
	}
//	fwrite(OUT,O-OUT,1,stdout);

	return 0;
}
