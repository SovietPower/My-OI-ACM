/*
210300kb	12428ms
����ѯ��$l,r,k$����$t=r-l+1$������ָ������$[k,k+t-1]$����Ȼ$k$��ߵ��˶�Ҫ��$k$��ʼ�������У�$k+t-1$�ұߵ���Ҫ��$k+t-1$�����������С������еıȽ��鷳��
~~Ҳ�Ƚ���Ȼ����~~����һ����$mid\in[k-1,k+t-1]$��ʹ��$mid$��ߵ��˶�������$[k,mid]$�У��ұߵ��˶����ŵ�$[mid+1,k+t-1]$�С����Ҵ��ۺܺ��㣬������Ҫ��һ���Ȳ����еĺͣ��Լ���������˵�����͡�
������������$mid$����Ȼ��$mid$����˵���������$mid-k+1$�����Կ��Զ���+��ϯ����������$\log^2$�ġ�
ע�⵽��������Ǹ�ǰ׺�����Կ���ֱ������ϯ���϶��֡�
��ô���ӶȾ���$O(n\log n)$����
~~Ī����дָ��~~
Ϊɶ�ҵ���ϯ����ô��\_(:�١���)\_ 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define F(l,r) (1ll*((r)-(l)+1)*(l+r)>>1)//n(a1+an)/2... l<=r+1
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int A[N],root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m,
	#define rson rs,m+1,r
	#define lson2 ls,son[y][0],l,m
	#define rson2 rs,son[y][1],m+1,r
	#define S N*21
	int tot,son[S][2],sz[S];
	LL lsum,rsum,sum[S];
	#undef S
	void Insert(int &x,int y,int l,int r,int p)
	{
		sz[x=++tot]=sz[y]+1, sum[x]=sum[y]+p;
		if(l==r) return;
		int m=l+r>>1;
		p<=m?(rs=son[y][1],Insert(lson2,p)):(ls=son[y][0],Insert(rson2,p));
	}
	int Query(int x,int y,int l,int r,int K)//y-x
	{
		if(l==r) return lsum+=sum[y]-sum[x],l;//mid=k-1 -> lsum=sum[now]=0
		int m=l+r>>1,t=sz[son[y][0]]-sz[ls];
		return m-K+1>=t?(rsum+=sum[son[y][1]]-sum[rs],Query(lson2,K)):(lsum+=sum[son[y][0]]-sum[ls],Query(rson2,K+t));
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
	int n=read(),Q=read(),mx=0,mn=N;
	for(int *s=A+1,*ed=A+1+n; s!=ed; ++s) mx=std::max(mx,*s=read()), mn=std::min(mn,*s);
	for(int i=1; i<=n; ++i) T.Insert(root[i],root[i-1],mn,mx,A[i]);
	for(int l,r,ql,qr; Q--; )
	{
		l=read(),r=read(),ql=read(),qr=ql+r-l;
		if(ql<=mn||qr>=mx) printf("%lld\n",std::abs(T.sum[root[r]]-T.sum[root[l-1]]-F(ql,qr)));
		else
		{
			T.lsum=0, T.rsum=0;
			int mid=T.Query(root[l-1],root[r],mn,mx,ql);
			printf("%lld\n",F(ql,mid)-T.lsum+T.rsum-F(mid+1,qr));
		}
	}
	return 0;
}
