//×¢Òâ½¨Ê÷ 
#include<cstdio>
#include<algorithm>
const int N=1e5+5;
//using std::swap;

int n,m,root,t[N],sz[N],son[N][2],fa[N];
bool tag[N];

inline void Update(int rt)
{
	sz[rt]=sz[son[rt][0]]+sz[son[rt][1]]+1;
}
inline void Down(int rt)
{
	tag[rt]^=1;
	if(son[rt][0]) tag[son[rt][0]]^=1;
	if(son[rt][1]) tag[son[rt][1]]^=1;
	std::swap(son[rt][0],son[rt][1]);
}
void Rotate(int x,int &k)
{
	int a=fa[x],b=fa[a],l=(son[a][1]==x),r=l^1;
//	if(tag[a]) Down(a);
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
		if(tag[b]) Down(b);
		if(tag[a]) Down(a);
		if(tag[x]) Down(x);
		if(a!=k)
		{
			if((son[a][1]==x)^(son[b][1]==a)) Rotate(x,k);
			else Rotate(a,k);
		}
		Rotate(x,k);
	}
}
void Build(int l,int r,int f)
{
	if(l>r) return;
	int m=l+r>>1;
	fa[m]=f, son[f][m>f]=m, sz[m]=1;
	if(l==r) return;
	Build(l,m-1,m),Build(m+1,r,m);
	Update(m);
}
int Find(int x)
{
	int k=root;
	while(1)
	{
		if(tag[k]) Down(k);//!
//		printf("%d %d\n",x,k);
		if(sz[son[k][0]]+1==x) return k;
		if(sz[son[k][0]]>=x) k=son[k][0];
		else x-=sz[son[k][0]]+1, k=son[k][1];
	}
}
void Reverse(int L,int R)
{
	int l=Find(L),r=Find(R+2);
//	printf("[%d,%d]:[%d,%d]\n",L,R+2,l,r);
	Splay(l,root),Splay(r,son[root][1]);
	tag[son[r][0]]^=1;
}
void Print(int x)
{
	if(tag[x]) Down(x);
	if(son[x][0]) Print(son[x][0]);
	if(x!=1 && x!=n+2) printf("%d ",x-1);
	if(son[x][1]) Print(son[x][1]);
}

int main()
{
	scanf("%d%d",&n,&m);
	Build(1,n+2,0);
	root=n+3>>1;
	int l,r;
	while(m--) scanf("%d%d",&l,&r),Reverse(l,r);
//	Splay(n+3>>1,root);
	Print(root);

	return 0;
}
