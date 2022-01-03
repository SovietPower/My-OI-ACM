/*
��ÿ��Merge(),Split()ʱ�����Ľڵ㶼����һ��(��ʵ����ϯ��һ��)��ʱ��ռ临�Ӷȶ�ΪO(qlogq)��(Ӧ�ø���Щ ��Ϊrand()?�ڴ���ı�ը����)
�������޸ĵĲ���ʵ�����ǿ���ֱ�Ӹ�ֵ�ģ���Ϊ�Ժ�Ҳ����ȥ�ĵ�ǰ����ֻ��Ҫ��ѯ���޸�ʱ�ԻḴ���½ڵ㡣
��Ȼ����3.4.5.6����ı�ԭ��������Split()��ı�������̬��������Ҫ�½��ڵ㣬�����ڵ㲻��ҪMerge()��
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

	int tot,fix[S],val[S],son[S][2],sz[S];//����Ҫ*50��QAQ 
	inline int New_Node(int v){
		val[++tot]=v, fix[tot]=rand(), sz[tot]=1/*sz[]����ν*/;
		return tot;
	}
	inline void Update(int rt){
		sz[rt]=sz[lson]+sz[rson]+1;
	}
	int Merge(int x,int y)
	{//���Ƴ�һ�úϲ������������ 
		if(!x||!y) return x^y;
		if(fix[x]<fix[y])
		{
			int p=New_Node(val[x]);//����x������ӣ������Ҷ��� 
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
	{//���Ƴ�����������x,y 
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
