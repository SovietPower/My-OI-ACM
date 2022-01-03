/*
936kb	20ms
$Description$
给定$n$棵无根树。对每棵树，输出与它同构的树的最小编号。
$n及每棵树的点数\leq 50$。
$Solution$
对于一棵无根树，它的重心最多不超过两个。
所以从两个重心分别DFS，可以将无根树转为有根树。
然后可以用树哈希，或者括号序（直接用string）来表示每棵树。
对于每个点的每棵子树，可以对哈希值或字符串sort一下用最小表示法记录。
*/
#include <cstdio>
#include <cctype>
#include <string>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=53;

std::string str[N],s[N];
struct Tree
{
	int Min,Enum,H[N],nxt[N<<1],to[N<<1],sz[N],f[N];
	inline void AE(int u,int v)
	{
		if(u)
			to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum,
			to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
	void Find_root(int x,int fa,int tot)
	{
		int mx=0; sz[x]=1;
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa)
				Find_root(v,x,tot), sz[x]+=sz[v], mx=std::max(mx,sz[v]);
		Min=std::min(Min,f[x]=std::max(mx,tot-sz[x]));
	}
	void DFS(int x,int fa)
	{
		static std::string tmp[N];
		s[x]="(";
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa) DFS(to[i],x);
		int t=0;
		for(int i=H[x]; i; i=nxt[i])//先处理完其它子树 才能用这个tmp数组啊→_→ 
			if(to[i]!=fa) tmp[++t]=s[to[i]];
		std::sort(tmp+1,tmp+1+t);
		for(int i=1; i<=t; ++i) s[x]+=tmp[i];
		s[x]+=")";
	}
}T[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int tot=read();
	for(int t=1; t<=tot; ++t)
	{
		int n=read();
		for(int i=1; i<=n; ++i) T[t].AE(read(),i);
		T[t].Min=N, T[t].Find_root(1,1,n);
		std::string now="";
		for(int i=1; i<=n; ++i)
			if(T[t].f[i]==T[t].Min) T[t].DFS(i,i), now=std::max(now,s[i]);
		str[t]=now;
	}
	for(int i=1; i<=tot; ++i)
	{
		int j=1;
		while(str[i]!=str[j]) ++j;
		printf("%d\n",j);
	}
	return 0;
}
