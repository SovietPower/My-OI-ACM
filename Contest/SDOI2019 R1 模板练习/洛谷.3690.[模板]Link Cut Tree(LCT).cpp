//520ms	2984KB
//https://www.cnblogs.com/SovietPower/p/8615938.html
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;
struct LCT
{
	#define ls son[x][0]
	#define rs son[x][1]
	int fa[N],son[N][2],sum[N],val[N],sk[N];
	bool rev[N];
	inline void Update(int x)
	{
		sum[x]=sum[ls]^sum[rs]^val[x];
	}
	inline bool n_root(int x)
	{
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	inline void Rev(int x)
	{
		std::swap(ls,rs), rev[x]^=1;
	}
	inline void PushDown(int x)
	{
		if(rev[x]) Rev(ls), Rev(rs), rev[x]=0;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[x]=b, fa[a]=x, son[a][l]=son[x][r], son[x][r]=a;
		Update(a);
	}
	void Splay(int x)
	{
		int t=1,a=x; sk[1]=a;
		while(n_root(a)) sk[++t]=a=fa[a];
		while(t) PushDown(sk[t--]);
		while(n_root(x))
		{
			if(n_root(a=fa[x])) Rotate(son[a][0]==x^son[fa[a]][0]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
	void Access(int x)
	{
		for(int pre=0; x; x=fa[pre=x])
			Splay(x), rs=pre, Update(x);
	}
	void MakeRoot(int x)
	{
		Access(x), Splay(x), Rev(x);
	}
	void Split(int x,int y)
	{
		MakeRoot(x), Access(y), Splay(y);
	}
	int FindRoot(int x)
	{
		Access(x), Splay(x);
		while(ls) x=ls;
		return x;
	}
	void Link(int x,int y)
	{
		MakeRoot(x);
		if(FindRoot(y)!=x) fa[x]=y;
	}
	void Cut(int x,int y)
	{
		MakeRoot(x);
		if(FindRoot(y)==x&&fa[x]==y&&!rs) fa[x]=son[y][0]=0, Update(y);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(),q=read();
	for(int i=1; i<=n; ++i) T.val[i]=read();
	for(int x,y; q--; )
		switch(read())
		{
			case 0: x=read(),y=read(),T.Split(x,y),printf("%d\n",T.sum[y]); break;
			case 1: x=read(),y=read(),T.Link(x,y); break;
			case 2: x=read(),y=read(),T.Cut(x,y); break;
			case 3: T.Splay(x=read()),T.val[x]=read(); break;
		}

	return 0;
}
