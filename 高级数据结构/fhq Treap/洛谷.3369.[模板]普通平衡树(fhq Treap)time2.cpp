//尴尬 rank没加1 
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5;

struct fhq_Treap
{
	#define lson son[rt][0]
	#define rson son[rt][1]

	int tot,son[N][2],val[N],fix[N],sz[N];
	inline int New_Node(int v){
		sz[++tot]=1, fix[tot]=rand(), val[tot]=v;
		return tot;
	}
	inline void Update(int rt){
		sz[rt]=sz[lson]+sz[rson]+1;
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x^y;
		if(fix[x]<fix[y])
		{
			son[x][1]=Merge(son[x][1],y);
			Update(x);
			return x;
		}
		else
		{
			son[y][0]=Merge(x,son[y][0]);
			Update(y);
			return y;
		}
	}
	void Split(int rt,int v,int &x,int &y)
	{
		if(!rt) x=y=0;
		else{
			if(val[rt]<=v) x=rt,Split(rson,v,rson,y);
			else y=rt,Split(lson,v,x,lson);
			Update(rt);
		}
	}
	int Kth(int k,int rt)
	{
		while(1)
		{
			if(sz[lson]<k && sz[lson]+1==k) return val[rt];
			if(sz[lson]<k) k-=sz[lson]+1,rt=rson;
			else rt=lson;
		}
	}
	int Find(int rt,int w)
	{
		while(son[rt][w]) rt=son[rt][w];
		return val[rt];
	}
}t;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int q=read(),opt,val,x,y,z,root=0;
	while(q--)
	{
		switch(opt=read(),val=read(),opt)
		{
			case 1: t.Split(root,val,x,y),root=t.Merge(t.Merge(x,t.New_Node(val)),y);
					break;
			case 2: t.Split(root,val,x,z),t.Split(x,val-1,x,y),
					y=t.Merge(t.son[y][0],t.son[y][1]),root=t.Merge(t.Merge(x,y),z);
					break;
			case 3: t.Split(root,val-1,x,y),printf("%d\n",t.sz[x]+1),root=t.Merge(x,y);
					break;
			case 4: printf("%d\n",t.Kth(val,root));
					break;
			case 5: t.Split(root,val-1,x,y),printf("%d\n",t.Find(x,1)/*t.Kth(sz[x],x)*/),root=t.Merge(x,y);
					break;
			case 6: t.Split(root,val/*以val分..*/,x,y),printf("%d\n",t.Find(y,0)),root=t.Merge(x,y);
					break;
		}
	}
	return 0;
}
