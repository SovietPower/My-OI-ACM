/*
�������������һ������Ȼ��ȥ������ֱ����
��Ҫ�������ֱ��������������ĵ�Ķ���Ӧ����С(Ҫ����ž��Ǻܶ�ֲ�����)��
ö��/���һ�����ڵ�x��������ʼDFS��ÿ�������߶�����С�ĵ�v(ע����������ĵ�Ķ���-1)�������ϵı�x->v��
DFS�����������С�ĵ�v�󣬿��Դ�x��������δ���ʵĵ㣬��չ����
*/
#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=10005,M=2e4+5;

int n,m,Max,V,pre[N],Enum,H[N],nxt[M],to[M],_Enum,_H[N],_nxt[M],_to[M],Dgr[N],dgr[N],ans[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	++Dgr[u], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++Dgr[v], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline void AddTree(int u,int v){
	_to[++_Enum]=v, _nxt[_Enum]=_H[u], _H[u]=_Enum;
	_to[++_Enum]=u, _nxt[_Enum]=_H[v], _H[v]=_Enum;
}
void Build(int x)
{
	vis[x]=1;
	int way=0;
	for(int i=H[x]; i; i=nxt[i]) --dgr[to[i]];
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&(dgr[way]>dgr[to[i]]||(dgr[way]==dgr[to[i]]&&rand()&1))) way=to[i];
//		if(!vis[to[i]]&&dgr[way]>dgr[to[i]]) way=to[i];//�Բ��� 
	if(way) AddTree(x,way), Build(way);
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) AddTree(x,to[i]), Build(to[i]);
}
void DFS(int x,int f,int d)
{
	if(d>Max) Max=d, V=x;
	for(int i=_H[x]; i; i=_nxt[i])
		if(_to[i]!=f) pre[_to[i]]=x, DFS(_to[i],x,d+1);
}
void Solve(int i)
{
	_Enum=0, memset(_H,0,sizeof _H);
	memset(vis,0,sizeof vis), memcpy(dgr,Dgr,sizeof dgr), Build(i);
	Max=0, DFS(i,i,1);
	int u=V;
	Max=0, DFS(u,u,1);
	if(Max>ans[0]){
		ans[ans[0]=Max]=V;
		while(V!=u) ans[--ans[0]]=V=pre[V];
		ans[0]=Max;
	}
}

int main()
{
//	freopen("guide.in","r",stdin);
//	freopen("guide.out","w",stdout);

	srand(time(NULL));
	n=read(),m=read();
	for(int i=1; i<=m; ++i) AddEdge(read(),read());
	Dgr[0]=1000000;
	for(int T=10000; T; --T) Solve(rand()%n+1);//����Ҫ��� 
//	for(int i=1; i<=n; ++i) Solve(i);
	printf("%d\n",ans[0]);
	for(int i=1; i<=ans[0]; ++i) printf("%d\n",ans[i]);

	return 0;
}
