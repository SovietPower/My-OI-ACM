//利用先前的根节点建树 想一下不难写。
#include <cstdio>
#include <cctype>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e6+5,MAXIN=2e6;

int n,q,root[N],A[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Seg_Tree
{
	#define lson son[x][0]
	#define rson son[x][1]

	int tot,val[N*21],son[N*21][2];
	void Build(int &x,int l,int r)
	{
		x=++tot;
		if(l==r) val[x]=A[l];
		else{
			int m=l+r>>1;
			Build(lson,l,m), Build(rson,m+1,r);
		}
	}
	void Modify(int x,int &y,int l,int r,int p,int v)
	{
		y=++tot;
		if(l==r) val[y]=v;
		else{
			int m=l+r>>1;
			if(p<=m) son[y][1]=rson, Modify(lson,son[y][0],l,m,p,v);
			else son[y][0]=lson, Modify(rson,son[y][1],m+1,r,p,v);
		}
	}
	int Query(int x,int l,int r,int p)
	{
		if(l==r) return val[x];
		if(p<=(l+r>>1)) return Query(lson,l,l+r>>1,p);
		return Query(rson,(l+r>>1)+1,r,p);
	}
}t;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	n=read(),q=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	t.Build(root[0],1,n);
	for(int opt,ver,p,i=1; i<=q; ++i)
	{
		ver=read(), opt=read(), p=read();
		if(opt==1) t.Modify(root[ver],root[i],1,n,p,read());
		else root[i]=root[ver], printf("%d\n",t.Query(root[i],1,n,p));
	}
	return 0;
}
