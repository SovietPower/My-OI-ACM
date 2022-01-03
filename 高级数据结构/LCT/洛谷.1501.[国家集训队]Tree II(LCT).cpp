//标记下放同线段树 注意51061^2 > 2147483647，要开unsigned int 
//*sz[]别忘了。。
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod (51061)
typedef unsigned int uint;
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
	#define ADD(x,v) (x)+=(v), (x)%=mod//直接这样最快 
//	#define ADD(x,v) (x)+=(v), (x)>=mod?(x)-=mod:0
//	#define ADD(x,v) (x)+=(v); if((x)>=mod) (x)-=mod//比上一行快一点 

	int son[N][2],fa[N],sk[N],sz[N];
	uint val[N],sum[N],m_tag[N],a_tag[N];
	bool r_tag[N];
	inline void Update(int x){
		sz[x]=sz[lson]+sz[rson]+1;
		sum[x]=(sum[lson]+sum[rson]+val[x])%mod;
	}
	inline void Rev(int x){
		std::swap(lson,rson), r_tag[x]^=1;
	}
	inline void Mult(int x,uint v){
		(sum[x]*=v)%=mod, (val[x]*=v)%=mod, (m_tag[x]*=v)%=mod, (a_tag[x]*=v)%=mod;
	}
	inline void Add(int x,uint v){
//		sum[x]+=v*sz[x]%mod, sum[x]>=mod?sum[x]-=mod:0, val[x]+=v, val[x]>=mod?val[x]-=mod:0, a_tag[x]+=v, a_tag[x]>=mod?a_tag[x]-=mod:0;
//		ADD(sum[x],v*sz[x]%mod/*2.3 ADD这要取模！*/); ADD(val[x],v); ADD(a_tag[x],v);
		ADD(sum[x],v*sz[x]); ADD(val[x],v); ADD(a_tag[x],v);
	}
	void PushDown(int x){
		if(m_tag[x]!=1) Mult(lson,m_tag[x]),Mult(rson,m_tag[x]),m_tag[x]=1;
		if(a_tag[x]) Add(lson,a_tag[x]),Add(rson,a_tag[x]),a_tag[x]=0;
		if(r_tag[x]) Rev(lson),Rev(rson),r_tag[x]=0;
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
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
		int t=1,a=x,b; sk[1]=x;
		while(n_root(a)) sk[++t]=a=fa[a];
		while(t) PushDown(sk[t--]);
		while(n_root(x))
		{
			a=fa[x],b=fa[a];
			if(n_root(a)) Rotate(son[a][1]==x^son[b][1]==a?x:a);
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
//	int Find_root(int x){
//		Access(x), Splay(x);
//		while(lson) x=lson;
//		return x;
//	}
	void Link(int x,int y){
		Make_root(x), fa[x]=y;
	}
	void Cut(int x,int y){
		Split(x,y), fa[x]=son[y][0]=0, Update(y);
//		Make_root(x);
//		if(Find_root(y)==x&&fa[x]==y&&!rson)
//			fa[x]=son[y][0]=0, Update(y);
	}
}

int main()
{
	int n=read(),q=read();
	for(int i=1; i<=n; ++i) LCT::sz[i]=LCT::sum[i]=LCT::val[i]=LCT::m_tag[i]=1;
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),LCT::Link(u,v);
	int u,v,c,d; char opt[3];
	while(q--)
	{
		scanf("%s",opt),u=read(),v=read();
		if(opt[0]=='+') c=read(),LCT::Split(u,v),LCT::Add(v,c);
		else if(opt[0]=='-') c=read(),d=read(),LCT::Cut(u,v),LCT::Link(c,d);
		else if(opt[0]=='*') c=read(),LCT::Split(u,v),LCT::Mult(v,c);
		else LCT::Split(u,v),printf("%d\n",LCT::sum[v]);
	}
	return 0;
}
