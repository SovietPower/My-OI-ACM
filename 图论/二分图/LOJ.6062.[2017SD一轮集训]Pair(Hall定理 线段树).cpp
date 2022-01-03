/*
583ms	4140KiB
首先Bi之间的大小关系没用，先对它排序，假设从小到大排 
那么每个Ai所能匹配的Bi就是一个B[]的后缀 
把一个B[]后缀的匹配看做一条边的覆盖，设Xi为Bi被覆盖的次数 
容易想到 对于每个i∈[1,m]都要满足 Xi-i >= 0，即min{Xi-i}>=0 
用线段树维护即可 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=150005;

int n,m,h,A[N],B[N];
struct Seg_Tree
{
	int val[N<<2],tag[N<<2];
	inline void PushUp(int rt)
	{
		val[rt]=std::min(val[rt<<1],val[rt<<1|1]);
	}
	inline void PushDown(int rt)
	{
		tag[rt<<1]+=tag[rt], tag[rt<<1|1]+=tag[rt];
		val[rt<<1]+=tag[rt], val[rt<<1|1]+=tag[rt];
		tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) val[rt]=-l;
		else{
			int m=l+r>>1;
			Build(l,m,rt<<1), Build(m+1,r,rt<<1|1);
			PushUp(rt);
		}
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L>R) return;
		if(L<=l && r<=R)
			tag[rt]+=v, val[rt]+=v;
		else{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			if(L<=m) Modify(l,m,rt<<1,L,R,v);
			if(m<R) Modify(m+1,r,rt<<1|1,L,R,v);
			PushUp(rt);
		}
	}
	int Query_Min(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return val[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::min(Query_Min(l,m,rt<<1,L,R),Query_Min(m+1,r,rt<<1|1,L,R));
			else return Query_Min(l,m,rt<<1,L,R);
		return Query_Min(m+1,r,rt<<1|1,L,R);
	}
}t;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	int l=1,r=m+1,mid;
	while(l<r)
		if(B[mid=l+r>>1]+x>=h) r=mid;
		else l=mid+1;
	return l;
}

int main()
{
	n=read(),m=read(),h=read();
	for(int i=1; i<=m; ++i) B[i]=read();
	std::sort(B+1,B+1+m);
	for(int i=1; i<=n; ++i) A[i]=Find(read());
	int res=0;
	t.Build(1,m,1);
	for(int i=1; i<m; ++i) t.Modify(1,m,1,A[i],m,1);
	for(int i=m; i<=n; ++i)
	{
		t.Modify(1,m,1,A[i],m,1);
		if(t.val[1]>=0) ++res;
		t.Modify(1,m,1,A[i-m+1],m,-1);
	}
	printf("%d",res);

	return 0;
}
