#include<cstdio>
#include<cctype>
const int N=1e5+5;

int n,root,size,sz[N],cnt[N],t[N],son[N][2],fa[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

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
	Update(a),Update(x);
}
void Splay(int x,int &k)
{
	while(x!=k)
	{
		int a=fa[x],b=fa[a];
		if(a!=k)
		{
			if((son[a][0]==x)^(son[b][0]==a)) Rotate(x,k);
			else Rotate(a,k);
		}
		Rotate(x,k);
	}
}
void Insert(int v,int k)
{
	int f=0;
	while(k && t[k]!=v) f=k,k=son[k][v>t[k]];//v>t[k]!
	if(k) ++cnt[k];
	else
	{
		k=++size, sz[k]=cnt[k]=1, t[k]=v, fa[k]=f;
		if(f) son[f][v>t[f]]=k;
	}
	Splay(k,root);
}
void Rank(int v,int k)
{
	if(!k) return;//!
	while(son[k][v>t[k]] && t[k]!=v) k=son[k][v>t[k]];
	Splay(k,root);
}
void Delete(int v)
{
	Rank(v,root);//!
//	while(son[k][v>t[k]] && t[k]!=v) k=son[k][v>t[k]];//!
	if(cnt[root]>1) {--cnt[root],--sz[root]; return;}//--sz[k]!
	if(son[root][0] && son[root][1])//两种情况!
	{
		int tmp=root,k=son[root][1];
		root=k;//root=k!
		while(son[k][0]) k=son[k][0];
		sz[k]+=sz[son[tmp][0]],//加sz!
		fa[son[tmp][0]]=k, son[k][0]=son[tmp][0];
		Splay(k,root);//!
	}
	else root=son[root][0]+son[root][1];
	fa[root]=0;//!
//	Splay(k,root);
}
int Get_Rank(int x,int k)
{
	while(1)
	{
		if(sz[son[k][0]]<x && sz[son[k][0]]+cnt[k]>=x) return k;
		if(sz[son[k][0]]<x) x-=sz[son[k][0]]+cnt[k],k=son[k][1];
		else k=son[k][0];
	}
}
int Find(int v,int f)
{
	Rank(v,root);
	if((t[root]>v && !f)||(t[root]<v && f)) return root;
	int k=son[root][f^1];
	while(son[k][f]) k=son[k][f];
	return k;
}

int main()
{
//	freopen("3369.in","r",stdin);

	n=read();
	int opt,x;
	while(n--)
	{
		opt=read(),x=read();
		if(opt==1) Insert(x,root);
		else if(opt==2) Delete(x);
		else if(opt==3) Rank(x,root),printf("%d\n",sz[son[root][0]]+1);
		else if(opt==4) printf("%d\n",t[Get_Rank(x,root)]);
		else if(opt==5) printf("%d\n",t[Find(x,1)]);
		else printf("%d\n",t[Find(x,0)]);
	}

	return 0;
}
