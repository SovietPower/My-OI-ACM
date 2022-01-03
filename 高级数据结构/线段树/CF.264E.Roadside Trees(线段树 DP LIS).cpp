/*
840ms	12800KB
https://www.cnblogs.com/SovietPower/p/9743673.html
为了方便，我们将x坐标左右反转，再将所有高度取反，这样依然是维护从左到右的LIS，但是每次是在右边删除元素。
这样对于在p刚种的树，最多只有9棵树比它高，即它只会转移到这9棵树，除这9棵树外，它可以从1~p-1的任何树转移（其它9棵树除比它高的外同样可以从它前面任何树转移）。
我们把这9棵树的DP值暴力删掉，然后从低到高从1~pos[h]-1转移并更新。按高度更新就只需要考虑位置合不合法了。
我们对位置建线段树维护每个位置的DP值，就只有单点修改、区间max。
对于砍掉右数第k棵树，设位置为p，因为只有右边最多9棵树从它转移，同样将它们的DP值暴力删掉，然后删掉位置p的DP值。
但是右边10棵树不一定是最高的，虽然它们可以从前面所有树转移，但还要满足高度小于它们。
这可以二维线段树。但是我们只需要用另一棵线段树对每个高度维护同样的DP值（不同位置高度不同），就可以从左到右，直接用线段树查询并更新了。
这样在一棵线段树上更新完DP值后在另一棵上改一下即可。
复杂度$O(10n\log n)$。
总结：是最高的10棵就在维护位置DP值的线段树上转移，是最靠右的10棵就在维护高度DP值的线段树上转移。最后更新一下另一棵的DP值（都维护一样的）。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 50000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+15;

int pos[N],h[N];
std::set<int> st;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int f[N],mx[S];
	#undef S

	#define Update(rt) mx[rt]=std::max(mx[ls],mx[rs])
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) {mx[rt]=v; return;}
		int m=l+r>>1;
		if(p<=m) Modify(lson,p,v);
		else Modify(rson,p,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int R)
	{
		if(r<=R) return mx[rt];
		int m=l+r>>1;
		if(m<R) return std::max(Query(lson,R),Query(rson,R));
		return Query(lson,R);
	}
	void Insert(int p,int n)//对于新插入的p查询DP值并更新 
	{
		Modify(0,n,1,p,f[p]=Query(0,n,1,p-1)+1);
	}
}Tp,Th;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	#define Sp 0,n,1
	#define Sh 0,m+10,1
	int n=read(),m=read();//pos[i]:高i的树的位置 h[i]:i位置的树的高度 
	for(int t=1; t<=m; ++t)
		if(read()==1)//plant
		{
			int p=n-read()+1,ht=t+10-read();
			pos[ht]=p, h[p]=ht, st.insert(p);
			for(int i=ht+1; i<=ht+9; ++i)
				if(pos[i]) Tp.Modify(Sp,pos[i],0);
			for(int i=ht; i<=ht+9; ++i)
				if(pos[i])
				{
					Tp.Insert(pos[i],n);
					Th.f[i]=Tp.f[pos[i]];
					Th.Modify(Sh,i,Th.f[i]);
				}
			printf("%d\n",Tp.mx[1]);
		}
		else
		{
			int k=read();
			std::set<int>::iterator it=st.end();
			while(k--) --it, Th.Modify(Sh,h[*it],0);
			Tp.Modify(Sp,*it,0), pos[h[*it]]=0;
			for(st.erase(it++); it!=st.end(); ++it)
			{
				Th.Insert(h[*it],m+10);
				Tp.f[*it]=Th.f[h[*it]];
				Tp.Modify(Sp,*it,Tp.f[*it]);
			}
			printf("%d\n",Tp.mx[1]);
		}

	return 0;
}
