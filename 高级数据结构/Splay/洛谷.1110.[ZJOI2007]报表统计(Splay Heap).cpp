/*
对于询问1，直接用带修改的堆维护即可，能不用Splay就不用了 
对于堆的修改，可以将要修改的元素另插入一个堆，当两个堆的堆顶相等时，就都弹出 
对于询问2，需要前驱后继，还是用平衡树 

询问2中相邻两个值是前驱后继！不能直接用子节点！
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
const int N=5e5+5,M=N*3;

int n,q,st[N],ed[N],Min2=1e9;
struct Splay_Tree
{
	int size,root,son[M][2],fa[M],sz[M],cnt[M],t[M];
	inline void Update(int rt)
	{
		sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+cnt[rt];
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
	inline void Update_Min2(int k,int w)
	{
		while(son[k][w]) k=son[k][w];
		Min2=std::min(Min2,std::abs(t[root]-t[k]));
	}
	void Insert(int v,int k)
	{
		int f=0;
		while(t[k]!=v && k) f=k,k=son[k][v>t[k]];
		if(k) ++cnt[k],++sz[k];
		else
		{
			k=++size, sz[k]=cnt[k]=1, t[k]=v, fa[k]=f;
			if(f) son[f][v>t[f]]=k;
		}
		Splay(k,root);
		if(!Min2) return;
		if(cnt[k]>1) Min2=0;
		if(son[k][0]) Update_Min2(son[k][0],1);
		if(son[k][1]) Update_Min2(son[k][1],0);
	}
}t;
struct Heap
{
	int sz,A[M];
	inline int Top()
	{
		return A[1];
	}
	void Push(int x)
	{
		A[++sz]=x;
		int now=sz,nxt=now>>1;
		while(now>1 && A[nxt]>A[now])
			std::swap(A[nxt],A[now]), now=nxt, nxt=now>>1;
	}
	void Pop()
	{
		A[1]=A[sz--];
		int now=1,nxt;
		while(now<<1<=sz)
		{
			nxt=now<<1;
			if(A[nxt]>A[nxt+1] && nxt<sz) ++nxt;
			if(A[nxt]>=A[now]) break;
			std::swap(A[now],A[nxt]);
			now=nxt;
		}
	}
}h1,h2;

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
void Ins()
{
	int p=read(),v=read();
	if(p!=n)
		h2.Push(std::abs(st[p+1]-ed[p])),
		h1.Push(std::abs(st[p+1]-v));
	h1.Push(std::abs(ed[p]-v));
	ed[p]=v;
	if(Min2) t.Insert(v,t.root);
}
int Query_Min1()
{
	while(h1.Top()==h2.Top()) h1.Pop(),h2.Pop();
	return h1.Top();
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1110.in","r",stdin);
#endif

	n=read(),q=read();
	st[1]=ed[1]=read(),t.Insert(st[1],t.root);
	for(int i=2;i<=n;++i)
		st[i]=ed[i]=read(),h1.Push(std::abs(st[i]-st[i-1])),t.Insert(st[i],t.root);
	char s[20];int p,v;
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='I') Ins();
		else if(s[4]=='G') printf("%d\n",Query_Min1());
		else printf("%d\n",Min2);
	}

	return 0;
}
