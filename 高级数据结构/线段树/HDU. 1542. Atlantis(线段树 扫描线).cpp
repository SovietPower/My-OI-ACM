/*
$Description$
������������
$Solution$
��$x$������ɨ����ɨ����$y$��������߶�������ӡ������䲻Ϊ$0$����λ����͡�
ʵ���е�ϸ������дһ�£�
1. ����ɢ��ǰԭ����Ϊ$Ref$�����߶�������ɢ�����$p$λ��Ҷ�ӵ�ֵΪ$Ref[p+1]-Ref[p]$����������ɢ���ĳ���1�������޸ĵ�ʱ���Ǹ�$[l,r-1]$��ע����$l=r$����������Ҷ����Ҫ��ֵ����ֻ�ܸ��Ǹ������ֵ����
2. ��Ϊ�������ӵı����������θ��ǣ����Բ���ҪPushDown����1��1ֻ�޸��ڶ�Ӧ��$\log$���������ϡ�ֻҪһ�������䱻�ӹ������ǣ�����һ�Σ��������ֵ��Ϊ$Ref[r+1]-Ref[l]$�����迼�������䣻���������ֵΪ$sum[lson]+sum[rson]$��ע������Ҷ�ڵ㣩������ÿ�������޸ĺ�Updateһ�¸����伴�ɡ�
3. ��𰸵�ʱ�򣬲�����$x$����ÿ������$q$�Ĵ𰸼�Ϊ��$(x[q+1]-x[q])*sum[root]$��$sum[root]$Ϊ�߶�����$y$�����ǵ����䳤�Ⱥ͡���ע����$x[qn+1]=x[qn]$�����һ���϶��������𰸣���

���Ӷ�$O(n\log n)$��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e3+5;

double Ref[N];
struct Node
{
	double x1,y1,x2,y2;
}P[N];
struct Operation
{
	double x; int l,r,val;
	bool operator <(const Operation &a)const
	{
		return x<a.x;
	}
}A[N];
struct Segment_Tree
{
	#define S N<<2
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	double sum[S]; int cnt[S];
	#undef S
	
	inline void Update(int rt,int l,int r)
	{
		if(cnt[rt]) sum[rt]=Ref[r+1]-Ref[l];
		else if(l<r) sum[rt]=sum[ls]+sum[rs];
		else sum[rt]=0;
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R)
		{
			cnt[rt]+=v, Update(rt,l,r);
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
		Update(rt,l,r);
	}
	void Build(int l,int r,int rt)
	{
		sum[rt]=cnt[rt]=0;
		if(l==r) return;
		int m=l+r>>1; Build(lson), Build(rson);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int TT=0; ++TT; )
	{
		int n=read(),cnt=0;
		if(!n) break;
		for(int i=1; i<=n; ++i) scanf("%lf%lf%lf%lf",&P[i].x1,&P[i].y1,&P[i].x2,&P[i].y2);
		for(int i=1; i<=n; ++i) Ref[++cnt]=P[i].y1, Ref[++cnt]=P[i].y2;
		std::sort(Ref+1,Ref+1+cnt);
		cnt=std::unique(Ref+1,Ref+1+cnt)-Ref-1;

		int m=0;
		for(int i=1; i<=n; ++i)
		{
			int L=std::lower_bound(Ref+1,Ref+1+cnt,P[i].y1)-Ref;
			int R=std::lower_bound(Ref+1,Ref+1+cnt,P[i].y2)-Ref-1;
			A[++m]=Operation{P[i].x1,L,R,1};
			A[++m]=Operation{P[i].x2,L,R,-1};
		}
		std::sort(A+1,A+1+m);
		
		double ans=0;
		#define S 1,cnt,1
		T.Build(S);
		for(int i=1; i<m; ++i)
		{
			if(A[i].l<=A[i].r) T.Modify(S,A[i].l,A[i].r,A[i].val);
			ans+=T.sum[1]*(A[i+1].x-A[i].x);
		}
		printf("Test case #%d\n",TT);
		printf("Total explored area: %.2f\n\n",ans);
	}
	

	return 0;
}
