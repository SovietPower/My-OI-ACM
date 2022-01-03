/*
3264kb	1380ms
很明显题目是要求去掉一条边后两边子树sz[]的乘积。
LCT维护的是链的信息，那么子树呢?
我们用s_i[x]来记录轻边连向x的子树的和(记作虚儿子)，那么sum[x]更新时就是sum[lson]+sum[rson]+val[x]+s_i[x]。
现在需要s_i[x]，考虑什么时候会影响它。
Splay()影响的只是节点在辅助树Splay中的相对位置，并不会对树中的信息产生影响。
Access()需要更改右儿子，即加上一个虚儿子加上一个实儿子，对应更新即可，如果只需要维护sum之类不需要Update()(一加一减)。
Make_root()无影响。虽然使整棵树形态都发生了变化，但这一操作并不直接用来获取信息。
Split()不需要考虑(仅是调用函数)。
Find_root()无影响。 
Link()后y多了一个虚儿子，那么sum[y],s_i[y]加上x。这一步之前要将y旋到根(Access(y),Splay(y))，否则y以上的部分不会更新。
Cut()无影响。虽然少了个儿子，但这一操作不会用来直接获取信息，下次获取信息时会更新，不会影响正确性。
这样答案就是x,y两边s_i+1的乘积(分离出路径后实的就是x->y了，再加上自己)，或是(y为根时)sz[x]*(sz[y]-sz[x]) 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],sz[N],sz_i[N],sk[N];
	bool tag[N];
	inline void Update(int x){
		sz[x]=sz[lson]+sz[rson]+1+sz_i[x];
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
		{
			Splay(x);
			sz_i[x]+=sz[rson], sz_i[x]-=sz[rson=pre];
//			Update(x);
		}
	}
	void Make_root(int x){
		Access(x), Splay(x), Rev(x);
	}
	void Split(int x,int  y){
		Make_root(x), Access(y), Splay(y);
	}
	void Link(int x,int y){
		Split(x,y), sz_i[fa[x]=y]+=sz[x], Update(y);//更新！
	}
	long long Query(int x,int y){
		Split(x,y); return 1ll*(sz_i[x]+1)*(sz_i[y]+1);//1ll*sz[x]*(sz[y]-sz[x]);
	}
}

int main()
{
	int n=read(),q=read(),x,y; char opt[3];
	for(int i=1; i<=n; ++i) LCT::sz[i]=1;
	while(q--)
	{
		scanf("%s",opt),x=read(),y=read();
		if(opt[0]=='A') LCT::Link(x,y);
		else printf("%lld\n",LCT::Query(x,y));
	}
	return 0;
}
