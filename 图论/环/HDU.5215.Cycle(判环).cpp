/*
93MS	11940K
$Description$
给定$n$个点$m$条边的无向图，问是否存在一个长度为奇数/偶数的简单环。n<=1e5,m<=3e5。
$Solution$
容易想到DFS时直接黑白染色。但是只这样会遗漏一种偶环。
对于奇环黑白染色即可，二分图一定不存在奇环，存在奇环一定不是二分图。
对于偶环，因为两个奇环如果有至少一个公共点，它们都去掉公共部分后奇偶性仍相同，就会形成偶环。
所以对于奇环暴力在点上打标记即可。
也可以Tarjan缩每个双连通分量，只有在这个双连通分量仅是一个奇环时，其中不存在偶环。
但是判负环时要判p!=0结束循环？why？
*/
//#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=6e5+5;

int Enum,H[N],nxt[M],to[M],vis[N],fa[N];
bool odd,even,tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;

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
void DFS(int x)
{
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			if(vis[v]==-1) fa[v]=x, vis[v]=vis[x]^1, DFS(v);
			else if(vis[x]^vis[v]) even=1;
			else
			{
				odd=1; int p=x;
				while(!even && p!=v && p)//p!=0???
				{
					if(tag[p]) even=1;
					tag[p]=1, p=fa[p];
				}
//				if(tag[v]) even=1;//最上面的点...无所谓了？
//				else tag[v]=1;
			}
		}
}
void Work()
{
	odd=even=Enum=0, memset(H,0,sizeof H);
	memset(vis,0xff,sizeof vis), memset(tag,0,sizeof tag);

	int n=read(),m=read();
	while(m--) AE(read(),read());
	for(int i=1; i<=n&&(!odd||!even); ++i)
		if(vis[i]==-1) vis[i]=fa[i]=0, DFS(i);
	puts(odd?"YES":"NO"), puts(even?"YES":"NO");
}

int main()
{
	for(int T=read(); T--; Work());
	return 0;
}
