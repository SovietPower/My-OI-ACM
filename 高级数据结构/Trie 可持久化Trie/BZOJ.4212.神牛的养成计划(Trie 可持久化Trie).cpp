/*
439336kb	2988ms
�����ܹ�ƥ��$s1$��һǰ׺�Ĵ�����Щ���ʡ������д������ܷ��ֿ���ƥ��$s1$����һ�����䣬���Խ�һ��$Trie$���������Ϊ$[l,r]$��
~~ͬ��ƥ��$s2$��һ��׺��Ҳ��һ�����䣬�Ϳ��Զ�ά�����ˡ�~~
Ȼ��Ҫ��ľ���$[l,r]$�еĴ�ƥ��$s2$���ж��ٸ��������д�`reverse`����һ�ÿɳ־û�$Trie$��������ƥ��Ϳ����ˡ�
�����ʱ����Բ���`sort`��ֱ���ڵ�һ��$Trie$��DFS���ɣ���Ȼʡ��$\log$������$n$��$2000$���Ǹ����ñ߱���$26$�ĳ���=-=������ֱ��`sort`�Ƚϵ�ʱ����һλһλ�Ⱥ��ˡ��ο�����$clover\_hxy$��д����
���Ӷ�$O(26n)$�������Ӷ��$O(n|s_i|\log n)$Ȼ�����������ˡ�
�����ǿ�����ߣ�ֱ�����߱����Լ����󽻸��Ӷ������Եİɣ�
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
