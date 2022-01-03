/*
6292kb	1292ms
��һ����ֻ���������������״ֻ̬��һ������ô��nxt[x]��fa[x]���������ͳ���һ��������ÿ���㿪ʼ�Ĵ��������������ĸ��ڵ�ľ��롣
nxt[]�ĸ��ļ���̬�޸����ߣ���LCT���ɡ�
������ѯ��Ҫ�ľ��� Access(x),Splay(x);return sz[x];(sz[lson]+1һ��...)
�޸ľͽ�Cut(x,fa[x])����x�������󿳵������������ˡ�
��Ϊ����Ҫȥ��һ��x->y�������ұ�֤��һ����������Split,Make_root,PushDown...�Ϳ���ʡ�ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,A[N],nxt[N];
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],sz[N],sk[N];
	inline void Update(int x){
		sz[x]=sz[lson]+sz[rson]+1;
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[a]=x, fa[x]=b;
		son[a][l]=son[x][r], son[x][r]=a;
		Update(a);//Update(x);
	}
	void Splay(int x)
	{
		int t=1,a=x,b; sk[1]=x;
		while(n_root(x))
		{
			a=fa[x], b=fa[a];
			if(n_root(a)) Rotate(son[a][1]==x^son[b][1]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
	void Access(int x){
		for(int pre=0; x; x=fa[pre=x])
			Splay(x), rson=pre, Update(x);
	}
	int Query(int x){
		Access(x),Splay(x); return sz[x];
	}
	void Modify(int x,int y){
//		Access(x), fa[x]=son[fa[x]][1]=0;//�������� x��������(������)��������fa[x]�ϵ� 
		Access(x), Splay(x), lson=fa[lson]=0, Update(x);
		if(x+y<=n) fa[x]=x+y;
	}
}

int main()
{
	n=read();
	for(int a,i=1; i<=n; ++i)
	{
		a=read(), LCT::sz[i]=1;
		if(i+a<=n) LCT::fa[i]=i+a;//����Ҫ��ʼʱ��Link()����������߼��� 
	}
	int opt,x,y,m=read();
	while(m--)
	{
		opt=read(),x=read()+1;
		if(opt==1) printf("%d\n",LCT::Query(x));
		else y=read(), LCT::Modify(x,y);
	}
	return 0;
}
