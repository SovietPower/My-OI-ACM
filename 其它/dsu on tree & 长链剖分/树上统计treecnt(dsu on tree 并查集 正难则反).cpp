/*
https://www.cnblogs.com/SovietPower/p/9688048.html
枚举每条边，计算它的贡献。
那么我们要判断有多少连续区间的点跨过这条边，并不好算，反过来去求在这条边的两侧分别有多少个连续区间。
那么显然有$O(n^2)$的做法，即对每条边DFS它的两侧，枚举一下每一侧的连续区间。
我们还可以DFS这棵树，对于每个点我们需要计算它子树内和子树外的连续区间数。
对于子树内的点，并查集显然是可以维护的（每次合并相邻点成为一个连续区间时新产生的连续区间数可算，就是两个集合size的乘积）。
对于子树外的点怎么算呢。我们可以先假设子树外为$1,2,...,n$，且有这些区间。我们每次在子树中加入点时，就把它从子树外的集合的点中删掉，并计算子树外少的区间数。
我们发现不需要n个元素的集合，也不需要这样删。在一个初始只有0和n+1的空集合里，每次加入子树内的点，然后计算，也是等价的。
于是我们需要对每个子树合并并查集及处理set。
可以用dsu on tree，每次先处理完轻儿子的子树，每次处理完都清空那棵子树的贡献/状态（并查集、set）。最后处理重儿子所在子树，并保留其状态。
处理完这整棵子树后（也就是算完该边答案后），再把子树内其它未加入的轻子树给加入并查集、set。
dsu的复杂度是$O(n\log n)$的，再套上别的，复杂度为$O(n\log^2n)$。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Calc(x) (1ll*(x)*(x-1)>>1ll)//区间个数 
typedef long long LL;
const int N=1e5+5;

int n,Enum,H[N],nxt[N<<1],to[N<<1],fa[N],sz[N],son[N],Fa[N],size[N];
bool vis[N];//计算子树内的连续区间（是否子树内已存在相邻的）
LL Ans,sum1,sum2;
std::set<int> st;
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
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, DFS1(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
int Find(int x)
{
	return x==Fa[x]?x:Fa[x]=Find(Fa[x]);
}
void Upd(int x)
{
	st.insert(x);//我怎么记得有返回值(iterator)来...
	std::set<int>::iterator it=st.find(x),pre=it,nxt=++it;
	--pre;
	sum2-=Calc(*nxt-*pre-1);//子树外以前的连续区间被分割 
	sum2+=Calc(x-*pre-1)+Calc(*nxt-x-1);

	vis[x]=1;
	if(vis[x-1])
	{
		int r1=Find(x-1),r2=Find(x);//它们之前显然不会在一个集合啊（它们之间只会算一次，要么是加x-1，以前有x；要么是加x，以前有x-1）。
		sum1+=1ll*size[r1]*size[r2];
		Fa[r1]=r2, size[r2]+=size[r1];
	}
	if(vis[x+1])
	{
		int r1=Find(x+1),r2=Find(x);
		sum1+=1ll*size[r1]*size[r2];
		Fa[r1]=r2, size[r2]+=size[r1];
	}
}
void Clear(int x)
{
	Fa[x]=x, size[x]=1, vis[x]=0;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) Clear(to[i]);
}
void Update(int x)
{
	Upd(x);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) Update(to[i]);
}
void DFS2(int x)
{
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x]&&v!=son[x])
		{
			DFS2(v), Clear(v);
			st.clear(), st.insert(0), st.insert(n+1);
			sum1=0, sum2=Calc(n);//还是在DFS完子树后就初始化吧 
		}
	if(son[x]) DFS2(son[x]);

	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x]&&v!=son[x]) Update(v);

	Upd(x);
	Ans+=Calc(n)-sum1-sum2;
}

int main()
{
//	freopen("treecnt.in","r",stdin);
//	freopen("treecnt.out","w",stdout);

	n=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	for(int i=1; i<=n; ++i) Fa[i]=i,size[i]=1;//!
	st.insert(0), st.insert(n+1);//边界.
	sum1=0, sum2=Calc(n), DFS1(1), DFS2(1), printf("%lld\n",Ans);

	return 0;
}
