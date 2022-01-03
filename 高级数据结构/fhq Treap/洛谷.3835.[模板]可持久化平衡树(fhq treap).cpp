/*
对每次Merge(),Split()时产生的节点都复制一份(其实和主席树一样)。时间空间复杂度都为O(qlogq)。(应该更大些 因为rand()?内存真的爆炸。。)
对于无修改的操作实际上是可以直接赋值的，因为以后也不会去改当前树，只需要查询；修改时自会复制新节点。
虽然操作3.4.5.6不会改变原树，但是Split()会改变树的形态，所以仍要新建节点，但根节点不需要Merge()。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=5e5+5,S=N*45,INF=0x7fffffff;

int root[N];
namespace fhq_Treap
{
	#define lson son[rt][0]
	#define rson son[rt][1]

	int tot,fix[S],val[S],son[S][2],sz[S];//必须要*50啊QAQ 
	inline int New_Node(int v){
		val[++tot]=v, fix[tot]=rand(), sz[tot]=1/*sz[]无所谓*/;
		return tot;
	}
	inline void Update(int rt){
		sz[rt]=sz[lson]+sz[rson]+1;
	}
	int Merge(int x,int y)
	{//复制出一棵合并后的树并返回 
		if(!x||!y) return x^y;
		if(fix[x]<fix[y])
		{
			int p=New_Node(val[x]);//复制x的左儿子，更新右儿子 
			son[p][0]=son[x][0], son[p][1]=Merge(son[x][1],y), Update(p);
			return p;
		}
		else{
			int p=New_Node(val[y]);
			son[p][1]=son[y][1], son[p][0]=Merge(x,son[y][0]), Update(p);
			return p;
		}
	}
	void Split(int rt,int v,int &x,int &y)
	{//复制出两棵树来给x,y 
		if(!rt) x=y=0;
		else if(val[rt]<=v){
			x=New_Node(val[rt]), son[x][0]=lson, Split(rson,v,son[x][1],y);
			Update(x);
		}
		else{
			y=New_Node(val[rt]), son[y][1]=rson, Split(lson,v,x,son[y][0]);
			Update(y);
		}
	}
	int Kth(int k,int rt)
	{
		while(1)
		{
			if(sz[lson]+1==k) return val[rt];
			if(sz[lson]<k) k-=sz[lson]+1, rt=rson;
			else rt=lson;
		}
	}
	int Find(int x,int w)
	{
		if(!x) return w?INF:-INF;
		while(son[x][w]) x=son[x][w];
		return val[x];
	}
}
using namespace fhq_Treap;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int q=read();
	for(int ver,opt,val,x,y,z,i=1; i<=q; ++i)
	{
		switch(ver=read(),opt=read(),val=read(),opt)
		{
					
			case 1: Split(root[ver],val,x,y),root[i]=Merge(Merge(x,New_Node(val)),y);
					break;
			case 2: Split(root[ver],val,x,z),Split(x,val-1,x,y);
					if(sz[y]) y=Merge(son[y][0],son[y][1]), root[i]=Merge(Merge(x,y),z);
					else root[i]=root[ver];
					break;
			case 3: root[i]=root[ver],Split(root[ver],val-1,x,y),printf("%d\n",sz[x]+1);//,root[i]=Merge(x,y);
					break;
			case 4: root[i]=root[ver],printf("%d\n",Kth(val,root[ver]));
					break;
			case 5: root[i]=root[ver],Split(root[ver],val-1,x,y),printf("%d\n",Find(x,1));//,root[i]=Merge(x,y);
					break;
			case 6: root[i]=root[ver],Split(root[ver],val,x,y),printf("%d\n",Find(y,0));//,root[i]=Merge(x,y);
					break;
		}
	}
	return 0;
}
