/*
题意: 有一张图，求一条x->y的路径，使得路径上最长边尽量短并输出它的长度。会有<=5000次删边。
这实际上就是动态地维护MST。用LCT维护MST，路径询问也能直接查询，每次删边看这条边是否在MST上。
只有1000个点！边直接矩阵存。
而且删边次数很少，于是最初想的是每次删边用堆优化Prim O(nlogn)重新求一遍MST。但是5000*1000*10=5e7。。(也许行吧)
日常删边改成加边，离线即可。加边时MST上的求路径Max，看是否需要Cut,重新Link.(正序的话还要找一遍没被删的连接两集合的最小边)
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define MAXIN (200000)
const int N=1005,M=1e5+5,S=N+M;//虽然维护的是MST但大小还是要M的。。当然可以记录每条树边并循环利用，以后再写吧。。

int n,m,type[M],ff[N],qx[M],qy[M],id[N][N],Ans[M];
char IN[MAXIN],*SS=IN,*TT=IN;
bool ban[M];
struct Edge{
	int fr,to,val;
	Edge() {}
	Edge(int f,int t,int v):fr(f),to(t),val(v) {}
	bool operator <(const Edge &a)const{
		return val<a.val;
	}
}e[M];
namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int pos[S],val[S],son[S][2],fa[S],sk[S];
	bool rev[S];
	inline int Get(int x,int y){
		return val[x]>val[y]?x:y;
	}
	inline void Update(int x){
		pos[x]=Get(x,Get(pos[lson],pos[rson]));//是左右儿子的pos！又一次写错。。
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	inline void Rev(int x){
		std::swap(lson,rson), rev[x]^=1;
	}
	void PushDown(int x){
		if(rev[x]) Rev(lson),Rev(rson),rev[x]=0;
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
	int Find_root(int x)
	{
		Access(x), Splay(x);
		while(lson) x=lson;
		return x;
	}
	void Link(int x){//在合法的情况下Find_root()并不是必须的(不维护子树信息的话?) 
		Make_root(e[x].to), fa[fa[e[x].to]=x+N]=e[x].fr;
		val[x+N]=e[x].val, Update(x+N);
	}
	void Cut(int x){//注意这的编号 
		Access(e[x-N].to), Splay(x), lson=rson=fa[lson]=fa[rson]=0;
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
	return x==ff[x]?x:ff[x]=Get_fa(ff[x]);
}

int main()
{
	n=read(),m=read();int Q=read();
	for(int x,y,i=1; i<=m; ++i) x=read(),y=read(),e[i]=Edge(x,y,read());
	std::sort(e+1,e+1+m);//先排序再编号！
	for(int i=1; i<=m; ++i) id[e[i].fr][e[i].to]=id[e[i].to][e[i].fr]=i;
	for(int i=1; i<=Q; ++i)
	{
		type[i]=read(),qx[i]=read(),qy[i]=read();
		if(type[i]==2) ban[id[qx[i]][qy[i]]]=1;
	}
	for(int i=1; i<=n; ++i) ff[i]=i;
	for(int t,x,y,k=0,i=1; i<=m; ++i)
		if(!ban[t=id[x=e[i].fr][y=e[i].to]] && Get_fa(x)!=Get_fa(y))
		{//不需要记r1,r2 
			ff[ff[x]]=ff[y], Link(t);
			if(++k==n) break;
		}
	int cnt=0;
	for(int i=Q,x,y,t; i; --i)
	{
		Split(x=qx[i],y=qy[i]);
		if(type[i]==1) Ans[++cnt]=val[pos[y]];
		else if(t=id[x][y],val[pos[y]]>e[t].val){
			Cut(pos[y]), Link(t);
		}
	}
	while(cnt) printf("%d\n",Ans[cnt--]);

	return 0;
}
