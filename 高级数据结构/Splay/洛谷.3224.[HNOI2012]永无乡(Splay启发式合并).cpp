/*
查找排名为k的数用平衡树 
合并时用启发式合并，把size小的树上的所有节点插入到size大的树中，每个节点最多需要O(logn)时间 
并查集维护连通关系即可 
O(nlogn*insert time)
据(主席)说按顺序插入能做到均摊O(1)，中序遍历即可有序插入 

1.并查集与平衡树是独立的!不要混用fa!并查集只起判断连通关系的作用 
2.不需要记录root，Splay时到fa[x]=0即可，因为合并是在一棵树中插入 
3.Splay中条件!
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=1e5+5;

int n,m,ff[N],t[N],son[N][2],fa[N],sz[N];

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
void Rotate(int x)
{
	int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
	if(b) son[b][son[b][1]==a]=x;
//	if(!a) printf("Warning:b:%d x:%d\n",b,x);
	fa[x]=b, fa[a]=x, fa[son[x][r]]=a;
	son[a][l]=son[x][r], son[x][r]=a;
	Update(a), Update(x);
}
void Splay(int x)
{
	while(fa[x])//相差不大，反而这样略快 
	{
		int a=fa[x],b=fa[a];
		if(b)//注意是fa[a]!
		{//如果是a，那若这时fa[a]=0，fa[x]会变为0，再经一次Rotate(x)后会改变fa[x]即fa[0]的值 
			if((son[a][1]==x)^(son[b][1]==a)) Rotate(x);
			else Rotate(a);
		}
		Rotate(x);
	}
//	for(int f;f=fa[x];Rotate(x))
//		if(fa[f])
//			((son[f][1]==x)^(son[fa[f]][1]==f))?Rotate(x):Rotate(f);
}
void Insert(int k,int y)
{
	while(son[k][t[y]>t[k]]) k=son[k][t[y]>t[k]];
	fa[y]=k, son[k][t[y]>t[k]]=y, sz[y]=1;
	++sz[k];
//	printf("k:%d fa:%d\n",k,fa[k]);
	Splay(k);
}
int Getf(int x)
{
	return x==ff[x]?x:ff[x]=Getf(ff[x]);
}
void DFS(int tar,int y)
{
	int l=son[y][0],r=son[y][1];//要清空节点信息，所以清空前要记录 
	son[y][0]=son[y][1]=fa[y]=/*sz[y]=*/0;
	if(l) DFS(tar,l);
	Insert(tar,y);
	if(r) DFS(tar,r);
}
void Merge(int x,int y)
{
//	int r1=Getf(x),r2=Getf(y);
	if(x==y) return;
	Splay(x),Splay(y);//保证复杂度 
	if(sz[x]<sz[y]) std::swap(x,y);
	ff[y]=x;
	DFS(x,y);
}
int Rank(int v,int x)
{
	Splay(x);
	if(v>sz[x]) return -1;
	int k=x;
	while(1)
	{
		if(sz[son[k][0]]+1>=v && sz[son[k][0]]<v) return k;
		if(sz[son[k][0]]>=v) k=son[k][0];
		else v-=sz[son[k][0]]+1,k=son[k][1];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3224.in","r",stdin);
#endif

	n=read(),m=read();
	for(int i=1;i<=n;++i) t[i]=read(),ff[i]=i,sz[i]=1;
	int q,a,b;
	char s[5];
	while(m--) a=Getf(read()),b=Getf(read()),Merge(a,b);
	q=read();
	while(q--)
	{
		scanf("%s",s),a=Getf(read()),b=read();
		if(s[0]=='Q') printf("%d\n",Rank(b,a));
		else b=Getf(b),Merge(a,b);
	}

	return 0;
}
