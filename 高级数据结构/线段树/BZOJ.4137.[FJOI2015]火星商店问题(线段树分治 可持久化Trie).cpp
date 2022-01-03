/*
39092kb	3156ms
$Description$
��$n$���̵꣬ÿ���̵궼һֱ���м�ֵ$v_i$����Ʒ�����ֲ�����
1. ��$x$���̵깺���ֵΪ$v$����Ʒ����ʹ����+1��
2. �����б����$[l,r]$���̵��У����$d$���ڣ������죩��������л����ֵ�У���$x$�������ֵ��
$n,q,v_i\leq 10^5$��
$Solution$
ע�����������е����⣬���Կ�BZOJ/������ۡ�
ÿ��ѯ���������������䣬һ��ʱ������$[t-d+1,t]$��������Ʒ����$[L,R]$��
ÿ����Ʒ������һ��ʱ��㷢���ģ����������䣬�Ҿ�Ȼһֱû��ͨ= =������ô�Ϳ��԰�ʱ���߶��������ˡ�
��ÿ��ѯ�ʰ�ʱ������ŵ��߶�����Ӧ�ڵ��ϡ���ô��ÿ���ڵ㴦����ʱ����ڸ������ڵ���Ʒ������Ŵ�С������뵽�ɳ־û�$Trie$��Ϳ��Խ������ڵ��ϵ�ѯ���ˡ�
����������ʼ����Ʒ��������򣬷���ʱֱ�Ӹ���ʱ��㻮�ֵ����������������������
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define BIT 16
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int root[N],Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct OPT
{
	int t,id,v;
	bool operator <(const OPT &x)const
	{
		return id<x.id;
	}
}opt[N],tmp1[N],tmp2[N];
struct Quries
{
	int l,r,tl,tr,v;
}q[N];
struct TRIE
{
	#define S N*(BIT+2)
	int tot,son[S][2],sz[S];
	#undef S
	void Insert(int &rt,int y,int v)
	{
		int x=rt=++tot;
		for(int i=BIT,c; ~i; --i)
			c=v>>i&1, son[x][c^1]=son[y][c^1], x=son[x][c]=++tot, y=son[y][c], sz[x]=sz[y]+1;
	}
	int Query(int x,int y,int v)//y-x
	{
		int res=0;
		for(int i=BIT,c; ~i; --i)
		{
			c=(v>>i&1)^1;
			if(sz[son[y][c]]-sz[son[x][c]]>0) res|=1<<i;
			else c^=1;
			x=son[x][c], y=son[y][c];
		}
		return res;
	}
}Trie;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int A[N];
	std::vector<int> vec[S];
	#undef S
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {vec[rt].push_back(v); return;}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
	}
	inline int Find(int x,int r)
	{
		int l=1,mid,ans=0;
		while(l<=r)
			if(A[mid=l+r>>1]<=x) ans=mid,l=mid+1;
			else r=mid-1;
		return ans;
	}
	void Solve(int L,int R,const std::vector<int> &v)
	{
		Trie.tot=0; int t=0;
		for(int i=L; i<=R; ++i) A[++t]=opt[i].id, Trie.Insert(root[t],root[t-1],opt[i].v);
		for(int i=0,lim=v.size(),id; i<lim; ++i)
		{
			const Quries &q=::q[id=v[i]];
			Ans[id]=std::max(Ans[id],Trie.Query(root[Find(q.l-1,t)],root[Find(q.r,t)],q.v));
		}
	}
	void DFS(int l,int r,int rt,int L,int R)
	{
		if(L>R) return;
		if(vec[rt].size()) Solve(L,R,vec[rt]);
		if(l==r) return;
		int m=l+r>>1,t1=0,t2=0;
		for(int i=L; i<=R; ++i) opt[i].t<=m?(tmp1[t1++]=opt[i],0):(tmp2[t2++]=opt[i],0);
		for(int i=0,p=L; i<t1; opt[p++]=tmp1[i++]);
		for(int i=0,p=L+t1; i<t2; opt[p++]=tmp2[i++]);
		DFS(lson,L,L+t1-1), DFS(rson,L+t1,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<=n; ++i) Trie.Insert(root[i],root[i-1],read());
	int tot=0,cnt=0;
	for(int i=1,l,r,v; i<=m; ++i)
		if(!read()) ++tot, opt[tot]=(OPT){tot,read(),read()};
		else l=read(),r=read(),v=read(),Ans[++cnt]=Trie.Query(root[l-1],root[r],v), q[cnt]=(Quries){l,r,std::max(tot-read()+1,1),tot,v};
	std::sort(opt+1,opt+1+tot);
	for(int i=1; i<=cnt; ++i) if(q[i].tl<=q[i].tr) T.Modify(1,tot,1,q[i].tl,q[i].tr,i);
	T.DFS(1,tot,1,1,tot);
	for(int i=1; i<=cnt; ++i) printf("%d\n",Ans[i]);

	return 0;
}
