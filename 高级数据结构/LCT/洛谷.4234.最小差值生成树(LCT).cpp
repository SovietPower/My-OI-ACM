/*
先将边排序，这样就可以按从小到大的顺序维护生成树，枚举到一条未连通的边就连上，已连通则(用当前更大的)替换掉路径上最小的边，这样一定不会更差。
每次构成树时更新答案。答案就是当前边减去生成树上最小边的权值。
LCT上维护最小边的编号。求最小边把树上的边用vis[]标记即可。
不熟啊.
(另外暴力可以排序后枚举一个分界点，在它之后求最小生成树，在它之前求最大生成树)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define INF 10000007
const int N=5e4+5,M=2e5+5,S=N+M;

int n,m,_fa[N];
bool vis[M];
struct Edge
{
	int fr,to,val;
	Edge() {}
	Edge(int f,int t,int v): fr(f),to(t),val(v) {}
	bool operator <(const Edge &a)const {
		return val<a.val;
	}
}e[M];
namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[S],son[S][2],sk[S],pos[S],val[S];
	bool tag[S];
	inline int Get(int x,int y){//取最小的边 
		return val[x]<val[y]?x:y;
	}
	inline void Update(int x){
		pos[x]=Get(x,Get(pos[lson],pos[rson]));//是左右儿子的最小边pos[]！
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	inline void Rev(int x){
		std::swap(lson,rson), tag[x]^=1;
	}
	void PushDown(int x){
		if(tag[x]) Rev(lson),Rev(rson),tag[x]=0;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[a]=x, fa[x]=b, son[a][l]=son[x][r], son[x][r]=a;
		Update(a);
	}
	void Splay(int x)
	{
		int t=1,a=x; sk[1]=x;
		while(n_root(a)) sk[++t]=a=fa[a];
		while(t) PushDown(sk[t--]);
		while(n_root(x))
		{
			if(n_root(a=fa[x])) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
	void Access(int x){
		for(int pre=0; x; x=fa[pre=x])
			Splay(x), rson=pre, Update(x);
	}
	void Make_root(int x){
		Access(x), Splay(x), Rev(x);
	}
	void Split(int x,int y){
		Make_root(x), Access(y), Splay(y);
	}
	void Link(int x){
		Make_root(e[x].to), fa[fa[e[x].to]=x+N]=e[x].fr;
	}
	void Cut(int x){
		Access(e[x-N].to), Splay(x), lson=rson=fa[lson]=fa[rson]/*=fa[x]*/=0;//fa[x]应该是用不到吧。。注意更新顺序！后更新lson,rson...
	}
}
using namespace LCT;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Get_fa(int x){
	return x==_fa[x]?x:_fa[x]=Get_fa(_fa[x]);
}

int main()
{
	n=read(),m=read();
	val[0]=INF;//空节点！
	for(int i=1; i<=n; ++i) _fa[i]=i, val[i]=INF;//点有自己的权值，设为INF避免影响答案(最小边) 
	for(int u,v,w,i=1; i<=m; ++i) u=read(),v=read(),w=read(),e[i]=Edge(u,v,w);
	std::sort(e+1,e+1+m);
//	for(int i=1; i<=m; ++i) val[i+N]=e[i].val;
	int res=1e6;
	for(int p=1,x,y,k=1,i=1; i<=m; ++i)
	{
		val[i+N]=e[i].val, x=e[i].fr, y=e[i].to;
		if(k<n && Get_fa(x)!=Get_fa(y))
		{
			_fa[_fa[x]]=_fa[y];//路径压缩后 
			Link(i), vis[i]=1;
			if(++k>=n) res=e[i].val-e[p].val;
		}
		else if(x!=y)//不要计算重边 
		{
			Split(x,y);
			vis[pos[y]-N]=0, vis[i]=1;//别忘了Splay(y)后再用y的信息pos[y]！而且要先用pos[y]清vis再Cut().
			while(!vis[p]) ++p;
			Cut(pos[y]), Link(i);
			if(k>=n) res=std::min(res,e[i].val-e[p].val);
		}
	}
	printf("%d",res);

	return 0;
}
