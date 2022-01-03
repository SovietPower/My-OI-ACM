#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int n,K,Enum,H[N],nxt[N<<1],to[N<<1],dis[N],pre[N],dgr[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	++dgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	++dgr[u], to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
int BFS(int s)
{
	static int q[N];
	memset(dis,0,sizeof dis);
	int h=0,t=1; q[0]=s, pre[s]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=pre[x]) dis[v]=dis[x]+1, pre[v]=x, q[t++]=v;
	}
	return q[t-1];
}
void DFS(int x,int fa,int dep)
{
	if(dep==K&&dgr[x]!=1) {puts("No"); exit(0);}
	else if(dep&&dep<K&&dgr[x]<=3) {puts("No"); exit(0);}
	else if(dep>K) {puts("No"); exit(0);}
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa) DFS(to[i],x,dep+1);
}

int main()
{
	n=read(),K=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	int u=BFS(1),root=BFS(u);
	if(dis[root]!=K<<1) return puts("No"),0;
	for(int tmp=K; tmp--; root=pre[root]);
	if(dgr[root]<3) return puts("No"),0;
	DFS(root,root,0), puts("Yes");

	return 0;
}
