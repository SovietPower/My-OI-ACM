/*
TLE on #2
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=1e5+5;
//const LL M1=2e9,M2=3000000000ll,M3=1e9;

std::vector<int> Ans;
struct Segment_Tree_2D
{
	#define S N*170
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	int tot,cntB,son[S][2],p,id,L,R;
	std::vector<int> vec[S];
	#undef S
	void Ins(int &x,int _p,int _id)
	{
		p=_p, id=_id, Insert(x,1,cntB);
	}
	void Insert(int &x,int l,int r)
	{
		if(!x) x=++tot; vec[x].emplace_back(id);
		if(l==r) return;
		int m=l+r>>1; p<=m?Insert(lson):Insert(rson);
	}
	void Qry(int x,int _L,int _R)
	{
		L=_L, R=_R, Query(x,1,cntB);
	}
	void Query(int x,int l,int r)
	{
		if(!x) return;
		if(L<=l && r<=R)
		{
			for(auto a:vec[x]) Ans.emplace_back(a);
			return;
		}
		int m=l+r>>1;
		if(L<=m) Query(lson);
		if(m<R) Query(rson);
	}
	#undef ls
	#undef rs
	#undef lson
	#undef rson
};
struct Segment_Tree_1D
{
	#define S N
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	int tot,cntA,son[S][2],root[S],id,p1,p2,L1,R1,L2,R2;
	Segment_Tree_2D T;
	#undef S
	void Ins(int &x,int _p1,int _p2,int _id)
	{
		p1=_p1, p2=_p2, id=_id, Insert(x,1,cntA);
	}
	void Insert(int &x,int l,int r)
	{
		if(!x) x=++tot; T.Ins(root[x],p2,id);
		if(l==r) return;
		int m=l+r>>1; p1<=m?Insert(lson):Insert(rson);
	}
	void Qry(int x,int _L1,int _R1,int _L2,int _R2)
	{
		if(_L1<=_R1 && _L2<=_R2)
			L1=_L1, R1=_R1, L2=_L2, R2=_R2, Query(x,1,cntA);
	}
	void Query(int x,int l,int r)
	{
		if(!x) return;
//		printf("Query(%d %lld~%lld %lld~%lld %lld~%lld)\n",x,l,r,L1,R1,L2,R2);
		if(L1<=l && r<=R1)
		{
			T.Qry(root[x],L2,R2);
			return;
		}
		int m=l+r>>1;
		if(L1<=m) Query(lson);
		if(m<R1) Query(rson);
	}
}T;
struct Array
{
	int cnt,val[N];
	LL A[N],Ref[N];
	int Find(LL v)
	{
		if(Ref[cnt]<v) return cnt+1;
		int l=1,r=cnt,mid;
		while(l<r)
			if(Ref[mid=l+r>>1]<v) l=mid+1;
			else r=mid;
		return l;
	}
	int Find2(LL v)
	{
		if(Ref[1]>v) return 0;
		int l=1,r=cnt,mid,ans=0;
		while(l<=r)
			if(Ref[mid=l+r>>1]<=v) l=mid+1,ans=mid;
			else r=mid-1;
		return ans;
	}
	void Discrete(const int n)
	{
		for(int i=1; i<=n; ++i) Ref[i]=A[i];
		std::sort(Ref+1,Ref+1+n);
		cnt=1;
		for(int i=2; i<=n; ++i) if(Ref[i]!=Ref[i-1]) Ref[++cnt]=Ref[i];
		for(int i=1; i<=n; ++i) val[i]=Find(A[i]);
	}
}A,B;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
#define De 0
int main()
{
	int n=read(),Q=read();
	int root=0;
	for(int i=1; i<=n; ++i)
	{
		LL x=read(),y=read();
		A.A[i]=x+2*y, B.A[i]=2*y-x;
	}
	A.Discrete(n), B.Discrete(n);
	int cntA=A.cnt,cntB=B.cnt;
	T.cntA=A.cnt, T.T.cntB=B.cnt;
	for(int i=1; i<=n; ++i) T.Ins(root,A.val[i],B.val[i],i);
	for(int p=0; Q--; )
	{
		LL x=-1-((p+read())%mod),y=(p+read())%mod;
//		De&&printf("(%d,%d)\n",x,y);
		int L1=A.Find(2*y+x),R1=cntA,L2=1,R2=B.Find2(2*y-x);
//		De&&printf("%d~%d %d~%d  %d %d\n",L1,R1,L2,R2,2*y+x,2*y-x);
		Ans.clear(), T.Qry(root,L1,R1,L2,R2);
		LL res=0,t=1;
		std::sort(Ans.begin(),Ans.end());
		if(De) for(auto a:Ans) printf("%d ",a); De&&pc('\n');
		for(auto a:Ans) res+=a*t%mod, t=t*5782344%mod;
		p=(int)(res%mod);
		printf("%d\n",p);
	}

	return 0;
}
