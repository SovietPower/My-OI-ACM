#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=40000,INF=1e8;

int n,size,root,sz[N],cnt[N],t[N],son[N][2],fa[N];

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
	sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+1;
}
void Rotate(int x,int &rt)
{
	int a=fa[x],b=fa[a],l=(son[a][1]==x),r=l^1;
	if(a==rt) rt=x;
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
	while(k && t[k]!=v) f=k,k=son[k][v>t[k]];
//	if(k) ++cnt[k];
	if(k) ;
	else
	{
		k=++size, sz[k]=/*cnt[k]=*/1, t[k]=v, fa[k]=f;
		if(f) son[f][v>t[f]]=k;
	}
	Splay(k,root);
}
void Get_Rank(int k,int v)
{
//	if(!k) return;
	while(son[k][v>t[k]] && t[k]!=v) k=son[k][v>t[k]];
	Splay(k,root);
}
int Find(int v,int f)
{
	Get_Rank(root,v);
	if(t[root]==v||(t[root]<v && !f)||(t[root]>v && f)) return root;
	int k=son[root][f];
	while(son[k][f^1]) k=son[k][f^1];
	return k;
}

int main()
{
	n=read();
	Insert(root,-INF), Insert(root,INF);
	int a=read();long long res=a;
	Insert(root,a);
	for(int i=1;i<n;++i)
	{
		a=read();
		int p=Find(a,0),p2=Find(a,1);
		res+=min(a-t[p],t[p2]-a);
//		printf("%d %d %d delta:%d\n",a,t[p],t[p2],min(a-t[p],t[p2]-a));
		Insert(root,a);
	}
	printf("%lld",res);

	return 0;
}
