/*
24736kb	4284ms
���޸Ĳ�����һ�²�ַŵ���Ӧ���ϣ��ͳ�����ÿ���������ڳ��ִ���������ɫ����ͺ�[CF600E](http://codeforces.com/contest/600/problem/E)�����ˡ�ֱ����$dsu$��
�޸�ĳ����ɫ���ִ�����ʱ�����ֵ����$O(1)$��������׸�$set$�����Ը��Ӷ���$O(q\log^2n)$��������������
> ���ڸ��Ӷȣ���CF600E�ж�һ������޸���$O(1)$�ģ��������п�����$O(q)$��һ�����Ϲ��źܶ���޸ģ�����$dsu$�ĸ��Ӷȱ�֤���ڣ�ÿ����ֻ�ᱻͳ��$O(\log n)$�Σ����Բ���$set$���Ӷ�������$O(q\log n)$��
һЩϸ�ڣ�
����������������׵�ʱ�������Ҷ�����ϸ��£��������м�����ĳ����ɫ���ִ���$<0$���������RE...����Ϊ��ֵļ���������棬�ӱ���ڵײ㣩��
��������DFS����ͨ��ö��DFS����棬Ӧ�����Ż����ٳ�����
����BZOJ��z�����ݷ�Χ��ʵֻ��1e5�����Բ�����ɢ��233.
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int dep[N],fa[N],sz[N],son[N],top[N],L[N],R[N],A[N],Max,tm[N],cnt[N],Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
std::set<int> st[N];
struct Graph
{
	int Enum,H[N],nxt[N<<2],to[N<<2];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
	inline void AQ(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
}T,Q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]<dep[v]?u:v;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	A[L[x]=++Index]=x, top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=T.H[x],v; i; i=T.nxt[i])
			if((v=T.to[i])!=fa[x] && v!=son[x]) DFS2(v,v);
	}
	R[x]=Index;
}
inline void Add(int c)
{
	int t=tm[c]; ++tm[c];
	--cnt[t], ++cnt[t+1], st[t].erase(c), st[t+1].insert(c);
	if(t+1>tm[Max]||(t+1==tm[Max] && c<Max)) Max=c;
}
inline void Subd(int c)
{
	int t=tm[c]; --tm[c];
	--cnt[t], ++cnt[t-1], st[t].erase(c), st[t-1].insert(c);
	if(c==Max) !cnt[t] ? Max=*st[t-1].begin() : Max=*st[t].begin();
}
inline void Upd(int x)
{
	for(int i=Q.H[x]; i; i=Q.nxt[i])
		i&1 ? Add(Q.to[i]) : Subd(Q.to[i]);
}
void Solve(int x,bool keep)
{
	static int Time,vis[N];
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x] && v!=son[x]) Solve(v,0);
	if(son[x]) Solve(son[x],1);

	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x] && v!=son[x])
			for(int j=R[v]; j>=L[v]; --j) Upd(A[j]);//Ҫ����ö�� 
	Upd(x), Ans[x]=tm[Max]?Max:0;

	if(!keep)
	{
		Max=0, ++Time;
		for(int u=L[x]; u<=R[x]; ++u)
			for(int i=Q.H[A[u]]; i; i=Q.nxt[i])
			{
				int c=Q.to[i];
				if(vis[c]!=Time) vis[c]=Time, --cnt[tm[c]], st[tm[c]].erase(c), ++cnt[tm[c]=0];//, st[0].insert(c);//erase�����ڵ�Ԫ��û������ 
			}
	}
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<n; ++i) T.AE(read(),read());
	DFS1(1), DFS2(1,1);
	for(int i=1; i<=m; ++i)
	{
		int x=read(),y=read(),z=read(),w=LCA(x,y);
		Q.AQ(x,z), Q.AQ(w,z), Q.AQ(y,z), Q.AQ(fa[w],z);
	}
	Max=0, cnt[0]=n, Solve(1,1);
	for(int i=1; i<=n; ++i) printf("%d\n",Ans[i]);

	return 0;
}
