/*
4928KB	192MS
线段树每个节点记录$f(mid)$最大的直线（在$mid$处函数值最大的直线），称作优势线段（还是直线啊...无所谓了）。
如果是在区间插入线段会影响$O(\log n)$个区间，每个区间的更新是$O(\log n)$的，所以插入复杂度为$O(n\log^2n)$。
（这题是在$[1,n]$插入所以复杂度是一个$log$的吧）
查询时利用标记永久化的思想，答案一定在某一条经过节点的优势线段上。复杂度$O(\log n)$。
注意b是S-P不是S。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 1000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=50005;

char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	double K[S],B[S];
	#undef S
	void Insert(int l,int r,int rt,double k,double b)
	{
		if(!K[rt]) {K[rt]=k, B[rt]=b; return;}
		double l1=k*l+b,r1=k*r+b,l2=K[rt]*l+B[rt],r2=K[rt]*r+B[rt];
		if(l1<=l2 && r1<=r2) return;
		if(l1>l2 && r1>r2) {K[rt]=k, B[rt]=b; return;}
		double p=(B[rt]-b)/(k-K[rt]);//交点坐标 
		int m=l+r>>1;
		if(l1<l2)
			if(p<=m) Insert(lson,K[rt],B[rt]), K[rt]=k, B[rt]=b;
			else Insert(rson,k,b);
		else
			if(p<=m) Insert(lson,k,b);
			else Insert(rson,K[rt],B[rt]), K[rt]=k, B[rt]=b;
	}
	double Query(int l,int r,int rt,int x)
	{
		if(l==r) return K[rt]*x+B[rt];
		int m=l+r>>1;
		return std::max(K[rt]*x+B[rt],x<=m?Query(lson,x):Query(rson,x));
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline double readdb()
{
	double x=0,y=0.1,f=1;register char c=gc();
	for(;!isdigit(c)&&c!='.';c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);x=x*10+c-'0',c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=(c-'0')*y,y*=0.1,c=gc());
	return x*f;
}

int main()
{
	const int n=50000; double k,b;
	for(int Q=read(); Q--; )
	{
		register char c=gc(); while(c!='Q'&&c!='P') c=gc();
		switch(c)
		{
			case 'Q': printf("%d\n",(int)(T.Query(1,n,1,read())/100)); break;
			case 'P': b=readdb(),k=readdb(),T.Insert(1,n,1,k,b-k); break;
		}
	}
	return 0;
}
