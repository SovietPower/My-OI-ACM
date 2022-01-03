/*
439ms	46MB
$Description$
每个位置有一个$3\times3$的矩阵，要求支持区间赋值和求区间乘积。
$n,q\leq10^5$。

$Solution$
裸的线段树+矩阵快速幂是$O(3^3q\log^2n)$的，因为维护区间乘的话，区间赋值为矩阵$A$的时候要赋值$A^{r-l+1}$，带一个快速幂。
考虑怎么把那个快速幂去掉。发现对于长度为$n$的线段树的区间长度只有$O(\log n)$种，可以预处理出$A$的区间次幂，直接赋值。
不同区间的长度可能比较乱，但是把线段树长度补成$2^k$，就很容易维护了。
复杂度$O(3^3(n+q)\log n)$。
写了这个题的代码纯属闲...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 998244353
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<17)+7,M=1e5+5,BIT=17;

int ref[N];
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read();
struct Matrix
{
	int a[3][3];
	inline void Read()
	{
		for(int i=0; i<3; ++i)
			for(int j=0; j<3; ++j) a[i][j]=read();
	}
	Matrix operator *(const Matrix &x)
	{
		Matrix res;
		for(int i=0; i<3; ++i)
			for(int j=0; j<3; ++j)
			{
				LL tmp=0;
				for(int k=0; k<3; ++k) tmp+=1ll*a[i][k]*x.a[k][j]%mod;
				res.a[i][j]=tmp%mod;
			}
		return res;
	}
}A[N],pw[M][BIT+1];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int tag[S];
	Matrix t[S];
	#undef S
	#define Upd(rt,id,l) t[rt]=pw[id][ref[l]], tag[rt]=id
	#define Update(rt) t[rt]=t[ls]*t[rs]
	inline void PushDown(int rt,int m)
	{
		Upd(ls,tag[rt],m>>1), Upd(rs,tag[rt],m>>1), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {t[rt]=A[l]; return;}
		int m=l+r>>1; Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int id)
	{
		if(L<=l && r<=R) {Upd(rt,id,r-l+1); return;}
		if(tag[rt]) PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,id);
		if(m<R) Modify(rson,L,R,id);
		Update(rt);
	}
	Matrix Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return t[rt];
		if(tag[rt]) PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)*Query(rson,L,R);
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	#define S 1,lim,1
	int n=read()-1,Q=read(),lim=1,bit=0;
	for(int i=1; i<=n; ++i) A[i].Read();
	while(lim<n) lim<<=1, ++bit;
	for(int i=0; i<=bit; ++i) ref[1<<i]=i;
	T.Build(S);
	for(int t=0; Q--; )
		switch(read())
		{
			case 1:
			{
				int l=read(),r=read(); pw[++t][0].Read();
				for(int i=1; i<=bit; ++i) pw[t][i]=pw[t][i-1]*pw[t][i-1];
				T.Modify(S,l,r,t); break;
			}
			case 2:
			{
				int l=read(),r=read();
				Matrix res=T.Query(S,l,r-1); LL ans=0;
				for(int i=0; i<3; ++i)
					for(int j=0; j<3; ++j) ans+=res.a[i][j];
				printf("%d\n",(int)(ans%mod)); break;
			}
		}

	return 0;
}
