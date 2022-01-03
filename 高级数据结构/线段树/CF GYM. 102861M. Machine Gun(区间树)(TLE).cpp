/*
TLE on #5
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
#define mod 1000000007
#define Vec std::vector<Node>
typedef long long LL;
const int N=(1e5+5)*2;//*2

#define De 0
struct Node
{
	int l,r,id;
	bool operator <(const Node &x)const
	{
		return l!=x.l?l<x.l:r<x.r;
	}
	bool operator <=(const Node &x)const
	{
		id<x.id;
	}
	bool operator !=(const Node &x)const
	{
		return id!=x.id;
	}
	void P() {printf("%d~%d %d\n",l,r,id);}
}node[N];
std::vector<int> Ans,Ans2;

//inline bool Cmp(const Node &a,const Node &b)
//{
//	return a.l!=b.l?a.l<b.l:a.r<b.r;
//}

inline void Merge(std::vector<int> &rt,std::vector<int> &a,std::vector<int> &b)
{
	std::vector<int> tmp;
	auto l=a.begin(),le=a.end(),r=b.begin(),re=b.end();
	while(l!=le&&r!=re)
		if(*l<*r) tmp.pb(*l++);
		else if(*l>*r) tmp.pb(*r++);
		else tmp.pb(*l++), r++;
	while(l!=le) tmp.pb(*l++);
	while(r!=re) tmp.pb(*r++);
	int las=0; std::vector<int>().swap(rt);//先用完a,b再清空！
	for(auto i:tmp)
		if(i!=las) rt.pb(i), las=i;
}
struct Segment_Tree
{
	#define S N<<2
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	int son[S][2];
	std::vector<int> vec[S];
	#undef S
	void Insert(int l,int r,int rt,int p,int id)
	{
		if(l==r) {vec[rt].pb(id); return;} 
		int m=l+r>>1;
		p<=m?Insert(lson,p,id):Insert(rson,p,id);
	}
	void Maintain(int l,int r,int rt)
	{
		if(l==r) return;
		int m=l+r>>1;
		Maintain(lson), Maintain(rson), Merge(vec[rt],vec[ls],vec[rs]);
	}
	void Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Merge(Ans,Ans,vec[rt]); return;}
		int m=l+r>>1;
		if(L<=m) Query(lson,L,R);
		if(m<R) Query(rson,L,R);
	}
	#undef ls
	#undef rs
	#undef lson
	#undef rson
}ST;
struct Interval_Tree
{
	#define S N*19//N<<2
	#define ls son[rt][0]
	#define rs son[rt][1]
	int tot,A[N<<1],son[S][2],center[S];
	Vec Sa[S],Sb[S];
	#undef S
	void Build(int &rt,Vec &va,Vec &vb)
	{
		int t=va.size();
		if(!t) {rt=0; return;}
		int cnt=0; !rt&&(rt=++tot);
		for(auto i:va) A[++cnt]=i.l, A[++cnt]=i.r;
		std::nth_element(A+1,A+t,A+1+cnt);//O(n)找中位数 
		int xc=A[t]; center[rt]=xc;
//		if(De)
//		{
//			printf("\nrt:%d\nA:",rt);
//			for(auto i:va) i.P();
//			printf("B:"); for(auto i:vb) i.P();
//			printf("center:%d\n",xc);
//		}
		Vec val,vbl,var,vbr;
		for(auto i:va)
			if(i.r<xc) val.pb(i);
			else if(i.l>xc) var.pb(i);
			else Sa[rt].pb(i);
		for(auto i:vb)
			if(i.r<xc) vbl.pb(i);
			else if(i.l>xc) vbr.pb(i);
			else Sb[rt].pb(i);
		Build(ls,val,vbl), Build(rs,var,vbr);
	}
	#define Update() std::sort(tmp.begin(),tmp.end()), Merge(Ans2,Ans2,tmp)
//	#define Update() rt
	void Query(int rt,int p)
	{
		if(!rt) return;
		std::vector<int> tmp;
		if(p==center[rt])
		{
			for(auto i:Sa[rt]) tmp.pb(i.id);
			Update();
		}
		else if(p<center[rt])
		{
			for(auto i:Sa[rt])
				if(i.l<=p) tmp.pb(i.id); else break;
			Update(), Query(ls,p);
		}
		else
		{
			for(auto i:Sb[rt])
				if(i.r>=p) tmp.pb(i.id); else break;
			Update(), Query(rs,p);
		}
	}
}IT;
struct Array
{
	int cnt;
	LL A[N],B[N],Ref[N];
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
		const int m=n<<1;
		for(int i=1; i<=n; ++i) Ref[(i<<1)-1]=A[i], Ref[i<<1]=B[i];
		std::sort(Ref+1,Ref+1+m);
		cnt=1;
		for(int i=2; i<=m; ++i) if(Ref[i]!=Ref[i-1]) Ref[++cnt]=Ref[i];
		for(int i=1; i<=n; ++i) A[i]=Find(A[i]), B[i]=Find(B[i]);
	}
}A;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool cmpl(const Node &a,const Node &b)
{
	return a.l<b.l;
}
bool cmpr(const Node &a,const Node &b)
{
	return a.r>b.r;
}

int main()
{
	int n=read(),Q=read();
	for(int i=1; i<=n; ++i)
	{
		LL x=read(),y=read();
		A.A[i]=2*y-x, A.B[i]=2*y+x;
	}
	A.Discrete(n);
//ST
	int cnt=A.cnt;
	for(int i=1; i<=n; ++i)
	{
		node[i]=(Node){A.A[i],A.B[i],i};
		ST.Insert(1,cnt,1,A.A[i],i), ST.Insert(1,cnt,1,A.B[i],i);
	}
	ST.Maintain(1,cnt,1);
//IT
	Vec a,b; int root=0;
	for(int i=1; i<=n; ++i) a.pb(node[i]),b.pb(node[i]);
	std::sort(a.begin(),a.end(),cmpl), std::sort(b.begin(),b.end(),cmpr);
	IT.Build(root,a,b);
//Query
	for(int p=0; Q--; )
	{
		LL x=-1-((p+read())%mod),y=(p+read())%mod;
		int L=A.Find(2*y+x),R=A.Find2(2*y-x);
		std::vector<int>().swap(Ans), std::vector<int>().swap(Ans2);
//
		if(L<=R)
		{
			ST.Query(1,cnt,1,L,R), IT.Query(root,L);
//			if(De) {puts("ST Query:"); for(auto a:Ans) printf("%d ",a); De&&pc('\n');}
			std::vector<int> tmp;
			for(auto i:Ans2) if(node[i].l<=L && node[i].r>=R) tmp.pb(i);
//			if(De) {puts("IT Query:"); for(auto a:tmp) printf("%d ",a); De&&pc('\n');}
			Merge(Ans,Ans,tmp);
		}
//
		LL res=0,t=1; int las=-1;
		for(auto a:Ans)
			if(a!=las) res+=a*t%mod, t=t*5782344%mod, las=a;
		printf("%d\n",p=(int)(res%mod));//(int)(res%mod)!=(int)res%mod!
	}

	return 0;
}
