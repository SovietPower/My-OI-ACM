/*
13704kb	3020ms(13572kb	3216ms)
给定一颗树，将树边改成有向边，求连通的点对个数的最大最小值。点对连通，要么a能到达b，要么b能到达a(n<=250000)。
最小可到达点对数自然是把一条路径上的边不断反向，也就是黑白染色后都由黑点指向白点。这样答案就是$n-1$。
最大可到达点对数，容易想到找一个点$a$，然后将其子树分为两部分$x,y$，$x$子树所有边全指向$a$，$a$与$y$子树之间的边全指向$y$。这样答案就是$sz[x]\times sz[y]$，要让$sz[x],sz[y]$尽量相等。找重心就好了。
然后DP，求划分重心两部分子树大小分别为$x$和$n-1-x$是否可行。
$f[i]$表示一部分子树$sz$和为$i$是否可行。转移就是个可行性背包，可以用$bitset$优化到$\frac{n^2}{w}$，但还是不够。
对于$size\geq\sqrt{n}$的子树，最多不会超过$\sqrt{n}$个，可以直接背包转移。
对于$size<\sqrt{n}$的子树，根据$size$按多重背包做，可以直接二进制拆分。
复杂度为$O(\frac{n\sqrt{n}\log n}{w})$。
注意到$\sum sz[i]=n$，所以$sz[i]$最多有$O(\sqrt{n})$种（$1+2+...+\sqrt{n}\approx n$）。即这是一个有$O(\sqrt{n})$个物品的多重背包。用二进制拆分有$O(\sqrt{n}\log n)$个物品。
二进制优化，从小到大，有一个物品$x$出现超过两次，就把两个合并成一个给$2x$。这样物品总数就是$O(\sqrt{n})$了。
所以复杂度为$O(\frac{n\sqrt{n}}{w})$。（虽然实际比上面的做法还慢一点儿==）
当根节点度数大于$\sqrt{n}$时可以用堆做：https://blog.csdn.net/neither_nor/article/details/52725690。~~大体看了看15年论文没看见这个做法 不细看了~~
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=250005;

int n,Enum,H[N],nxt[N<<1],to[N<<1],sz[N],root,Max,cnt[N];
std::bitset<N> f;

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
void Get_root(int x,int f)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=f)
		{
			Get_root(v,x), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,n-sz[x]);
	if(mx<Max) Max=mx, root=x;
}
void DFS(int x,int f)
{
	sz[x]=1;//重算一遍sz啊 想什么呢 
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=f) DFS(v,x), sz[x]+=sz[v];
}

int main()
{
	n=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	Max=1e9, Get_root(1,1), DFS(root,0);

//	f[0]=1;//O(n*sqrt(n)/w)
//	for(int i=H[root]; i; i=nxt[i]) ++cnt[sz[to[i]]];
//	for(int i=1; i<=n; ++i)
//		if(cnt[i]>2) cnt[i<<1]+=(cnt[i]-1)>>1, cnt[i]=1+!(cnt[i]&1);
//	for(int i=1; i<=n; ++i)
//		while(cnt[i]--) f|=f<<i;

	f[0]=1; const int lim=sqrt(n);//O(n*sqrt(n)*logn/w)
	for(int i=H[root]; i; i=nxt[i])
		if(sz[to[i]]<lim) ++cnt[sz[to[i]]];
		else f|=f<<sz[to[i]];
	for(int i=1; i<lim; ++i)
		for(int j=cnt[i],k=1; j; j-=k,k<<=1)
			if(j>k) f|=f<<i*k;
			else {f|=f<<i*j; break;}

	LL ans=0;
	for(int i=1; i<n; ++i) if(f[i]) ans=std::max(ans,1ll*i*(n-1-i));
	for(int i=1; i<=n; ++i) ans+=sz[i];
	printf("%d %lld\n",n-1,ans-n);

	return 0;
}
