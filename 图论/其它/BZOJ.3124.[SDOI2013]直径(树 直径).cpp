/*
17660kb	1932ms
��Ҫ�ж�һ�����Ƿ�������ֱ���������ı� 
����֤��(����)�����ϵĶ���ֱ��һ���Ǵ�ĳ��(Щ)��������м侭��ͬһ����(Ϊ��������ϵı߽����ؼ��ߺ���)������ĳ��(Щ)�������
ֻ��Ҫ�жϵ�ǰ���ֱ���ϵ����б��Ƿ�Ϊ�ؼ��ߡ����һ����(u->v)���ǹؼ��ߣ���ô˵����(ֱ��)��ǰ��u������v֮�⻹��u->v'���������(�õ�ֱ��)�����Ƕ�ÿ�����¼�ӽڵ����Զ(ֱ��)����Զ����(���ϸ�����һ��������)�ͺ��ˡ�
����Ǵ�R1�������������ǿ����е�R2�Ǳߵķǹؼ��ߣ���R2������һ�鼴���е�R1���õ��м���������
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;
const LL INF=1e10;

int n,Ans,root,Enum,H[N],to[N<<1],nxt[N<<1],fa[N];
LL Max,dis[N],mx[N],s_mx[N],val[N<<1];
bool is_d[N],Mark[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void pre_DFS(int x,LL d)
{
	if(d>Max) Max=d, root=x;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) fa[to[i]]=x,pre_DFS(to[i],d+val[i]);
}
void DFS(int x,int f)
{
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=f)
		{
			DFS(v,x);
			if(mx[x]<val[i]+mx[v]) mx[x]=val[i]+mx[v];
			else if(s_mx[x]<val[i]+mx[v]) s_mx[x]=val[i]+mx[v];
		}
}
void DFS_for_Ans(int x,int f,LL d)
{
	for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=f&&is_d[to[i]])
				if(s_mx[x]+d>=Max) {Mark[x]=1/*�ڴ˶Ͽ�*/; return;}
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f&&is_d[to[i]])
			DFS_for_Ans(to[i],x,d+val[i]);
}

int main()
{
//	freopen("diameter.in","r",stdin);
//	freopen("diameter.out","w",stdout);

	n=read();
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	Max=-INF, pre_DFS(1,0);
	int u=root,v;
	Max=-INF, fa[u]=0, pre_DFS(u,0), v=root;
	while(root!=u) is_d[root]=1,root=fa[root];
	is_d[root]=1;

	DFS(u,-1), DFS_for_Ans(u,-1,0);
	memset(mx,0,sizeof mx), memset(s_mx,0,sizeof s_mx);
	DFS(v,-1), DFS_for_Ans(v,-1,0);
	for(bool f=0; v!=u; v=fa[v],Ans+=f)
		if(Mark[v]) f^=1;
	printf("%lld\n%d",Max,Ans);

	return 0;
}
