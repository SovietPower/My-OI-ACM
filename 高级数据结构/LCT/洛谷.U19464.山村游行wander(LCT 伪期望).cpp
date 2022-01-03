/*
题意: 森林，动态建边、删边，询问从S开始走到T的期望时间。走位: 每次人会随机地选一条未走过的边走，走到无路可走，再退回。这样直到终点T。走一条边、从一条边退回都花费时间1. 
题目特点是走到一棵子树一定会全走完，且是两遍的值。画个图，可以看出这一过程是: 
从S开始，随机走到通往T的边或S的一棵子树，走S的子树i的期望为 2*p[i]*sz[i](来回走)；
在S->T的路径上，可能会随机走到一棵子树中，期望同样为 2*p[i]*sz[i]。
于是总期望为 Ans = ∑(枚举S的子树i)2*p[i]*sz[i] + ∑(枚举路径上的子树i)2*p[i]*sz[i].
那么这个概率p[i]是多少呢，就是1/2啊。。不同子树间一点影响没有。
所以 Ans = ∑(枚举S的子树i)sz[i] + ∑(枚举路径上的子树)sz[i]. LCT维护子树sz[]就行了。(小数是唬人的)
输出的话，就输出 树的大小-sz_i[T]-1 或是 以T为根的左子树大小(到T的路径确实还有1，但是已经算上S的sz(1)了).
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],sz[N],sz_i[N],sk[N];
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
			if(n_root(a=fa[x])) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
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
	bool pre_Link(int x,int y){
		Make_root(x);//Split(x,y); //已Find_root(y)
		return Find_root(y)==x;
	}
	void Link(int x,int y){
		sz_i[y]+=sz[x], fa[x]=y, Update(y);
	}
	bool pre_Cut(int x,int y){
		Make_root(x);
		return Find_root(y)==x&&fa[x]==y&&!rson;
	}
	void Cut(int x,int y){
		fa[x]=son[y][0]=0, Update(y);
	}
	int Query(int x,int y){//已pre_Link():Make_root(x), Access(y), Splay(y).
		return sz[son[y][0]];//return sz[y]-sz_i[y]-1;
	}
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
	int n=read(),q=read(),opt,x,y;
	while(q--)
	{
		opt=read(),x=read(),y=read();
		if(!opt){
			if(LCT::pre_Link(x,y)) puts("ILLEGAL");
			else LCT::Link(x,y), puts("OK");
		}
		else if(opt==1){
			if(!LCT::pre_Cut(x,y)) puts("ILLEGAL");
			else LCT::Cut(x,y),puts("OK");
		}
		else if(LCT::pre_Link(x,y)) printf("%d.0000\n",LCT::Query(x,y));
		else puts("ILLEGAL");
	}
	return 0;
}
