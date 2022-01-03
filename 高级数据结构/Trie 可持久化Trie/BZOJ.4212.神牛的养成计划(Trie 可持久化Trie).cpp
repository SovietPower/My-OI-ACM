/*
439336kb	2988ms
考虑能够匹配$s1$这一前缀的串有哪些性质。对所有串排序，能发现可以匹配$s1$的是一段区间，可以建一棵$Trie$求出来，设为$[l,r]$。
~~同理匹配$s2$这一后缀的也是一段区间，就可以二维数点了。~~
然后要求的就是$[l,r]$中的串匹配$s2$的有多少个。把所有串`reverse`，建一棵可持久化$Trie$，在上面匹配就可以了。
排序的时候可以不用`sort`，直接在第一棵$Trie$上DFS即可，虽然省个$\log$但这题$n$才$2000$，那个不用边表还有$26$的常数=-=。所以直接`sort`比较的时候暴力一位一位比好了。参考了下$clover\_hxy$的写法。
复杂度$O(26n)$。排序复杂度最坏$O(n|s_i|\log n)$然而根本到不了。
如果不强制在线，直接离线暴力对集合求交复杂度是线性的吧？
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 1000000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e6+5,M=2005;

int A[N],L[M],R[M],id[M],root[M];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	int tot,son[N][26],L[N],R[N];
	void Insert(int *s,int *ed,int id)
	{
		for(int x=0; s!=ed; ++s)
		{
			x=son[x][*s]?son[x][*s]:(L[++tot]=N,son[x][*s]=tot);
			L[x]=std::min(L[x],id), R[x]=std::max(R[x],id);
		}
	}
	void Query(int *s,int *ed,int &l,int &r)
	{
		int x=0;
		for(; s!=ed; ++s)
			if(son[x][*s]) x=son[x][*s];
			else {l=-1; return;}
		l=L[x], r=R[x];
	}
}T1;
struct Trie2
{
	int tot,son[N][26],sz[N];
	void Insert(int *s,int *ed,int &rt,int y)//reverse
	{
		for(int x=rt=++tot; s!=ed; --s)
		{
			memcpy(son[x],son[y],sizeof son[y]);
			x=son[x][*s]=++tot, y=son[y][*s], sz[x]=sz[y]+1;
		}
	}
	int Query(int *s,int *ed,int x,int y)//y-x
	{
		for(; s!=ed; --s)
			if(sz[son[y][*s]]-sz[son[x][*s]]>0) x=son[x][*s], y=son[y][*s];
			else return 0;
		return sz[y]-sz[x];
	}
}T2;


inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline bool cmp(int a,int b)
{
	int p1=L[a],p2=L[b],l=std::min(R[a]-p1,R[b]-p2);
	for(int i=0; i<=l; ++i) if(A[p1+i]!=A[p2+i]) return A[p1+i]<A[p2+i];
	return R[a]-p1<R[b]-p2;
}

int main()
{
	int n=read(),tot=0;
	for(int i=1; i<=n; ++i)
	{
		L[i]=tot+1;
		register char c; while(!isalpha(c=gc()));
		for(; isalpha(c); A[++tot]=c-97,c=gc());
		R[i]=tot, id[i]=i;
	}
	std::sort(id+1,id+1+n,cmp);
	for(int i=1; i<=n; ++i) T1.Insert(A+L[id[i]],A+R[id[i]]+1,i);
	for(int i=1; i<=n; ++i) T2.Insert(A+R[id[i]],A+L[id[i]]-1,root[i],root[i-1]);
	for(int Q=read(),ans=0; Q--; )
	{
		register char c; while(!isalpha(c=gc()));
		int cnt=0;
		for(; isalpha(c); A[++cnt]=(c-97+ans)%26,c=gc());
		int tmp=cnt; while(!isalpha(c=gc()));
		for(; isalpha(c); A[++cnt]=(c-97+ans)%26,c=gc());
		int l,r; T1.Query(A+1,A+tmp+1,l,r);
		if(l!=-1) printf("%d\n",ans=T2.Query(A+cnt,A+tmp,root[l-1],root[r]));
		else printf("%d\n",ans=0);
	}
	return 0;
}
