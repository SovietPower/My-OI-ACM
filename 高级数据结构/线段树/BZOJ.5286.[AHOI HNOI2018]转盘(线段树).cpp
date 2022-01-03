/*
8152kb	1656ms
如果从$1$开始，把每个时间$t_i$减去$i$，答案取决于$\max\{t_i-i\}$。记取得最大值的位置是$p$，答案是$t_p+1+n-1-p=\max\{t_i-i\}+1+n-1$。
把环拆成链，每次询问就可以$O(n)$求了（滑动窗口）。

考虑怎么维护答案：$\min\limits_{i=1}^n\{\max\limits_{j=i}^{i+n-1}\{t_j-j\}+i\}+n-1$。
放宽一下条件，即$Ans=\min\limits_{i=1}^n\{\max\limits_{j=i}^{2n}\{t_j-j\}+i\}+n-1$，用线段树维护区间$\max\{t_i-i\}$。需要的是个后缀最大值，所以合并的时候考虑一下右区间对左区间的贡献维护$\min$就可以了（同[BZOJ2957]楼房重建，虽然没写过...）。
具体：维护区间$\max\{t_i-i\}$和最小值$ans[rt]$（最小值此时只考虑当前节点右区间对左区间的影响）。合并的时候二分当前右区间的最大值$val$能影响到左区间的哪个位置：如果左区间的某个$mx[rson]\geq val$，该区间后缀最大值的影响就是$mx[rson]$，直接用$ans[rt]$更新一下然后递归右区间；否则右区间的最小值就是$val+mid+1$，递归左区间。
（或者也可以，找到第一个$>val$的位置$p$，然后用$val+p+1$和$p$之前的$ans$更新答案）

另外注意到最后的答案就是拿$[n+1,2n]$的最大值在$[1,n]$中二分得到的，而$[n+1,2n]$的最大值就是$[1,n]$的最大值$-n$。所以只维护$[1,n]$的线段树就可以了，查询的时候用$[1,n]$的最大值$-n$在$[1,n]$二分一下。

复杂度$O(n\log^2n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,INF=1<<30;

int tm[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int ans[S],mx[S];
	#undef S
	int Query(int l,int r,int rt,int val)
	{
		if(l==r) return mx[rt]>val?val+l+1:INF;
		int m=l+r>>1;
		return mx[rs]>val?std::min(ans[rt],Query(rson,val)):Query(lson,val);//找第一个>val的位置 
//		if(l==r) return l+std::max(mx[rt],val);//both are ok...
//		int m=l+r>>1;
//		return mx[rs]>=val?std::min(ans[rt],Query(rson,val)):std::min(val+m+1,Query(lson,val));//考虑val的影响 
	}
	void Update(int l,int r,int rt)
	{
		mx[rt]=std::max(mx[ls],mx[rs]);
		ans[rt]=Query(l,l+r>>1,ls,mx[rs]);
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {/*ans[rt]=tm[l],*/ mx[rt]=tm[l]-l; return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(l,r,rt);
	}
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) {/*ans[rt]=v,*/ mx[rt]=v-l; return;}
		int m=l+r>>1;
		p<=m ? Modify(lson,p,v) : Modify(rson,p,v);
		Update(l,r,rt);
	}
}T;

int main()
{
//	freopen("circle.in","r",stdin);
//	freopen("circle.out","w",stdout);

	const int n=read(),m=read(),P=read();
	for(int i=1; i<=n; ++i) tm[i]=read();
	T.Build(1,n,1);
	int ans; printf("%d\n",ans=T.Query(1,n,1,T.mx[1]-n)+n-1);
	for(int i=1; i<=m; ++i)
	{
		int x=read(),y=read();
		if(P) x^=ans, y^=ans;
		T.Modify(1,n,1,x,y);
		printf("%d\n",ans=T.Query(1,n,1,T.mx[1]-n)+n-1);
	}

	return 0;
}
