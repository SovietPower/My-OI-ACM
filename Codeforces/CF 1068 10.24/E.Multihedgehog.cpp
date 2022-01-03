#include <cstdio>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define Failed {puts("No"); exit(0);}
typedef long long LL;
const int N=1e5+5;

int n,K,Enum,H[N],nxt[N<<1],to[N<<1],dep[N],dgr[N];

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
	int root=0;
	for(int i=1; i<=n; ++i)
		if(dgr[i]==3) {root=i; break;}
	if(!root) return puts("No"),0;
	DFS(root,root,0);
	puts("Yes");

	return 0;
}
