/*
4800kb	5492ms
后缀数组显然不行啊。求LCP还可以哈希+二分，于是考虑用平衡树维护哈希值。
某一节点的哈希值 = hs[lson]*base^{sz[rson]+1} + s[rt]*base^{sz[rson]} + hs[rson] 
好像跑的很慢。。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define lson son[x][0]
#define rson son[x][1]
#define gc() getchar()
typedef unsigned long long ull;
const int N=110000;
const ull base=31;

int root,size,len,sz[N],fa[N],son[N][2],s[N];
char tmp[N];
ull hs[N],pw[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline char Get_opt()
{
	char c=gc();
	while(c!='Q'&&c!='R'&&c!='I') c=gc();
	return c;
}
inline char Get_char()
{
	char c=gc();
	while(!isalpha(c)) c=gc();
	return c;
}
inline void Update(int x)
{
	int rs=rson;
	sz[x]=sz[lson]+sz[rs]+1,
	hs[x]=hs[lson]*pw[sz[rs]+1]+s[x]*pw[sz[rs]]+hs[rs];
}
void Build(int l,int r,int f)
{
	if(l>r) return;
	int m=l+r>>1;
	son[f][m>f]=m, fa[m]=f, s[m]=tmp[m]-'a'+1;
	if(l==r) sz[l]=1, hs[l]=s[m];
	else Build(l,m-1,m), Build(m+1,r,m), Update(m);
}
void Rotate(int x,int &k)
{
	int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
	if(a==k) k=x;
	else son[b][son[b][1]==a]=x;
	fa[a]=x, fa[x]=b, fa[son[x][r]]=a, son[a][l]=son[x][r], son[x][r]=a;
	Update(a);
}
void Splay(int x,int &k)
{
	while(x!=k)
	{
		int a=fa[x];
		if(a!=k) son[a][1]==x^son[fa[a]][1]==a?Rotate(x,k):Rotate(a,k);
		Rotate(x,k);
	}
	Update(x);
}
int Kth(int k,int x)
{
	while(1)
	{
		if(sz[lson]+1==k) return x;
		if(sz[lson]<k) k-=sz[lson]+1, x=rson;
		else x=lson;
	}
}
inline int Split(int l,int r)//Get(l,r)
{
	int x=Kth(l,root),y=Kth(r,root);
	Splay(x,root), Splay(y,son[x][1]);
	return son[y][0];
}
inline bool Check(int x,int y,int len)
{
	ull v1=hs[Split(x,x+len+1)], v2=hs[Split(y,y+len+1)];
	return v1==v2;
}
void Query(int x,int y)
{
	int l=1,r=std::min(size-x-1,size-y-1),mid;
	while(l<=r){
		if(Check(x,y,mid=l+r>>1)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r);
}
void Modify(int p,char c)
{
	int x=Kth(p,root);
	Splay(x,root), s[x]=c-'a'+1, Update(x);
}
void Insert(int p,char c)
{
//	Split(p,p+1);//不能只用Split()！这的p是下标，不一定是编号！
	int p1=Kth(p,root),p2=Kth(p+1,root);
	Splay(p1,root), Splay(p2,son[root][1]);
	int x=++size;
	sz[x]=1, hs[x]=s[x]=c-'a'+1, fa[x]=p2, son[p2][0]=x;
	Update(p2), Update(p1);
}

int main()
{
	pw[0]=1;
	for(int i=1; i<N; ++i) pw[i]=pw[i-1]*31;
	scanf("%s",tmp+2), len=strlen(tmp+2);
	size=len+2, root=len+3>>1, Build(1,size,0);
	int m=read(),x,y; char opt;
	while(m--)
		switch(opt=Get_opt(),opt)
		{
			case 'Q':x=read(),y=read(),Query(x,y); break;
			case 'R':x=read(),Modify(x+1,Get_char()); break;
			case 'I':x=read(),Insert(x+1,Get_char()); break;
		}
	return 0;
}
