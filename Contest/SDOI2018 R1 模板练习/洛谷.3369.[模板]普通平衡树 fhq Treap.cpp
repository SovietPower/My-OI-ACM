#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
namespace fhq_Treap
{
	#define lson son[rt][0]
	#define rson son[rt][1]

	int tot,fa[N],son[N][2],sz[N],val[N],fix[N];
	inline int New_Node(int v){
		fix[++tot]=rand(), val[tot]=v, sz[tot]=1;
		return tot;
	}
	inline void Update(int rt){
		sz[rt]=sz[lson]+sz[rson]+1;
	}
	void Split(int rt,int v,int &x,int &y)
	{
		if(!rt) x=y=0;
		else{
			if(val[rt]<=v) x=rt,Split(rson,v,rson,y);//val[rt] not val[x]..
			else y=rt,Split(lson,v,x,lson);
			Update(rt);
		}
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x^y;
		if(fix[x]<fix[y]){
			son[x][1]=Merge(son[x][1],y), Update(x);
			return x;
		}
		else{
			son[y][0]=Merge(x,son[y][0]), Update(y);
			return y;
		}
	}
	int Rank(int k,int rt)
	{
		while(1)
		{
			if(sz[lson]+1==k) return rt;
			if(sz[lson]<k) k-=sz[lson]+1,rt=rson;
			else rt=lson;
		}
	}
	int Find(int rt,int w)
	{
		while(son[rt][w]) rt=son[rt][w];
		return rt;
	}
}
using namespace fhq_Treap;

int main()
{
	int n=read(),opt,v,x,y,z,root=0;
	while(n--)
		switch(opt=read(),v=read(),opt)
		{
			case 1: Split(root,v,x,y),x=Merge(x,New_Node(v)),root=Merge(x,y);
					break;
			case 2: Split(root,v,x,z),Split(x,v-1,x,y),y=Merge(son[y][0],son[y][1]),root=Merge(Merge(x,y),z);
					break;
			case 3: Split(root,v-1,x,y),printf("%d\n",sz[x]+1),root=Merge(x,y);
					break;
			case 4: printf("%d\n",val[Rank(v,root)]);
					break;
			case 5: Split(root,v-1,x,y),printf("%d\n",val[Find(x,1)]),root=Merge(x,y);
					break;
			case 6: Split(root,v,x,y),printf("%d\n",val[Find(y,0)]),root=Merge(x,y);
					break;
		}
	return 0;
}
