/*
4044kb	2256ms
求所有点到某个点距离和最短，即求树的重心。考虑如何动态维护。
两棵子树合并后的重心一定在两棵树的重心之间那条链上，所以在合并的时候用启发式合并，每合并一个点检查sz[]大的那棵子树的重心(记为root)最大子树的sz[]*2是否>n；
若>n，则向fa移动一次(先把合并点Splay到根)。重心还一定是在sz[]大的那棵子树中，且移动次数不会超过sz[]小的子树的点数(所以总移动次数不会超过O(n)?)。
复杂度O(nlog^2n).
具体实现。。~~想通了真是特别简单。。~~也就想想简单
先Link，然后从心向右中序遍历(深度大是向右！).
每到一个点判断其右子树和虚树的sz和*2是否>当前根的sz，如果是，则当前点是要找的重心，继续下一个。若sz[x]*2 < sz[root]，那么root就是根了。
可能有多个重心，这些重心应该是连续的一段。因为编号最小，若sz[x]*2==sz[root] && id[x]<id[root]，则更新root继续。
用并查集维护重心。(Find_root()太慢了)
(不需要再算左子树取max，及深度小于它的子树大小，因为既然重心在那边就不会大过另一边，更何况另一边还又插入了一棵子树)
(维护子树最大值找重心不行吧，合并更新好像很麻烦，直接用sz[]就可以找).

为什么一定要Make_root()重心。。突然觉得根本不明白LCT，不知道怎么走的了。唉以后再说吧。。~~先水过去~~
注意用点的sz[]前先Splay()更新！
至于更新重心可以通过缩短左右区间 能到O(nlogn)的方法(还比这个好理解。。)以后再做吧 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

#define lson son[x][0]
#define rson son[x][1]

int n,m,Ans,sz[N],sz_i[N],_fa[N],fa[N],son[N][2],sk[N];
bool tag[N];
inline void Update(int x){
	sz[x]=sz[lson]+sz[rson]+sz_i[x]+1;
}
inline bool n_root(int x){
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
inline void Rev(int x){
	std::swap(lson,rson), tag[x]^=1;
}
inline void PushDown(int x){
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
		a=fa[x];
		if(n_root(a)) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
		Rotate(x);
	}
	Update(x);
}
void Access(int x){
	for(int pre=0; x; x=fa[pre=x])
		Splay(x), sz_i[x]+=sz[rson]-sz[pre], rson=pre;//Update(x);
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
void Link(int x,int y){
	Split(x,y), sz_i[y]+=sz[x], fa[x]=y, Update(y);
}
int Get_fa(int x){
	return x==_fa[x]?x:_fa[x]=Get_fa(_fa[x]);
}
//int Next(int x){//?
//	PushDown(x), x=rson;
//	while(lson) PushDown(x),x=lson;
//	return x;
//}
int q[N],cnt;
void DFS(int x,int lim)
{
	PushDown(x);
	if(lson) DFS(lson,lim);
	if(cnt>lim) return;
	q[++cnt]=x;
	if(cnt>lim) return;
	if(rson) DFS(rson,lim);
}
int Union(int x,int y)
{
	int r1=Get_fa(x),r2=Get_fa(y);
//	int r1=Find_root(x),r2=Find_root(y);
	Splay(r1), Splay(r2);//先Splay更新sz[]！
	if(sz[r1]>sz[r2]||(sz[r1]==sz[r2]&&y>x)) std::swap(x,y),std::swap(r1,r2);//x->y r1->r2
	int lim=sz[r1],res=r2,tot=sz[r2]+sz[r1];
	Link(x,y), Access(x), Splay(r2);
	cnt=0;
	DFS(r2,lim);
	for(int sum,i=1; i<=cnt; ++i)
	{
		Splay(q[i]), sum=sz[son[q[i]][1]]+sz_i[q[i]]+1;
//		if(tot<sum<<1) res=q[i];//不这么写是不是有点问题啊 
//		else if(tot==sum<<1) res=std::min(res,q[i]);
		if(tot<sum<<1||(tot==sum<<1&&q[i]<=res)) res=q[i];
		else break;
	}
	Make_root(res);
	_fa[r1]=_fa[r2]=_fa[res]=res/*更新重心*/;
	return res;
}
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),m=read();
	int res=0,x,y; char opt[5];
	for(int i=1; i<=n; ++i) _fa[i]=i, res^=i, sz[i]=1;
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='A') x=read(),y=read(),res^=Get_fa(x)^Get_fa(y)^Union(x,y);
		else if(opt[0]=='Q') x=read(),printf("%d\n",Get_fa(x));//printf("%d\n",Find_root(x));
		else printf("%d\n",res);
	}
	return 0;
}
