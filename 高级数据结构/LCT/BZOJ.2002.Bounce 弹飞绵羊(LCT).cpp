/*
6292kb	1292ms
从一个点只能往后跳，即后继状态只有一个，那么拿nxt[x]做fa[x]啊！这样就成了一棵树，从每个点开始的答案是它到所在树的根节点的距离。
nxt[]的更改即动态修改树边，用LCT即可。
这样查询需要的就是 Access(x),Splay(x);return sz[x];(sz[lson]+1一样...)
修改就将Cut(x,fa[x])，将x旋到根后砍掉左子树就行了。
因为不需要去查一条x->y的链，且保证是一棵树，所以Split,Make_root,PushDown...就可以省了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,A[N],nxt[N];
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

	int fa[N],son[N][2],sz[N],sk[N];
	inline void Update(int x){
		sz[x]=sz[lson]+sz[rson]+1;
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[a]=x, fa[x]=b;
		son[a][l]=son[x][r], son[x][r]=a;
		Update(a);//Update(x);
	}
	void Splay(int x)
	{
		int t=1,a=x,b; sk[1]=x;
		while(n_root(x))
		{
			a=fa[x], b=fa[a];
			if(n_root(a)) Rotate(son[a][1]==x^son[b][1]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
	void Access(int x){
		for(int pre=0; x; x=fa[pre=x])
			Splay(x), rson=pre, Update(x);
	}
	int Query(int x){
		Access(x),Splay(x); return sz[x];
	}
	void Modify(int x,int y){
//		Access(x), fa[x]=son[fa[x]][1]=0;//这样不对 x的左子树(可能有)还是连在fa[x]上的 
		Access(x), Splay(x), lson=fa[lson]=0, Update(x);
		if(x+y<=n) fa[x]=x+y;
	}
}

int main()
{
	n=read();
	for(int a,i=1; i<=n; ++i)
	{
		a=read(), LCT::sz[i]=1;
		if(i+a<=n) LCT::fa[i]=i+a;//不需要初始时都Link()起来，连轻边即可 
	}
	int opt,x,y,m=read();
	while(m--)
	{
		opt=read(),x=read()+1;
		if(opt==1) printf("%d\n",LCT::Query(x));
		else y=read(), LCT::Modify(x,y);
	}
	return 0;
}
