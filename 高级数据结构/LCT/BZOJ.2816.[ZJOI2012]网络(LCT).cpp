/*
3364kb	5952ms
对每种颜色维护一个LCT，保存点之间的连接关系。
修改权值A[x]和所有Max[x]都要改；
修改边的颜色先枚举所有颜色，看是否在某种颜色中有边，然后断开。(枚举一遍就行啊 还以为要set什么的存边的颜色)
(条件1直接用数组存233)
修改x的颜色必须先把x旋到根再改！
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5;

int n,m,C,q,A[N],num[N][11];
struct LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],Max[N],sk[N];
	bool tag[N];
	inline void Update(int x){
		Max[x]=std::max(A[x],std::max(Max[lson],Max[rson]));
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
	bool pre_Link(int x,int y){
		Make_root(x);
		return Find_root(y)!=x;
	}
	void Link(int x,int y){
		fa[x]=y;
	}
	bool pre_Cut(int x,int y){
		Make_root(x);
		return Find_root(y)==x&&fa[x]==y&&!rson;
	}
	void Cut(int x,int y){
		fa[x]=son[y][0]=0, Update(y);
	}
	void Modify(int x,int col){//修改颜色 
		Access(x), Splay(x), Update(x);
	}
}t[10];
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(),m=read(),C=read(),q=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int u,v,w,i=1; i<=m; ++i)
		u=read(),v=read(),w=read(),++num[u][w],++num[v][w],t[w].pre_Link(u,v),t[w].Link(u,v);
	int opt,c,x,y,pos;
	while(q--)
	{
		opt=read();
		if(!opt){
			x=read(),A[x]=y=read();
			for(int i=0; i<C; ++i) t[i].Modify(x,y);
		}
		else if(opt==1){
			x=read(),y=read(),c=read(),pos=-1;
			for(int i=0; i<C; ++i)
				if(t[i].pre_Cut(x,y)) {pos=i; break;}
			if(~pos){
				if(pos==c) puts("Success.");//这个要判！
				else if(num[x][c]>=2||num[y][c]>=2) puts("Error 1.");
				else if(!t[c].pre_Link(x,y)) puts("Error 2.");
				else t[c].Link(x,y),t[pos].Cut(x,y),--num[x][pos],--num[y][pos],++num[x][c],++num[y][c],puts("Success.");
			}
			else puts("No such edge.");
		}
		else{
			c=read(),x=read(),y=read();
			if(!t[c].pre_Link(x,y)) t[c].Split(x,y), printf("%d\n",t[c].Max[y]);
			else puts("-1");
		}
	}
	return 0;
}
