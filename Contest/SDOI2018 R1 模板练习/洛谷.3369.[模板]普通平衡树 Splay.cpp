#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define MAXIN 500000
const int N=1e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
namespace Splay
{
	#define lson son[x][0]
	#define rson son[x][1]

	int root,size,fa[N],son[N][2],sz[N],t[N],cnt[N];
	inline void Update(int x){
		sz[x]=sz[lson]+sz[rson]+cnt[x];
	}
	void Rotate(int x,int &k)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(k==a) k=x;
		else son[b][son[b][1]==a]=x;
		fa[a]=x, fa[x]=b, fa[son[x][r]]=a,
		son[a][l]=son[x][r], son[x][r]=a;
		Update(a);// Update(x);
	}
	void Splay(int x,int &k)
	{
		while(x!=k)
		{
			int a=fa[x],b=fa[a];
			if(a!=k) (son[a][1]==x^son[b][1]==a)?Rotate(x,k):Rotate(a,k);
			Rotate(x,k);
		}
		Update(x);
	}
	void Insert(int v,int k)
	{
		int f=0;
		while(t[k]!=v&&k) f=k,k=son[k][v>t[k]];
		if(k) ++cnt[k];
		else{
			k=++size, sz[k]=cnt[k]=1, t[k]=v, fa[k]=f;
			if(f) son[f][v>t[f]]=k;
		}
		Splay(k,root);
	}
	void Rank(int v,int k)
	{
//		if(!k) return;
		while(t[k]!=v && son[k][v>t[k]]) k=son[k][v>t[k]];
		Splay(k,root);
	}
	void Delete(int v,int k)
	{
		Rank(v,root);
		if(cnt[root]>1) --cnt[root],--sz[root];
		else if(son[root][0]&&son[root][1])
		{
			int ls=son[root][0],k=son[root][1];
			fa[root=k]=0;
			while(son[k][0]) k=son[k][0];
			fa[ls]=k, son[k][0]=ls;// sz[k]+=sz[ls];
			Splay(k,root);
		}
		else root=son[root][0]^son[root][1],fa[root]=0;
	}
	int Get_Rank(int k,int x)
	{
		while(1)
		{
			if(sz[lson]<k && sz[lson]+cnt[x]>=k) return x;
			if(sz[lson]<k) k-=sz[lson]+cnt[x],x=rson;
			else x=lson;
		}
	}
	int Find(int v,int w)
	{
		Rank(v,root);
		if((t[root]>v&&!w)||(t[root]<v&&w)) return root;//!
		int x=son[root][w^1];
		while(son[x][w]) x=son[x][w];
		return x;
	}
}
using namespace Splay;

int main()
{
	int n=read(),opt;
	while(n--)
		switch(opt=read())
		{
			case 1: Insert(read(),root); break;
			case 2: Delete(read(),root); break;
			case 3: Rank(read(),root),printf("%d\n",sz[son[root][0]]+1); break;
			case 4: printf("%d\n",t[Get_Rank(read(),root)]); break;
			case 5: printf("%d\n",t[Find(read(),1)]); break;
			case 6: printf("%d\n",t[Find(read(),0)]); break;
		}
	return 0;
}
