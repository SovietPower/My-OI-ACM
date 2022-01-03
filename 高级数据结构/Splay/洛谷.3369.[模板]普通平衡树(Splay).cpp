#include<cstdio>
#include<cctype>
using namespace std;
const int N=1e5+5,INF=1e9;

int size,root,t[N],sz[N],son[N][2],fa[N],cnt[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
		if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

inline void Update(int rt)
{
	sz[rt]= sz[son[rt][0]]+sz[son[rt][1]]+cnt[rt];
}
void Rotate(int x,int &k)
{
	int a=fa[x],b=fa[a],l=(son[a][1]==x),r=l^1;
	if(a==k) k=x;
	else son[b][son[b][1]==a]=x;
	fa[a]=x, fa[x]=b, fa[son[x][r]]=a,
	son[a][l]=son[x][r], son[x][r]=a;
	Update(a),Update(x);
}
void Splay(int x,int &rt)
{
	int a,b;
	while(x!=rt)
	{
		a=fa[x], b=fa[a];
		if(a!=rt)
		{
			if((son[a][0]==x)^(son[b][0]==a)) Rotate(x,rt);
			else Rotate(a,rt);
		}
		Rotate(x,rt);
	}
}
void Insert(int k,int v)
{
	int f=0;
	while(k && t[k]!=v) f=k, k=son[k][v>t[k]];
	if(k) ++cnt[k];
	else
	{
		k=++size, sz[k]=cnt[k]=1, fa[k]=f, t[k]=v;
		if(f) son[f][v>t[f]]=k;
	}
	Splay(k,root);
}
void Get_Rank(int k,int v)
{
	if(!k) return;
	while(son[k][v>t[k]] && t[k]!=v) k=son[k][v>t[k]];
	Splay(k,root);
}
int Rank(int k,int x)
{
//	++x;//¼ÓÁËÉÚ±øÔªËØ 
	//if(sz[k]<x) return 0;
	while(1)
	{
		if(sz[son[k][0]]<x && sz[son[k][0]]+cnt[k]>=x) return k;
		if(sz[son[k][0]]<x) x-=sz[son[k][0]]+cnt[k],k=son[k][1];
		else k=son[k][0];
	}
}
int Find(int v,int f)
{
	Get_Rank(root,v);
	if((t[root]>v && f)||(t[root]<v && !f)) return root;
	int k=son[root][f];f^=1;
	while(son[k][f]) k=son[k][f];
	return k;
}
void Delete(int k,int v)
{
	Get_Rank(root,v);
	if(cnt[root]>1){--cnt[root],--sz[root];return;}
	int x=root;
	if(son[root][0] && son[root][1])
	{
		int k=son[root][1];root=k;
		while(son[k][0]) k=son[k][0];
		sz[k]+=sz[son[x][0]], fa[son[x][0]]=k, son[k][0]=son[x][0];
		Splay(k,root);
	}
	else
		root=son[root][0]+son[root][1];
	fa[root]=0;
}

int main()
{
//	freopen("testdata.in","r",stdin);

	int n=read(),opt,x;
//	Insert(root,-INF),Insert(root,INF);
	while(n--)
	{
		opt=read(),x=read();
		if(opt==1) Insert(root,x);
		else if(opt==2) Delete(root,x);
		else if(opt==3) Get_Rank(root,x), printf("%d\n",sz[son[root][0]]+1);
		else if(opt==4) printf("%d\n",t[Rank(root,x)]);
		else if(opt==5) printf("%d\n",t[Find(x,0)]);
		else printf("%d\n",t[Find(x,1)]);
	}

	return 0;
}
