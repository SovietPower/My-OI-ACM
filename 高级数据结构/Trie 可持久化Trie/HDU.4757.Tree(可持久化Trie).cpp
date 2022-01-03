/*
1201MS	30704K
$Description$
����һ���������е�Ȩ��Q��ѯ��x,y,z����x��y�ļ�·���У���z����ܵõ����������Ƕ��١�
$Solution$
���ڸ���������ѯ�ʣ����ǿ��Խ�Trie�����Ӹ�λ����λ̰�ĵ��ߣ������ŵľ��ߣ���
ͬ���ϵ���ϯ��һ�������ø��ڵ�ĸ��ڵ㽨�������ǿɳ־û�Trie��
��w=LCA(u,v)����Ϊֻ��xorһ������������u,v,w������ĸ��ڵ�Ϳ����ˣ�������ж�һ��w�Ƿ���ܸ��ţ�����Ҫfa[w]����
��u,v,w����Trie���ߣ���sz[u]+sz[v]-2*sz[w]>0�����ߡ�
����ѯ��ͬ��Ҳ��������
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define BIT 15
const int N=1e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],A[N],root[N],fa[N],dep[N],sz[N],son[N],top[N];
struct Trie
{
	#define S N*20//N*18Ϊʲô������ 
	int tot,sz[S],son[S][2];

	inline int New_Node()
	{
		++tot, sz[tot]=0, son[tot][0]=son[tot][1]=0;
		return tot;
	}
	void Insert(int x,int y,int v)
	{
		for(int i=BIT; ~i; --i)
		{
			int c=v>>i&1;
			son[x][c]=New_Node(), son[x][c^1]=son[y][c^1];
			x=son[x][c], y=son[y][c];
			sz[x]=sz[y]+1;//������ڵ��sz����Ҫ�� 
		}
	}
	int Query(int x,int y,int w,int v)
	{
		int res=0,tmp=A[w]^v;
		w=root[w];
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1;
			if(sz[son[x][c]]+sz[son[y][c]]-2*sz[son[w][c]]>0)
				x=son[x][c], y=son[y][c], w=son[w][c], res|=1<<i;
			else
				c^=1, x=son[x][c], y=son[y][c], w=son[w][c];
		}
		return std::max(res,tmp);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]<dep[v]?u:v;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	top[x]=tp;
	T.Insert(root[x]=T.New_Node()/**/,root[fa[x]],A[x]);
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x] && v!=son[x]) DFS2(v,v);
	}
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		T.tot=Enum=0, memset(H,0,sizeof H);
		memset(son,0,sizeof son);//!
//		memset(root,0,sizeof root);

		int Q=read();
		for(int i=1; i<=n; ++i) A[i]=read();
		for(int i=1; i<n; ++i) AE(read(),read());
		DFS1(1), DFS2(1,1);
		for(int u,v; Q--; ) u=read(),v=read(),printf("%d\n",T.Query(root[u],root[v],LCA(u,v),read()));
	}
	return 0;
}
