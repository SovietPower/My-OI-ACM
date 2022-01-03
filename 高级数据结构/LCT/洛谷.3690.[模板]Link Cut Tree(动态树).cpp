#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=3e5+5;

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

	int fa[N],val[N],sum[N],son[N][2],sk[N];
	bool tag[N];
	inline void Update(int x){
		sum[x]=sum[lson]^sum[rson]^val[x];
	}
	inline void Rev(int x){
		std::swap(lson,rson), tag[x]^=1;
	}
	inline void PushDown(int x){
		if(tag[x]) Rev(lson),Rev(rson),tag[x]=0;
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
		Update(a), Update(x);
	}
	void Splay(int x)
	{
		int t=1,a=x,b; sk[1]=x;
		while(n_root(a)) sk[++t]=a=fa[a];
		while(t) PushDown(sk[t--]);
		while(n_root(x))
		{
			a=fa[x], b=fa[a];
			if(n_root(a)) Rotate(son[a][1]==x^son[b][1]==a?x:a);
			Rotate(x);
		}
		Update(x);//还是加上吧 
	}
	void Access(int x){
		for(int pre=0; x; x=fa[pre=x])//pre=x!
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
//		Splay(x);//保证复杂度？
		return x;
	}
//	int Get_fa(int x){
//		while(fa[x]) x=fa[x];
//		return x;
//	}
//	void Link(int x,int y){
//		if(Get_fa(x)!=Get_fa(y)) Make_root(x),fa[x]=y;//Get_fa()有点慢啊 
//	}
	void Link(int x,int y)
	{
		Make_root(x);
		if(Find_root(y)!=x) fa[x]=y;//连的是轻边！不要加rson=y;
	}
	void Cut(int x,int y)
	{
		Make_root(x);
		if(Find_root(y)==x&&fa[x]==y&&!rson)
			fa[x]=son[y][0]=0, Update(y);
//		if(Find_root(y)==x&&fa[y]==x&&!son[y][0])//若Find_root()中把根又转回去了 
//			fa[y]=rson=0, Update(x);
	}
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) LCT::val[i]=read();
	int opt,x,y;
	while(m--)
	{
		opt=read(),x=read(),y=read();
		if(!opt) LCT::Split(x,y), printf("%d\n",LCT::sum[y]);
		else if(opt==1) LCT::Link(x,y);
		else if(opt==2) LCT::Cut(x,y);
		else LCT::Splay(x), LCT::val[x]=y;/*sum[y]^=val[x]^y, val[x]=y*/ //这步在Split()(查询时)的Splay()中 最后还会Update() 
	}
	return 0;
}
