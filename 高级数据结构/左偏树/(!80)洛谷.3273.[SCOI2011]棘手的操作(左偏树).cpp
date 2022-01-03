/*
七个操作(用左偏树)(t2表示第二棵子树): 
1.合并:直接合并(需要将一个t2中原有的根节点删掉) 
2.单点加:把这个点从它的堆里删了，加了再插入回去(有负数)(它可能成为这一个堆的根，所以也要从t2中删除再插入) 
3.整个连通块加:根节点打标记(从t2中删除，改数，再插入到t2) 
4.所有节点加:全局标记 
5.输出某个点的值:向上加上所有父节点的值，输出 
6.输出某个点所在连通块的最大值:找到根，输出 
7.输出所有节点的最大值:将所有堆的根节点取出，再维护第二棵子树 

(1)
在要改动子节点要下传父节点标记，像线段树一样 
(2)
左偏树的删除:左偏树不具有平衡树的性质，所以做不到删除权值为某个值的点，但是可以删除指定下标的点 
先合并要删除的点x的左右子树为s，再将左右合并后的子树与fa[x]合并 
合并后新树距离可能会改变，因此要更新fa[x]的距离 
	如果dis[s]+1<dis[fa]，则dis[fa]的距离要改小，如果s是fa的左子树，还要交换左右子树 
因为dis[fa]的距离改了所以要继续往上 
	如果dis[s]+1>dis[fa]，如果s是左子树就可以结束；如果是右子树，若dis[s]<dis[left]，则更新fa的距离，否则还要再交换一次子树，再向上更新 
(3)
单点加/减(主要是减)有可能在根，这会导致树根发生改变 
对于第二棵左偏树，需要维护树根位置以解决操作7 
(4)
注意第二棵树开始时的建树，将所有原节点合并 
(5)
合并两棵子树需将那棵根不是合并后的根节点的子树从第二棵中删掉 
(6)
第二棵树存的是每堆的根节点，所以要对对应堆的根节点进行操作 
(7)
将一个点取出重新插入时记得Init 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() (SS==TT &&(TT=(SS=IN)+fread(IN,1,1<<22,stdin),SS==TT)?EOF:*SS++)
#define gc() getchar()
const int N=3e5+5;

int n,TAG,q[N],root;
//char IN[1<<22],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
struct Leftist_Tree
{
	int val[N],fa[N],son[N][2],tag[N],dis[N];
	void Init(int p){fa[p]=son[p][0]=son[p][1]=0;}
	inline void PushDown(int x)
	{
		if(son[x][0]) val[son[x][0]]+=tag[x],tag[son[x][0]]+=tag[x];
		if(son[x][1]) val[son[x][1]]+=tag[x],tag[son[x][1]]+=tag[x];
		tag[x]=0;
	}
	int	Getf(int p)
	{
		while(fa[p]) p=fa[p];
		return p;
	}
	int Sum(int p)//到根节点路径的标记和 
	{
		int res=0;
		while(p=fa[p]) res+=tag[p];
		return res;
	}
	int Merge(int A,int B)
	{
		if(!A||!B) return A+B;
		if(val[A]<val[B]) std::swap(A,B);
		if(tag[A]) PushDown(A);
		son[A][1]=Merge(son[A][1],B);
		fa[son[A][1]]=A;
		if(dis[son[A][1]]>dis[son[A][0]]) std::swap(son[A][0],son[A][1]);
		dis[A]=dis[son[A][1]]+1;
		return A;
	}
	int Delete(int x)
	{
		if(tag[x]) PushDown(x);
		int f=fa[x],s=Merge(son[x][0],son[x][1]);
		fa[s]=f;
		if(f) son[f][son[f][1]==x]=s;
		while(f)
		{
			if(dis[son[f][0]]<dis[son[f][1]]) std::swap(son[f][0],son[f][1]);
			if(dis[son[f][1]]+1==dis[f]) return root;//根节点没有改变(距离并未发生改变)，直接return原来的根 
			dis[f]=dis[son[f][1]]+1;
//			fa[son[f][1]]=f;
			s=f, f=fa[f];
		}
		return s;//新的根节点 这个不要随便设，初始就是s，因为s可能就是根节点(f=0) 
	}
	int Add_Point(int x,int v)
	{
		int rt=Getf(x);
		if(rt==x)
			if(!(son[x][0]+son[x][1])||v>=0){val[x]+=v;return x;}
			else if(son[x][0]) rt=son[x][0];
			else rt=son[x][1];
		Delete(x);
		val[x]+=v+Sum(x);
		Init(x);
		return Merge(Getf(rt),x);//要合并Getf(rt)!删除后已经更新树了 
	}
	int Build()
	{
		int h=0,t=0,x,y;
		for(int i=1;i<=n;++i) q[t++]=i;
		while(h<t-1)
		{
			x=q[h++],y=q[h++];
			q[t++]=Merge(x,y);
		}
		return q[t-1];//返回第二棵子树的根节点 
	}
}t1,t2;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3273.in","r",stdin);
#endif

	t1.dis[0]=t2.dis[0]=-1;
	n=read();
	for(int i=1;i<=n;++i) t1.val[i]=t2.val[i]=read();
	root=t2.Build();
	int q=read(),x,y,rx,ry,v,tmp;
	char s[5];
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='U')
		{
			x=read(),y=read(),rx=t1.Getf(x),ry=t1.Getf(y);
			if(rx==ry) continue;
			tmp=t1.Merge(rx,ry);
			if(tmp==rx) root=t2.Delete(ry);
			else root=t2.Delete(rx);
		}
		else if(s[0]=='A')
			if(s[1]=='1')
			{
				x=read(),v=read();
				root=t2.Delete(t1.Getf(x));
				ry=t1.Add_Point(x,v);//第一棵子树更新后x所在堆的根节点 
				t2.val[ry]=t1.val[ry];
				t2.Init(ry);
				root=t2.Merge(root,ry);
			}
			else if(s[1]=='2')
			{
				x=read(),v=read();
				root=t2.Delete((rx=t1.Getf(x)));
				t1.val[rx]+=v, t1.tag[rx]+=v;
				t2.val[rx]=t1.val[rx];
				t2.Init(rx);
				root=t2.Merge(root,rx);
			}
			else
				v=read(), TAG+=v;
		else if(s[0]=='F')
			if(s[1]=='1') x=read(), printf("%d\n",t1.val[x]+t1.Sum(x)+TAG);
			else if(s[1]=='2') x=read(), printf("%d\n",t1.val[t1.Getf(x)]+TAG);
			else printf("%d\n",t2.val[root]+TAG);
	}

	return 0;
}
