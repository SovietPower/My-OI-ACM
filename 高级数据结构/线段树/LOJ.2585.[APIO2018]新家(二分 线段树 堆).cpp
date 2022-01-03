/*
BZOJ:55576kb	5916ms	LOJ:35911ms	69728K Luogu:5049ms	88.89MB
首先考虑离线，将询问按时间排序。对于每个在$[l,r]$出现的颜色，拆成在$l$加入和$r+1$删除两个操作，也按时间排序。
对于询问$(x,t)$，就是求$t$时刻，离$x$最远的颜色到$x$的距离，也就是从$x$出发往左右至少要走多远才能经过所有颜色。
考虑二分答案。那么就成了，求所有颜色是否都在$[x-mid,x+mid]$中出现过。
对于这种是否出现过/只计算一次的问题，通常是对每种颜色计算从左到右第一个出现的颜色。
对每个位置$i$记$pre_i$，表示$col_i$上次出现的位置。那么$i$是$col_i$颜色中，该区间第一个出现的当且仅当$pre_i<l$。
所以我们对区间求$pre_i<l$的位置个数就是答案了。但这好像要树套树。。于是复杂度就成了$O(n\log^3n)$。。

显然有点想偏。再看我们要求的问题：区间中是否出现过所有颜色。我们不需要求有多少种颜色出现了，只要能找到一种不在区间中出现过的颜色就可以了。
如果一种颜色不在$[l,r]$中出现过，那么它的$pre_i<l$且$i>r$。也就是说我们求$[r+1,n]$中是否存在$pre_i<l$就可以了，即求$pre_i$的最小值。
每种颜色的$pre_i$可以开$k$个$set$维护。
因为同一个位置可以有多种颜色，每个位置的$pre_i$会有很多且可能相同。所以对于每个位置还要用一个$multiset$或堆来维护$\min\{pre_i\}$并支持删除。
这样就OK啦，复杂度$O(n\log^2n)$。

再考虑一下二分能否直接在线段树上二分。实际上是可以的。
[orz kcz](https://loj.ac/article/523)。
二分一个$mid$，如果$Ans\geq mid$，则$(x-mid,x+mid)$中不含所有颜色，即$[x+mid,n]$中最小的前驱$mn$满足$mn\leq x-mid$。
我们实际是要求一个最大的$i$，使得$[i,n]$中最小的前驱$mn$，仍满足$mn+i\leq 2x$（$i$越大则$mn$越大，越容易不满足条件）。此时答案就是$\min\{i-x,\ x-\min\{pre_i\}\}$（一个是右端点一个是左端点）。
怎么在线段树上求最大的$i$呢。
先判一下无解情况。
假设现在是在线段树的$[l,r]$区间：
若$x$落在$[mid+1,r]$区间，则$i$也一定落在$[mid+1,r]$区间。
若$x$落在$[l,mid]$区间，则要判断一下$i$能否落在$[mid+1,r]$区间。因为$i$越大$mn$越大，所以只需要判下$i=mid+1$时是否可行就行了。
这样就一个$\log$啦。

注意求的$\min$是$[i,n]$的，如果递归到$[l,mid]$要与右区间取$\min$。
另外线段树上的节点以及$mn$是离散化后的值域，比较的时候用$ref[mid]$（实际值）与$x$比较。
*/
#include <set>
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define INF 1000000000
typedef long long LL;
const int N=3e5+7;

int n,ref[N];
std::multiset<int> st[N];
char IN[MAXIN],*SS=IN,*TT=IN,OUT[3000000],*O=OUT;
struct Node
{
	int x,type,t;
	bool operator <(const Node &x)const
	{
		return t<x.t;
	}
}A[N<<1];
struct Quries
{
	int x,t,id;
	bool operator <(const Quries &x)const
	{
		return t<x.t;
	}
}q[N];
struct Heap
{
	std::priority_queue<int,std::vector<int>,std::greater<int> > a,b;
//	inline int Top() {return a.top();}
	inline void Insert(int x) {a.push(x);}
	inline void Delete(int x)
	{
		if(a.top()!=x) b.push(x);
		else
		{
			a.pop();
			while(!b.empty()&&a.top()==b.top()) a.pop(),b.pop();
		}
	}
}hp[N];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int mn[S];
	#undef S
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	void Init(const int n)
	{
		for(int i=n<<2; i; --i) mn[i]=n;
	}
