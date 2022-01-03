/*
操作按左端点排个序 依次进行即可 
不是很懂 为什么不写Build 而在Add时改mp[rt]=p 会WA(too short on line 251..)
找到Reason了。。Modify下界写错 
那么为什么单点修改正确性会被下界影响。。 
又找到Reason了。。数据有0 mmp 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=1e5+5;

int n,m,maxn,pos;
struct Opt
{
	int p,k,v;
	inline bool operator <(const Opt &a)const {return p<a.p;}
}A[N<<1];
struct Seg_Tree
{
	int mx[N<<2],mp[N<<2];
//	std::pair<int,int> mx[N<<2];
	inline void PushUp(int rt)
	{
		if(mx[rt<<1]>=mx[rt<<1|1])
			mx[rt]=mx[rt<<1], mp[rt]=mp[rt<<1];
		else
			mx[rt]=mx[rt<<1|1], mp[rt]=mp[rt<<1|1];
//		mx[rt]=std::max(mx[rt<<1],mx[rt<<1|1]);//No1相等时按第二关键字升序，初始时取反即可 
	}
//	void Build(int l,int r,int rt)
//	{
//		if(l==r) mx[rt]=0, mp[rt]=l;//mx[rt]=std::make_pair(0,-l);
//		else
//		{
//			int m=l+r>>1;
//			Build(l,m,rt<<1), Build(m+1,r,rt<<1|1);
//			PushUp(rt);
//		}
//	}
	void Modify_Add(int l,int r,int rt,int p,int v)
	{
		if(l==r) mx[rt]+=v, mp[rt]=p;
		else
		{
			int m=l+r>>1;
			if(p<=m) Modify_Add(l,m,rt<<1,p,v);
			else Modify_Add(m+1,r,rt<<1|1,p,v);
			PushUp(rt);
		}
	}
}t;
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("2.out","w",stdout);
#endif

	n=read(),m=read();
	int mn=1e5,mx=1;
	for(int i=0;i<m;++i)
	{
		A[i<<1].p=read(), A[i<<1|1].p=read()+1,
		A[i<<1].k= A[i<<1|1].k= read(),
		A[i<<1].v=1, A[i<<1|1].v=-1;
		mn=std::min(A[i<<1].k,mn), mx=std::max(A[i<<1].k,mx);
	}
	std::sort(A,A+(m<<1));
	A[m<<1].p=n+1;
//	t.Build(mn,mx,1);
	int cnt=0;
//	printf("%d %d\n",mn,mx);
	for(int i=1;i<=n;++i)
	{
//		while(A[cnt].p<=i) t.Modify_Add(0,mx,1,A[cnt].k,A[cnt].v),++cnt;
		while(A[cnt].p<=i) t.Modify_Add(mn,mx,1,A[cnt].k,A[cnt].v),++cnt;
//		if(t.mx[1].first) printf("%d\n",-t.mx[1].second);
		if(t.mx[1]) printf("%d\n",t.mp[1]);
		else puts("-1");
	}

	return 0;
}
