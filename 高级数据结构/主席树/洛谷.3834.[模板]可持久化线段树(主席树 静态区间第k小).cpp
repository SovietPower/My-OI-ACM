//离散化后范围1~cnt不要错 
#include<cstdio>
#include<cctype>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5,MAXIN=2e6;

int n,m,A[N],ref[N],cnt,sum[N*18],tot,son[N*18][2],root[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int Find(int v)
{
	int l=1,r=cnt,m;
	while(l<r)
		if(ref[m=l+r>>1]<v) l=m+1;
		else r=m;
	return l;
}
void Discrete()
{
	std::sort(ref+1,ref+1+n);
	cnt=1;
	for(int i=2;i<=n;++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1;i<=n;++i) A[i]=Find(A[i]);
}
void Build(int x,int &y,int l,int r,int pos)
{
	sum[y=++tot]=sum[x]+1;
	if(l==r) return;
	int m=l+r>>1;
	if(pos<=m) son[y][1]=son[x][1],Build(son[x][0],son[y][0],l,m,pos);
	else son[y][0]=son[x][0],Build(son[x][1],son[y][1],m+1,r,pos);
}
int Query(int x,int y,int l,int r,int k)
{
	if(l==r) return l;
	int m=l+r>>1,tmp=sum[son[y][0]]-sum[son[x][0]];
	if(tmp>=k) return Query(son[x][0],son[y][0],l,m,k);
	else return Query(son[x][1],son[y][1],m+1,r,k-tmp);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("3834.in","r",stdin);
#endif

	n=read(),m=read();
	for(int i=1;i<=n;++i) ref[i]=A[i]=read();
	Discrete();
	for(int i=1;i<=n;++i) Build(root[i-1],root[i],1,cnt,A[i]);
	for(int i=1,l,r,k;i<=m;++i)
		l=read(),r=read(),k=read(),printf("%d\n",ref[Query(root[l-1],root[r],1,cnt,k)]);

	return 0;
}
