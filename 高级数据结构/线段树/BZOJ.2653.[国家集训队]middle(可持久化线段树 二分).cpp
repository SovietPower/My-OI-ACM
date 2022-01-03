/*
12848kb	756ms
����λ������$sort$����ʲô����������һ����$x$����$<x$����ȫ���$-1$��$\geq x$�������$1$���ж����к��Ƿ�Ǹ���
����ѯ��$(a,b,c,d)$��ͬ��Ҳ���Զ�����λ��$x$��Ȼ���ԭ���ж�Ӧ�ظ�Ϊ$+1$��$-1$��
��ʱ����$[b,c]$�е����Ǳ�ѡ�ģ���һ����$sum$����Ȼ��������$[a,b-1]$�����ǿ�����һ�������ĺ�׺����������$[c+1,d]$��������һ��������ǰ׺��Ȼ���ж��ܺ��Ƿ�Ǹ���
��Щ�����Խ����߶�����ά����

��Ȼÿ�ζ��ֲ������½��������Ǹտ�ʼʱ��ÿ��$x$��һ������
���������е���������ͬ��ÿ�ζ��ֵ�����$x$���$x+1$ʱ����Ȼ��$x$��ȣ���$+1$���$-1$����ֻ��һ����Ҳ����ÿ������һ����ȣ�ֻ��ı�һ��λ�á�
��������е������ظ�����Ȼ�ܸ��Ӷ�Ҳ������Ӱ�졣
���Կ��Զ�ÿ��$x$���ɳ־û��߶�����ά������͡����ǰ׺��׺�ͼ��ɡ�

���Ӷ�$O(n\log n+q\log^2n)$��

�����ظ�������������$c$��λ������$A_i=x$������ʵ����Ҫȥ�أ���$c$�ò�ͬ���߶������ɡ�������������λ����$x$�Ĺ�ϵ��Σ�һ���ܶ��ֵ���ȷλ�á�
���ȥ�أ�ע�����ÿ��ֵ����Ҫ�����ʼ���ǿ���������`2 2 2`��һֱ�޸�`root[now]`�Ļ�����`-1 -1 1`��ʵ���Ͽ�����`1 1 1` ����ע���߶�����Χ��`1~n`����`1~cnt`����
ȥ����Ȼ���Ż����ֱ߽磬���Ǻ���ûʲôʵ��Ч���������ˣ�= =
*/
#include <cstdio>
#include <cctype>
#include <assert.h>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 50000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=20005;

int root[N];
std::pair<int,int> A[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define S N*19//��������һ��2n�ռ䣬���ǲ�Ҫ���ſ�n(2+logn)= = 
	int tot,Ans,son[S][2],sum[S],pre[S],suf[S];
	#undef S
	inline void Update(int x)
	{
		int l=ls, r=rs;
		sum[x]=sum[l]+sum[r];
		pre[x]=std::max(pre[l],sum[l]+pre[r]);
		suf[x]=std::max(suf[r],sum[r]+suf[l]);
	}
	void Build(int &x,int l,int r)
	{
		x=++tot;
		if(l==r) {sum[x]=pre[x]=suf[x]=1; return;}
		int m=l+r>>1;
		Build(ls,l,m), Build(rs,m+1,r), Update(x);
	}
	void Modify(int &x,int y,int l,int r,int p)
	{
		x=++tot;
		if(l==r) {sum[x]=-1; return;}
		int m=l+r>>1;
		p<=m ? (rs=son[y][1],Modify(ls,son[y][0],l,m,p)) : (ls=son[y][0],Modify(rs,son[y][1],m+1,r,p));
		Update(x);
	}
	int QuerySum(int x,int l,int r,int L,int R)
	{
		if(L<=l && r<=R) return sum[x];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return QuerySum(ls,l,m,L,R)+QuerySum(rs,m+1,r,L,R);
			else return QuerySum(ls,l,m,L,R);
		return QuerySum(rs,m+1,r,L,R);
	}
	void QueryPre(int x,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
		{
			Ans=std::max(pre[x],Ans+sum[x]);
			return;
		}
		int m=l+r>>1;
		if(m<R) QueryPre(rs,m+1,r,L,R);
		if(L<=m) QueryPre(ls,l,m,L,R);//max(QueryPre(lson),QuerySum(lson)+QueryPre(rson)) ����д�ĸ��Ӷ���ɶ��...= = 
	}
	void QuerySuf(int x,int l,int r,int L,int R)
	{
		if(L<=l && r<=R)
		{
			Ans=std::max(suf[x],Ans+sum[x]);
			return;
		}
		int m=l+r>>1;
		if(L<=m) QuerySuf(ls,l,m,L,R);
		if(m<R) QuerySuf(rs,m+1,r,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
bool Check(int x,int n,int a,int b,int c,int d)
{
	int s=T.QuerySum(root[x],1,n,b,c);
	if(s>=0) return 1;
	if(a<b)
	{
		T.Ans=0, T.QuerySuf(root[x],1,n,a,b-1);//������ͬһ������ֱ��Query�ϲ������=v= Ϊ�˳�������= = 
		if((s+=T.Ans)>=0) return 1;
	}
	if(c<d)
	{
		T.Ans=0, T.QueryPre(root[x],1,n,c+1,d);
		if((s+=T.Ans)>=0) return 1;
	}
	return 0;
}

int main()
{
	static int ref[N];
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=std::make_pair(read(),i);
	std::sort(A+1,A+1+n); int cnt=1; ref[1]=A[1].first;
	for(int i=2; i<=n; ++i) if(A[i].first!=A[i-1].first) ref[++cnt]=A[i].first;
	T.Build(root[1],1,n), root[2]=root[1];
//	for(int i=2; i<=n; ++i) T.Modify(root[i],root[i-1],1,n,A[i-1].second);
	for(int i=2,now=2; i<=n; ++i)//A[n]���ù�.
	{
		T.Modify(root[now],root[now],1,n,A[i-1].second);
		if(A[i].first!=A[i-1].first) ++now, root[now]=root[now-1];//root[++now]=root[now-1] ���ǲ�Ҫд���������=-= 
	}
	for(int Q=read(),ans=0,q[4]; Q--; )
	{
		q[0]=(read()+ans)%n+1, q[1]=(read()+ans)%n+1, q[2]=(read()+ans)%n+1, q[3]=(read()+ans)%n+1;
		std::sort(q,q+4);
		int l=1,r=cnt,mid;
		while(l<=r)
			if(Check(mid=l+r>>1,n,q[0],q[1],q[2],q[3])) ans=mid, l=mid+1;
			else r=mid-1;
		printf("%d\n",ans=ref[ans]);
	}

	return 0;
}
