/*
13032kb	76ms
记以$1$为根DFS时每个点的深度是$dep_i$。对于一条限制$(a,b,D)$，满足条件的点$x$满足：$dep_a+dep_b-2dep_x\leq D\Rightarrow dep_x\geq\frac{dep_u+dep_v-D}{2}$。
那么$dep_x$最小是$\max\{0,\ \lceil\frac{dep_u+dep_v-D}{2}\rceil\}$（先不考虑负数的情况）。
记$p$为所有$m$条限制中，$\max\{0,\ \lceil\frac{dep_u+dep_v-D}{2}\rceil\}$最大的那个点$x$。
有一个结论是：若$p$不能满足所有限制，则一定无解。否则$p$为一个合法的解。
$p$就是要求最严格的限制所对应的那个点。对于和$p$不在同一棵子树里的限制，显然该限制要满足$p$；在同一棵子树内的，因为$p$是最严格的，所以只要满足$p$就可以啦。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int Enum,H[N],nxt[N<<1],to[N<<1],fa[N],dep[N],A[N],B[N],D[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
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
		if((v=to[i])!=fa[x]) fa[v]=x, dep[v]=dep[x]+1, DFS(v);
}

int main()
{
	for(int T=read(); T--; )
	{
		const int n=read(),m=read();
		Enum=0, memset(H,0,n+1<<2);
		for(int i=1; i<n; ++i) AE(read(),read());
		dep[1]=0, fa[1]=0, DFS(1);
		int mx=0,p=0;
		for(int i=1; i<=m; ++i)
		{
			int t=dep[A[i]=read()]+dep[B[i]=read()]-(D[i]=read());
			if(t>mx) mx=t, p=i;
		}
		if(!mx) {puts("TAK 1"); continue;}
		int x=A[p];
		for(int t=dep[x]-(mx+1)/2; t>0; --t,x=fa[x]);
		dep[x]=0, fa[x]=0, DFS(x);
		bool fg=1;
		for(int i=1; i<=m; ++i)
			if(dep[A[i]]+dep[B[i]]>D[i]) {fg=0; break;}
		fg?printf("TAK %d\n",x):puts("NIE");
	}
	return 0;
}
