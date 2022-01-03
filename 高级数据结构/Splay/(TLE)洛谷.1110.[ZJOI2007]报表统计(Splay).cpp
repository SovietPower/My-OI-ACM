/*
���Կ���������n�Σ�Insert��ÿ����ÿһ��������һ��Ԫ�� 
ֻ�в��룬û��ɾ�������Բ���һ��Ԫ�ض���ѯ��1Ӱ���ֻ�и�Ԫ����ǰ��һ��Ԫ��(ͬ��)����һ�εĿ�ͷԪ�� 
��ֻ��ɾ���ö����Ԫ������һ�ο�ͷԪ�صĲ�ټ�����Ԫ������һ�ο�ͷ�Ĳ�� -> ��¼��ֵ 
����ѯ��2����ֵ��ƽ�����в��룬����Ӱ��ľ�����������ֵ��(��Сֵֻ���ܴ��в���) -> ��¼ֵ 
���Զ���ÿһ��ֻ���¼��ͷ���βԪ�أ�ʣ�µľ��ǲ���ɾ���� 

ѯ��2����������ֵ��ǰ����̣�����ֱ�����ӽڵ㣡
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
	void Update_Min2(int k,int w)
	{
		while(son[k][w]) k=son[k][w];
		Min2=std::min(Min2,std::abs(t[root]-t[k]));
	}
	void Insert(int v,int k,bool opt)
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
		if(!(opt*Min2)) return;
		if(cnt[k]>1) Min2=0;
		if(son[k][0]) Update_Min2(son[k][0],1);
		if(son[k][1]) Update_Min2(son[k][1],0);
	}
	void Get_Rank(int v,int k)
	{
		while(t[k]!=v) k=son[k][v>t[k]];
		Splay(k,root);
	}
	void Delete(int v)
	{
		Get_Rank(v,root);
		int k=root;
		if(cnt[k]>1) --sz[k],--cnt[k];
		else if(son[k][0]*son[k][1])
		{
			int p=son[k][0];root=k=son[k][1];
			while(son[k][0]) k=son[k][0];
			fa[p]=k, son[k][0]=p, sz[k]+=sz[p];
			Splay(k,root);
		}
		else root=son[k][0]|son[k][1];
		fa[root]=0;
	}
	int Query_Min()
	{
		int k=root;
		while(son[k][0]) k=son[k][0];
		return t[k];
	}
}t1,t2;

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
		t1.Delete(std::abs(st[p+1]-ed[p])),
		t1.Insert(std::abs(st[p+1]-v),t1.root,0);
	t1.Insert(std::abs(ed[p]-v),t1.root,0);
	ed[p]=v;
	if(Min2) t2.Insert(v,t2.root,1);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1110.in","r",stdin);
#endif

	n=read(),q=read();
	st[1]=ed[1]=read(),t2.Insert(st[1],t2.root,1);
	for(int i=2;i<=n;++i)
		st[i]=ed[i]=read(),t1.Insert(std::abs(st[i]-st[i-1]),t1.root,0),t2.Insert(st[i],t2.root,1);
	char s[20];int p,v;
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='I') Ins();
		else if(s[4]=='G') printf("%d\n",t1.Query_Min());
		else printf("%d\n",Min2);
	}

	return 0;
}
