/*
624ms 9400KB 和另一个差不了多少 
题意:有n个数，将其分为k段，每段的值为这一段的总共数字种类，问最大总值是多少 
DP，用f[i][j]表示当前在i 分成了j份(第j份包括i) 
那枚举前边的断点k，即 
	f[i][j]=max{f[k][j-1]+val(k+1,1)}
val(a,b)表示[a,b]这段区间的价值(数字种数) 
O(n^2*k)
第二维可以滚动数组优化掉，只在最外层枚举即可 
优化求val()的过程 
val是与数的种类数有关，所以对于a[i]，在计算[1,las[a[i]]]的val[]时，a[i]不会做出贡献；
而用[las[a[i]]+1,i]计算val时，a[i]会有1的贡献 
即用f[k](k∈[1,las[a[i]]-1])时，不会有a[i]的贡献；
而用f[k](k∈[las[a[i]],i-1])更新时，a[i]会对其产生贡献(k这个点是不在后一个区间里的) 
在这段区间+1，然后查询最优值，更新f[i] 
区间加、区间查询最优值 -> 线段树 
注意1.可以从f[0]更新 
2.查询位置与第一层循环的关系 

基本线段树都不会写了...
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==IN &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define lson node[rt].ls
#define rson node[rt].rs
const int N=35005,MAXIN=5e6;

int n,k,A[N],f[N],las[N],tmp[N];
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
struct Seg_Tree
{
	int tot;
	struct Node
	{
		int ls,rs,maxv,tag;
	}node[N<<1];
	inline void PushUp(int rt)
	{
		node[rt].maxv=std::max(node[lson].maxv,node[rson].maxv);
	}
	inline void PushDown(int rt)
	{
		node[lson].maxv+=node[rt].tag, node[rson].maxv+=node[rt].tag;
		node[lson].tag+=node[rt].tag, node[rson].tag+=node[rt].tag;
		node[rt].tag=0;
	}
	void Build(int l,int r)
	{
		int p=tot++;
		node[p].tag=0;
		if(l==r) { node[p].ls=node[p].rs=-1,node[p].maxv=f[l]; return;}
		int m=l+r>>1;
		node[p].ls=tot, Build(l,m);
		node[p].rs=tot, Build(m+1,r);
		PushUp(p);
	}
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R)
		{
			++node[rt].maxv, ++node[rt].tag;
			return;
		}
		if(node[rt].tag) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(l,m,lson,L,R);
		if(m<R) Modify(m+1,r,rson,L,R);
		PushUp(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return node[rt].maxv;
		if(node[rt].tag) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(l,m,lson,L,R),Query(m+1,r,rson,L,R));
			else return Query(l,m,lson,L,R);
		else return Query(m+1,r,rson,L,R);
	}
}t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("D.in","r",stdin);
#endif

	n=read(),k=read();
	for(int i=1;i<=n;++i)
		A[i]=read(), las[i]=tmp[A[i]], tmp[A[i]]=i;
//	for(int i=1;i<=n;++i) printf("%d %d\n",A[i],las[i]);
	for(int i=1;i<=k;++i)
	{
		t.tot=0, t.Build(0,n);
		for(int j=i;j<=n;++j)
			t.Modify(0,n,0,las[j],j-1),f[j]=t.Query(0,n,0,i-1,j-1);
	}
	printf("%d",f[n]);

	return 0;
}
