/*
��������Ϊk������ƽ���� 
�ϲ�ʱ������ʽ�ϲ�����sizeС�����ϵ����нڵ���뵽size������У�ÿ���ڵ������ҪO(logn)ʱ�� 
���鼯ά����ͨ��ϵ���� 
O(nlogn*insert time)
��(��ϯ)˵��˳�������������̯O(1)�������������������� 

1.���鼯��ƽ�����Ƕ�����!��Ҫ����fa!���鼯ֻ���ж���ͨ��ϵ������ 
2.����Ҫ��¼root��Splayʱ��fa[x]=0���ɣ���Ϊ�ϲ�����һ�����в��� 
3.Splay������!
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
	while(fa[x])//���󣬷��������Կ� 
	{
		int a=fa[x],b=fa[a];
		if(b)//ע����fa[a]!
		{//�����a��������ʱfa[a]=0��fa[x]���Ϊ0���پ�һ��Rotate(x)���ı�fa[x]��fa[0]��ֵ 
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
	int l=son[y][0],r=son[y][1];//Ҫ��սڵ���Ϣ���������ǰҪ��¼ 
	son[y][0]=son[y][1]=fa[y]=/*sz[y]=*/0;
	if(l) DFS(tar,l);
	Insert(tar,y);
	if(r) DFS(tar,r);
}
void Merge(int x,int y)
{
//	int r1=Getf(x),r2=Getf(y);
	if(x==y) return;
	Splay(x),Splay(y);//��֤���Ӷ� 
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
