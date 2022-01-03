/*
64956kb	1288ms
$Description$
����һ���и�����ÿ�����е�Ȩ$v_i$��ѡ���ĵ㣬ʹ�ö�������ѡ�������$i,j$����$i$��$j$�����ȣ���$v_i>v_j$��
��������ѡ��ĵ�����ѡ�ĵ㲻������ͨ��
$n\leq 2\times 10^5$��
$Solution$
�������˻�Ϊ���������������һ���(�ϸ�)���������С�
����������ͬ�������ǻ���Ӱ��ġ����������ϵ�LIS����ÿ����xά��һ��״̬���ϣ����ϲ����ӽڵ�ļ��ϣ�Ȼ����val[x]�滻����һ���������������е��ڵľͲ����ˣ���
�����ڵ�״̬���ϵĴ�С���Ǵ��ˡ�
�����滻�����������ҵ��������λ�ã������������Ͳ��ù��ˣ�û�еĻ������ȥ��Ȼ��ݹ��ȥ���ҵ�һ�����ҵ�λ��ɾ����
��Ȼ��ʵ�����߶����ϲ���ô�鷳��ֱ����multiset����ʽ�ϲ��Ϳ����ˡ���
ע���Ǻϲ���������״̬��soҶ�ڵ�sz[]>1Ҳ�ǶԵģ���Ҫֱ����Ϊ0��
*/
#include <cstdio>
#include <cctype>
#include <cassert>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e5+5;

int n,A[N],cnt,ref[N],root[N],Enum,H[N],nxt[N],to[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define S N*19
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,sz[S],son[S][2];
	bool flag;

	#define Update(x) sz[x]=sz[lson]+sz[rson]
	void Delete(int x,int l,int r)
	{
		if(l==r)
		{
			flag=0, --sz[x];//not sz[x]=0!
			return;
		}
		if(sz[lson]) Delete(lson,l,l+r>>1);
		else/*if(sz[rson])*/ Delete(rson,(l+r>>1)+1,r);
		Update(x);
	}
	void Insert(int &x,int l,int r,int p)
	{
		if(!x) x=++tot;
		if(l==r)
		{
			if(!sz[x]) flag=1, ++sz[x];
			return;
		}
		int m=l+r>>1;
		if(p<=m)
		{
			Insert(lson,l,m,p);
			if(flag&&sz[rson]) Delete(rson,m+1,r);//�½���ʱ��϶�ɾ���˰�(û��������) 
		}
		else Insert(rson,m+1,r,p);
		Update(x);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x^y;
		lson=Merge(lson,son[y][0]), rson=Merge(rson,son[y][1]);
		sz[x]+=sz[y], sz[y]=0; return x;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	/*if(u)*/ to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
int Find(int x)
{
	int l=1, r=cnt, mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
void DFS(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		DFS(to[i]), root[x]=T.Merge(root[x],root[to[i]]);
	T.flag=0, T.Insert(root[x],1,cnt,A[x]);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read(), AddEdge(read(),i);

	std::sort(ref+1,ref+1+n), cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i]);

	DFS(1), printf("%d\n",T.sz[root[1]]);

	return 0;
}