//	void Build(int l,int r,int rt)
//	{
//		if(l==r) {mn[rt]=hp[l].a.top(); return;}
//		int m=l+r>>1; Build(lson), Build(rson), Update(rt);
//	}
	void Modify(int l,int r,int rt,int p)
	{
		if(l==r) {mn[rt]=hp[l].a.top(); return;}
		int m=l+r>>1;
		p<=m?Modify(lson,p):Modify(rson,p);
		Update(rt);
	}
//	int Query(int l,int r,int rt,int x,int mnv)
//	{
//		if(l==r) return std::min(ref[l]-x,x-std::min(mnv,ref[mn[rt]]));
//		int m=l+r>>1;
//		if(x>ref[m] || ref[m]+1+std::min(mnv,ref[mn[rs]])<=x<<1) return Query(rson,x,mnv);
//		return Query(lson,x,std::min(mnv,ref[mn[rs]]));
//	}
	int Query(int x)
	{
		int l=1,r=n,rt=1,mnv=INF;
		while(l!=r)
		{
			int m=l+r>>1;
			if(x>ref[m]||ref[m]+1+std::min(mnv,ref[mn[rs]])<=x<<1) l=m+1, rt=rs;
			else mnv=std::min(mnv,ref[mn[rs]]), r=m, rt=ls;
		}
		return std::min(ref[l]-x,x-std::min(mnv,ref[mn[rt]]));
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void print(int x)
{
	static char obuf[13];
	if(x<0) x=-x, *O++='-';
	if(x)
	{
		int t=0; while(x) obuf[++t]=x%10+48, x/=10;
		while(t) *O++=obuf[t--];
	}
	else *O++='0';
}
//void print(int x)
//{
//	if(x<0) x=-x, *O++='-';
//	if(x>9) print(x/10);
//	*O++ = x%10+48;
//}
int Discrete(int n)
{
	static std::pair<int,int*> tmp[N<<1];
	for(int i=1; i<=n; ++i) tmp[i]=std::make_pair(A[i].x,&A[i].x);
	std::sort(tmp+1,tmp+1+n);
	int cnt=1; ref[*tmp[1].second=1]=tmp[1].first;
	for(int i=2; i<=n; ++i)
		ref[*tmp[i].second=tmp[i].first==tmp[i-1].first?cnt:++cnt]=tmp[i].first;
	return cnt;
}
void Solve(int p,int col,int &tot)
{
	static int tm[N];
	if(col>0)
	{
		tot+=!tm[col]++;
		std::multiset<int>::iterator it=st[col].lower_bound(p);//话说写set类型的迭代器竟然也对。。
		int nxt=*it, pre=it==st[col].begin()?0:*--it;
		hp[p].Insert(pre), T.Modify(1,n,1,p);
		hp[nxt].Delete(pre), hp[nxt].Insert(p), T.Modify(1,n,1,nxt);//nxt最大也就是n，不会越界 
		st[col].insert(p);
	}
	else
	{
		col=-col, tot-=!--tm[col];
		std::multiset<int>::iterator it=st[col].find(p);
		int pre=it==st[col].begin()?0:(--it,*it++);
		hp[p].Delete(pre), T.Modify(1,n,1,p);
		st[col].erase(it++);
		hp[*it].Delete(p), hp[*it].Insert(pre), T.Modify(1,n,1,*it);
	}
}

int main()
{
	static int Ans[N];

	int n=read(),K=read(),Q=read(),cnt=0;
	for(int i=1,x,type; i<=n; ++i)
		x=read(), type=read(), A[++cnt]=(Node){x,type,read()}, A[++cnt]=(Node){x,-type,read()+1};
	std::sort(A+1,A+1+cnt);
	n=Discrete(cnt), ref[0]=-INF, ref[++n]=INF, ::n=n;

	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+Q);

	for(int i=1; i<=n; ++i) hp[i].Insert(n);
	for(int i=1; i<=K; ++i) hp[n].Insert(0), st[i].insert(n);
//	T.Build(1,n,1); A[cnt+1].t=INF;
	T.Init(n), T.Modify(1,n,1,n), A[cnt+1].t=INF;
	for(int i=1,now=1,tot=0; i<=Q; ++i)
	{
		while(A[now].t<=q[i].t) Solve(A[now].x,A[now].type,tot), ++now;
		Ans[q[i].id]=tot==K?T.Query(q[i].x):-1;
	}
	for(int i=1; i<=Q; ++i) print(Ans[i]), *O++='\n';//printf("%d\n",Ans[i]);
	fwrite(OUT,1,O-OUT,stdout);

	return 0;
}
