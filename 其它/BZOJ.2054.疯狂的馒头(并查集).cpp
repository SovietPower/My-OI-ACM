/*
18400kb	2520ms
并查集就是确定下一个未染色位置的，直接跳到那个位置染。然而我越想越麻烦=-= 以为有线性的，发现还是要并查集。。
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=1e6+5;

int fa[N],col[N];
char OUT[N*10],*O=OUT;

inline int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
inline void write(int x)
{
	static char buf[10];
	if(x)
	{
		int t=0;
		while(x) buf[++t]=x%10+48, x/=10;
		while(t) *O++=buf[t--];
	}
	else *O++='0';
}

int main()
{
	int n,m,p,q; scanf("%d%d%d%d",&n,&m,&p,&q);
	for(int i=1; i<=n; ++i) fa[i]=i;
	fa[n+1]=n+1;
	for(int i=m; i; --i)
	{
		int l=(i*p+q)%n+1,r=(i*q+p)%n+1; l>r&&(std::swap(l,r),0);
		for(int j=Find(l),ed=Find(r+1); j<=r; j=Find(j+1)) col[j]=i, fa[j]=ed;
	}
	for(int i=1; i<=n; ++i) write(col[i]), *O++='\n';
	fwrite(OUT,1,O-OUT,stdout);

	return 0;
}
