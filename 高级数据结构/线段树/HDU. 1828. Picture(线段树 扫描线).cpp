/*
$Description$
��$n$�����Σ�����θ��������γɵ�ͼ�ε��ܳ���$n\leq 1e5$��
$Solution$
ͬ1542����$x,y$����ֱ���ɨ����ɨ��Ȼ���$y,x$����ֱ�����ӣ����ǣ��������1542��ȫһ��������ֻ�е�ǰ���Ǵ���ǡ��Ϊ$1$��λ�ã����Ǻܺ��㡣
ע���ʵ���ǣ�ÿ������Ӽ���ǰ�������򳤶ȱ仯�ľ���ֵ����Ϊһ�����串�Ǵ�����0��1�ʹ�1��0�仯����ʾһ���ߡ�����Ҫɨ���ߵ�ͬһλ�õ������޸ģ������ȼӺ�������ظ�01�仯��
���Ӷ�$O(n\log n)$��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=2e4+5;

int Ref[N];
struct Opt
{
	int p,l,r,v;
	bool operator <(const Opt &a)const
	{
		return p!=a.p?p<a.p: v>a.v ;//!
	}
}qx[N],qy[N];
struct Node
{
	int x1,y1,x2,y2;
}A[N];
struct Segment_Tree
{
	#define S N<<2
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	int cnt[S],sum[S];
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
		memset(sum,0,r<<2), memset(cnt,0,r<<2);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int Solve(Opt *A,int m,int t)
{
	#define S 1,t,1
	T.Build(S);
	int ans=0;
	for(int i=1,las=0; i<=m; ++i)
	{
		if(A[i].l<=A[i].r) T.Modify(S,A[i].l,A[i].r,A[i].v);
//		if(A[i].p!=A[i+1].p) ..;
		ans+=std::abs(T.sum[1]-las), las=T.sum[1];//ע��������ʱ�̶����� 
	}
	return ans;
}

int main()
{	
	for(int n; ~scanf("%d",&n); )
	{
		for(int i=1; i<=n; ++i) A[i]=Node{read(),read(),read(),read()};
		int t=0;
		for(int i=1; i<=n; ++i)
			Ref[++t]=A[i].x1, Ref[++t]=A[i].x2, Ref[++t]=A[i].y1, Ref[++t]=A[i].y2;
		std::sort(Ref+1,Ref+1+t), t=std::unique(Ref+1,Ref+1+t)-Ref-1;

		int m=0;
		for(int i=1; i<=n; ++i)
		{
			int lx=std::lower_bound(Ref+1,Ref+1+t,A[i].x1)-Ref;
			int rx=std::lower_bound(Ref+1,Ref+1+t,A[i].x2)-Ref;
			int ly=std::lower_bound(Ref+1,Ref+1+t,A[i].y1)-Ref;
			int ry=std::lower_bound(Ref+1,Ref+1+t,A[i].y2)-Ref;
			qx[++m]=Opt{lx,ly,ry-1,1}, qx[++m]=Opt{rx,ly,ry-1,-1};
			qy[m-1]=Opt{ly,lx,rx-1,1}, qy[m]=Opt{ry,lx,rx-1,-1};
		}
		std::sort(qx+1,qx+1+m), std::sort(qy+1,qy+1+m);

		int ans=Solve(qx,m,t)+Solve(qy,m,t);
		printf("%d\n",ans);
	}

	return 0;
}
