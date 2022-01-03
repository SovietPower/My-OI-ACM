/*
13032kb	76ms
����$1$Ϊ��DFSʱÿ����������$dep_i$������һ������$(a,b,D)$�����������ĵ�$x$���㣺$dep_a+dep_b-2dep_x\leq D\Rightarrow dep_x\geq\frac{dep_u+dep_v-D}{2}$��
��ô$dep_x$��С��$\max\{0,\ \lceil\frac{dep_u+dep_v-D}{2}\rceil\}$���Ȳ����Ǹ������������
��$p$Ϊ����$m$�������У�$\max\{0,\ \lceil\frac{dep_u+dep_v-D}{2}\rceil\}$�����Ǹ���$x$��
��һ�������ǣ���$p$���������������ƣ���һ���޽⡣����$p$Ϊһ���Ϸ��Ľ⡣
$p$����Ҫ�����ϸ����������Ӧ���Ǹ��㡣���ں�$p$����ͬһ������������ƣ���Ȼ������Ҫ����$p$����ͬһ�������ڵģ���Ϊ$p$�����ϸ�ģ�����ֻҪ����$p$�Ϳ�������
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
