/*
21632kb	880ms
$Description$
给定$n$个区间$[L_i,R_i]$，要选出尽量多的区间，并满足它们互不相交。求最多能选出多少个的区间以及字典序最小的方案。
$n\leq2\times10^5$。
$Solution$
第一问随便做。
对于第二问，从小到大枚举区间$[l_i,r_i]$，我们需要判断此时能不能选$[l_i,r_i]$。
在之前选的区间中，设在$i$左边离$l_i$最近的区间的右端点是$L$，在$i$右边离$i$最近的左端点是$R$。
显然要满足$i$与选中的区间不相交，有$L<l_i$且$R>r_i$。同时这两个区间在已选择的区间中一定是相邻的。可以$set$维护选择的区间，$lower\_bound$一次找出。

满足不相交后，还要满足最优。
令$Ans(l,r)$表示用在$[l,r]$能选出的最多区间数。
那么能放入区间$[l_i,r_i]$还要满足$Ans(L+1,R-1)==Ans(L+1,l_i-1)+Ans(r_i+1,R-1)+1$。很好理解。（只判$i$的前后缀显然不对啊）

如何求$Ans(l,r)$？
二分可以找到第一个满足$l_i\geq l$的区间$i$，然后从$i$往后选，直到右端点$>r$。根据最简单的贪心，每选一个区间下一次选择的区间是确定的。so可以倍增，令$f[i][j]$表示从区间$i$开始选，选了$2^j$个区间后，停在哪个区间。
显然此时可以把完全包含其它区间的大区间给去掉，而且需要去掉（如果选到它们会影响答案）。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,INF=1<<30;

int cnt,Bit,L[N],R[N],f[18][N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int l,r,id;
	bool operator <(const Node &x)const
	{
		return r==x.r?l>x.l:r<x.r;
	}
}A[N],tmp[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Find(int x)
{
	int l=1,r=cnt,mid;//cnt+1!（l may be greater than l[cnt]）
	while(l<r)
		if(L[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline int Calc(int l,int r)
{
	if(L[cnt]<l) return 0;
	int p=Find(l);
	if(R[p]>r) return 0;
	int res=1;
	for(int i=Bit; ~i; --i)
		if(R[f[i][p]]<=r) res+=1<<i, p=f[i][p];
	return res;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=tmp[i]=(Node){read(),read()};
	std::sort(tmp+1,tmp+1+n), cnt=1;
	for(int i=2; i<=n; ++i) if(tmp[i].l>tmp[cnt].l) tmp[++cnt]=tmp[i];//左右端点应该都是单调的 
	for(int i=1; i<=cnt; ++i) L[i]=tmp[i].l, R[i]=tmp[i].r;
	L[cnt+1]=INF+1, R[0]=R[cnt+1]=INF+1;//INF+1!（后面会查l~INF）
	for(int i=1,j=1; i<=cnt; ++i)
	{
		while(L[j]<=R[i]) ++j;
		f[0][i]=j;
	}
	for(; 1<<Bit+1<=cnt; ++Bit);
	for(int j=1; j<=Bit; ++j)
		for(int i=1; i<=cnt; ++i)
			f[j][i]=f[j-1][f[j-1][i]];

	int ans=Calc(1,INF-1); printf("%d\n",ans);
	std::set<Node> st;
	st.insert((Node){0,0}), st.insert((Node){INF,INF});
	for(int i=1,k=0; i<=n; ++i)
	{
		int l=A[i].l, r=A[i].r;
		std::set<Node>::iterator it=st.lower_bound(A[i]);
		int R=(*it).l; if(r>=R) continue;
		int L=(*(--it)).r; if(l<=L) continue;
		if(Calc(L+1,R-1)==Calc(L+1,l-1)+Calc(r+1,R-1)+1)
			if(++k!=ans) printf("%d ",i), st.insert(A[i]);
			else {printf("%d",i); break;}
	}

	return 0;
}
