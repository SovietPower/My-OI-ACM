/*
五个操作:
1.将某元素置顶。删掉这个数，插入最左 
2.将某元素置底。同样 
3.旋到根后，直接将这个数与前驱/后继交换所有信息 不是左右子节点!
4.5.裸平衡树 
ps:1.用pos[i]表示第i本书在树上对应的节点，会方便很多(虽然复杂的我也不会)。注意比较的是pos，再开个数组 
2.交换信息交换记录有用信息的pos和t即可。注意pos是t值的位置，换的是pos[tx],pos[ty] 
3.pos[v]即v现在的位置，平衡树中正是以下标位置为排序标准的。将v旋到根即Splay(pos[v],root) 
4.找前驱可以直接return Rank(sz[x]-1)，后继同理 
5.删除节点可以利用该节点的排名，将前驱旋到根上，后继旋到son[root][1]，就可以直接删掉这个点 
6.加入两个哨兵节点 操作1.2就会非常容易 

不明白Move中Bottom为什么是找第n和n+1...
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=8e4+5;

int n,m,root,pos[N],t[N],sz[N],son[N][2],fa[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

inline void Update(int rt)
{
	sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+1;
}
void Build(int l,int r,int f)
{
	if(l>r) return;
	int m=l+r>>1;
	fa[m]=f, son[f][m>f]=m, sz[m]=1;
	if(l==r) return;
	Build(l,m-1,m), Build(m+1,r,m);
	Update(m);
}
void Rotate(int x,int &k)
{
	int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
	if(a==k) k=x;
	else son[b][son[b][1]==a]=x;
	fa[x]=b, fa[a]=x, fa[son[x][r]]=a;
	son[a][l]=son[x][r], son[x][r]=a;
	Update(a), Update(x);
}
void Splay(int x,int &k)
{
	while(x!=k)
	{
		int a=fa[x],b=fa[a];
		if(a!=k) (son[a][1]==x^son[b][1]==a)?Rotate(x,k):Rotate(a,k);
		Rotate(x,k);
	}
}
int Rank(int v,int k)
{
	while(1)
	{
		if(sz[son[k][0]]+1==v) return k;
		if(sz[son[k][0]]>=v) k=son[k][0];
		else v-=sz[son[k][0]]+1,k=son[k][1];
	}
}
//void Delete(int v)
//{
//	int k=root;
//	if(son[k][0]&&son[k][1])
//	{
//		int p=son[k][0];root=k=son[k][1];
//		while(son[k][0]) k=son[k][0];
//		fa[p]=k, son[k][0]=p, sz[k]+=sz[p];
//		Splay(k,root);
//	}
//	else root=son[k][0]|son[k][1];
//	fa[root]=0;
//}
void Delete(int k)
{
	int a=Rank(k-1,root),b=Rank(k+1,root);
	Splay(a,root), Splay(b,son[a][1]);
	fa[son[b][0]]=sz[son[b][0]]=0, son[b][0]=0;
	Update(b), Update(a);
}
void Move(int x,int v)
{
	Splay(x,root);
	int rank=sz[son[x][0]]+1;
	Delete(rank);
	int a,b;
	if(v==N) a=Rank(1,root),b=Rank(2,root);
	else if(v==-N) a=Rank(n,root),b=Rank(n+1,root);//n+1 n+2?
//	else a=Rank(rank+v-1,root),b=Rank(rank+v,root);
	Splay(a,root),Splay(b,son[a][1]);
	sz[x]=1, fa[x]=b, son[b][0]=x;
	Update(b), Update(a);
}
void Swap(int x,int y,int w)
{
	while(son[y][w]) y=son[y][w];
	std::swap(t[x],t[y]);
	std::swap(pos[t[x]],pos[t[y]]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2596.in","r",stdin);
#endif

	n=read(),m=read();
	for(int i=2;i<=n+1;++i) t[i]=read(),pos[t[i]]=i;
	Build(1,n+2,0);//Print(1+n>>1),putchar('\n');
	root=3+n>>1;
	char s[10];int v,k,p,x;
	while(m--)
	{
		scanf("%s",s),v=read();
		if(s[0]=='T')
		{
			Move(pos[v],N);
//		WA:	v=pos[v], Splay(v,root), p=root, Delete(v);
//			x=root;
//			while(son[x][0]) x=son[x][0];
//			fa[p]=x, son[p][0]=son[p][1]=0, sz[p]=1;
//			son[x][0]=p, ++sz[x];
//			Splay(x,root);
		}
		else if(s[0]=='B')
		{
			Move(pos[v],-N);
//		WA:	v=pos[v], Splay(v,root), p=root, Delete(v);
//			x=root;
//			while(son[x][1]) x=son[x][1];
//			fa[p]=x, son[p][0]=son[p][1]=0, sz[p]=1;
//			son[x][1]=p, ++sz[x];
//			Splay(x,root);
		}
		else if(s[0]=='I')
		{
//			k=read(), Move(pos[v],k);
			k=read(), Splay(pos[v],root);
			if(k==-1) Swap(root,son[root][0],1);
			else if(k==1) Swap(root,son[root][1],0);
		}
		else if(s[0]=='A') Splay(pos[v],root),printf("%d\n",sz[son[root][0]]-1);
		else printf("%d\n",t[Rank(v+1,root)]);
	}

	return 0;
}
