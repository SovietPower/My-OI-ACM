/*
858MS 5528K(怎么那么多跑的很快的啊--点分？)
$Description$
给定一棵树，每个点有权值，在$[0,m-1]$之间。求异或和为$0,1,...,m-1$的非空连通块各有多少个。
$n\leq 1000,m\leq 2^{10}$。
$Solution$
在每个连通块的根节点处统计。$f[x][k]$表示以$x$为根，异或和为$k$的连通块（子树）有多少个。
那么$f[x][k]=f[x][k]+\sum_{i\ \mathbb{xor}\ j=k}f[x][i]*f[v][j],\ v=son[x]$。
后一部分就是异或卷积，可以用$FWT$优化。
具体实现，不需要每次转移一棵子树都$FWT,IFWT$一次。中间过程一直用$FWT$后的$f$计算就可以了。
可能有的问题是，$f$本身（$f[x][k]$）还要加上自己，必须在转移的时候$IFWT$回去？不妨在$f[v]$计算完之后$IFWT(f[v])$，令$f[v][0]++$，然后再$FWT$回去，用这个$f[v]$去更新$f[x]$。这样就可以直接用$FWT$后的$f$计算了。
$f[x][0]$在计算前是不能$+1$的，因为必须要求$f[x]$代表的**非空连通块**是以$x$为根的。
最后把所有$f[i]\ IFWT$回去，再令$f[i][0]--$。
复杂度$O(nm\log m)$。
所以有这两种写法的差异。。
https://www.cnblogs.com/cjyyb/p/9065611.html
https://blog.csdn.net/clover_hxy/article/details/72722352
还可以点分治。。在第二篇里有。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define inv2 500000004
#define mod 1000000007
#define Add(x,y) (x+y>=mod?x+y-mod:x+y)
#define Sub(x,y) (x<y?x-y+mod:x-y)
typedef long long LL;
const int N=1024+5;

int lim,Enum,H[N],nxt[N<<1],to[N<<1],f[1005][N];
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
void FWT(int *a,int lim,int opt)
{
	for(int i=2; i<=lim; i<<=1)
		for(int j=0,mid=i>>1; j<lim; j+=i)
			for(int k=j; k<j+mid; ++k)
			{
				int x=a[k], y=a[k+mid];
				a[k]=Add(x,y), a[k+mid]=Sub(x,y);
				if(opt==-1) a[k]=1ll*a[k]*inv2%mod, a[k+mid]=1ll*a[k+mid]*inv2%mod;
			}
}
void DFS(int x,int fa)
{
	FWT(f[x],lim,1);
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			for(int j=0; j<lim; ++j) f[x][j]=1ll*f[x][j]*f[v][j]%mod;
		}
	FWT(f[x],lim,-1), f[x][0]=Add(f[x][0],1), FWT(f[x],lim,1);
}

int main()
{
	static LL Ans[N];
	for(int T=read(); T--; )
	{
		Enum=0, memset(H,0,sizeof H);
		memset(f,0,sizeof f), memset(Ans,0,sizeof Ans);
		int n=read(),m=read(); lim=m;
		for(int i=1; i<=n; ++i) ++f[i][read()];
		for(int i=1; i<n; ++i) AE(read(),read());
		DFS(1,1);
		for(int i=1; i<=n; ++i)
		{
			FWT(f[i],lim,-1), f[i][0]=Sub(f[i][0],1);
			for(int j=0; j<m; ++j) Ans[j]+=f[i][j];
		}
		for(int i=0; i<m; ++i) printf("%d%c",int(Ans[i]%mod)," \n"[i+1==m]);//输出格式。。
	}
	return 0;
}
